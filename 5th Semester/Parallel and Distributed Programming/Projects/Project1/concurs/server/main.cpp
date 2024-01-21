#include "pch.h"
#include "SynchPrimitive.hpp"
#include "List.hpp"
#include "Participant.hpp"
#include "ConcursServer.hpp"

#define COUNTRY_COUNT   5
#define TASKS_COUNT     10
#define QUEUE_SIZE      50

static const constexpr int gClientProducersCount = COUNTRY_COUNT;
static int gServerProducersCount = 2;
static int gConsumersCount = 2;
static int gDeltaT = 1;

static
VOID
PrintResults(_In_ const std::vector<std::pair<int, int>>& Results, _In_ const std::string& FileName)
{
    std::string outputFileName = "D:\\facultate-repo\\sem5\\ppd\\p1\\output\\" + FileName + ".txt";
    std::ofstream fout(outputFileName);

    for (const std::pair<int, int>& result : Results)
    {
        fout << result.first << ' ' << result.second << '\n';
    }
    fout.flush();
    fout.close();
}

static
VOID
CalculatePartialRanking(
    _In_ RankingManager&          RankingManager,
    _In_ const List<Participant>& Participants,
    _In_ int                      DeltaT
)
{
    for (int i = 1; i <= COUNTRY_COUNT * TASKS_COUNT; ++i)
    {
        RankingManager.WaitForTaskAndCalculatePartialRanking(Participants, DeltaT);
    }
}

static
VOID
CalculateFinalRankings(
    _In_    RankingManager&                   RankingManager,
    _In_    const List<Participant>&          Participants,
    _Inout_ std::vector<std::pair<int, int>>& CountryRanking,
    _Inout_ std::vector<std::pair<int, int>>& UserRanking
)
{
    RankingManager.CalculateCountryRanking(Participants, CountryRanking);
    RankingManager.CalculateUserRanking(Participants, UserRanking);
}

static
VOID
ConsumerWorker(
    _Inout_ ProducerConsumerQueue<Participant>& PcQueue,
    _Inout_ List<Participant>&                  Participants
)
{
    while (true)
    {
        std::optional<Participant> participant = PcQueue.Consume();
        if (!participant.has_value())
        {
            break;
        }

        Participants.Process(participant.value());
    }

    PcQueue.UnregisterConsumer();
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cout << "Use <p_r> <p_w> <delta_t>\n";
        return -1;
    }

    gServerProducersCount = atoi(argv[1]);
    gConsumersCount = atoi(argv[2]);
    gDeltaT = atoi(argv[3]);

    RankingManager rankingManager;
    ProducerConsumerQueue<Participant> pcQueue(QUEUE_SIZE, gClientProducersCount, gConsumersCount);
    List<Participant> participants;

    try
    {
        ConcursServer concursServer{ gClientProducersCount, gServerProducersCount, pcQueue, rankingManager };
        concursServer.Start();

        std::vector<std::thread> threads;
        for (int i = 1; i <= gConsumersCount; ++i)
        {
            threads.push_back(std::move(std::thread(ConsumerWorker, std::ref(pcQueue), std::ref(participants))));
        }

        CalculatePartialRanking(rankingManager, participants, gDeltaT);

        for (std::thread& thread : threads)
        {
            thread.join();
        }

        std::vector<std::pair<int, int>> countryRanking;
        std::vector<std::pair<int, int>> userRanking;
        CalculateFinalRankings(rankingManager, participants, countryRanking, userRanking);

        PrintResults(countryRanking, "ClasamentTari");
        PrintResults(userRanking, "ClasamentUseri");

        concursServer.SendFinalResults(countryRanking, userRanking);
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what();
    }

    return 0;
}