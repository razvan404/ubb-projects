#include "pch.h"
#include "..\server\Participant.hpp"
#include "ConcursClient.hpp"

#define COUNTRY_COUNT   5
#define TASKS_COUNT     10
#define CHUNK_MAX_SIZE  20
#ifdef V2
#define BLOCK_SIZE      27
#endif

static const constexpr int gProducersCount = COUNTRY_COUNT;
static const constexpr int gDeltaX = 1200;

static
VOID
RequestPartialRankings(_In_ ConcursClient& ConcursClient)
{
    ConcursClient.Send(99998); // signal that we want the partial leaderboard

    std::vector<std::pair<int, int>> countryRanking;
    ConcursClient.Recv(countryRanking);
}

static
VOID
RequestFinalRankings(_In_ ConcursClient& ConcursClient)
{
    ConcursClient.Send(99999); // signal that we want the final leaderboard

    std::vector<std::pair<int, int>> countryRanking;
    ConcursClient.Recv(countryRanking);

    std::vector<std::pair<int, int>> userRanking;
    ConcursClient.Recv(userRanking);
}

static
VOID
ProducerWorker(_In_ int ThreadIndex)
{
    try
    {
        ConcursClient concursClient;
        bool status = concursClient.Connect();
        if (!status)
        {
            return;
        }

        concursClient.Send(ThreadIndex);

#ifndef V2
        std::vector<Participant> participantsChunk;
        std::vector<std::vector<Participant>> participants;
#endif

        for (int j = 1; j <= TASKS_COUNT; ++j)
        {
            CHAR filePath[MAX_PATH] = { 0 };
            _snprintf_s(filePath, MAX_PATH, _TRUNCATE, "D:\\facultate-repo\\sem5\\ppd\\p1\\inputs\\RezultateC%d_P%d.txt", ThreadIndex, j);

            std::ifstream fin(filePath, std::ios::binary);
            if (!fin.is_open())
            {
                continue;
            }

#ifdef V2
            CHAR buffer[BLOCK_SIZE] = { 0 };
            while (!fin.eof())
            {
                fin.read(buffer, BLOCK_SIZE);
                std::streamsize bytesRead = fin.gcount();

                if (bytesRead == 0)
                {
                    break;
                }

                concursClient.Send(buffer, static_cast<int>(bytesRead));
            }
#else
            int participantId, participantScore;
            while (fin >> participantId >> participantScore)
            {
                Participant participant;
                participant.SetId(participantId);
                participant.SetScore(participantScore);

                participantsChunk.emplace_back(participant);
                if (participantsChunk.size() == CHUNK_MAX_SIZE)
                {
                    participants.emplace_back(participantsChunk);
                    participantsChunk.clear();
                }
            }
#endif

            fin.close();

#ifndef V2
            if (!participantsChunk.empty())
            {
                participants.emplace_back(participantsChunk);
                participantsChunk.clear();
            }

            for (const std::vector<Participant>& chunk : participants)
            {
                concursClient.Send(chunk);
                std::this_thread::sleep_for(std::chrono::milliseconds(gDeltaX));
            }
            participants.clear();
#endif

            RequestPartialRankings(concursClient);
        }

        RequestFinalRankings(concursClient);

        concursClient.Disconnect();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what();
    }
}

int main(int argc, char** argv)
{
    std::vector<std::thread> threads;
    for (int i = 1; i <= gProducersCount; ++i)
    {
        threads.push_back(std::move(std::thread(ProducerWorker, i)));
    }

    for (std::thread& thread : threads)
    {
        thread.join();
    }

    return 0;
}