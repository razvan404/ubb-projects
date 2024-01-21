#ifndef _RANKING_MANAGER_HPP_
#define _RANKING_MANAGER_HPP_

#include "List.hpp"

class RankingManager
{
public:
    VOID
    AddTask(_Inout_ std::promise<std::vector<std::pair<int, int>>>& Promise)
    {
        {
            std::lock_guard<std::mutex> lock(this->Mutex);
            this->PromiseQueue.push(std::move(Promise));
        }
        this->Cv.notify_one();
    }

    VOID
    WaitForTaskAndCalculatePartialRanking(_In_ const List<Participant>& Participants, _In_ int DeltaT)
    {
        std::promise<std::vector<std::pair<int, int>>> promise;
        {
            std::unique_lock<std::mutex> lock(this->Mutex);
            this->Cv.wait(lock, [this] { return !this->PromiseQueue.empty(); });

            promise = std::move(this->PromiseQueue.front());
            this->PromiseQueue.pop();
        }

        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - this->LastCalculated) > std::chrono::milliseconds(DeltaT) ||
            this->LastCountryRanking.empty())
        {
            this->LastCalculated = now;
            this->CalculateCountryRanking(Participants, this->LastCountryRanking);
        }

        promise.set_value(this->LastCountryRanking);
    }

    VOID
    CalculateCountryRanking(_In_ const List<Participant>& Participants, _Out_ std::vector<std::pair<int, int>>& Ranking)
    {
        std::unordered_map<int, int> countryRanking;
        std::vector<Participant> results;
        Participants.GetResults(results);

        for (const Participant& participant : results)
        {
            countryRanking[participant.GetCountry()] += participant.GetScore();
        }

        std::vector<std::pair<int, int>> sortedRanking;
        sortedRanking.reserve(countryRanking.size());
        for (const std::pair<int, int>& countryData : countryRanking)
        {
            sortedRanking.push_back(countryData);
        }

        std::sort(sortedRanking.begin(), sortedRanking.end(), [&](const std::pair<int, int>& A, const std::pair<int, int>& B) { return A.second > B.second; });
        Ranking = sortedRanking;
    }

    VOID
    CalculateUserRanking(_In_ const List<Participant>& Participants, _Out_ std::vector<std::pair<int, int>>& Ranking)
    {
        std::unordered_map<int, int> userRanking;
        std::vector<Participant> results;
        Participants.GetResults(results);

        for (const Participant& participant : results)
        {
            userRanking[participant.GetId()] += participant.GetScore();
        }

        std::vector<std::pair<int, int>> sortedRanking;
        sortedRanking.reserve(userRanking.size());
        for (const std::pair<int, int>& userData : userRanking)
        {
            sortedRanking.push_back(userData);
        }

        std::sort(sortedRanking.begin(), sortedRanking.end(), [&](const std::pair<int, int>& A, const std::pair<int, int>& B) { return A.second > B.second; });
        Ranking = sortedRanking;
    }

private:
    std::mutex Mutex;
    std::condition_variable Cv;
    _Guarded_by_(Mutex) std::queue<std::promise<std::vector<std::pair<int, int>>>> PromiseQueue;

    std::chrono::time_point<std::chrono::system_clock> LastCalculated = std::chrono::system_clock::now();
    std::vector<std::pair<int, int>> LastCountryRanking;
    std::vector<std::pair<int, int>> LastUserRanking;
};

#endif//_RANKING_MANAGER_HPP_