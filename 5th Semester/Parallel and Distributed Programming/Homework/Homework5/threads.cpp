#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <filesystem>
#include "consts.hpp"
#include "participant.hpp"
#include "participants_sync_list.hpp"
#include "blocking_queue.hpp"

namespace fs = std::filesystem;
int readersCount;
int workersCount;

void writeInFileAndDelete(std::vector<Participant*> data, std::string& outputPath) {
  FILE* fout = fopen(outputPath.c_str(), "w");
  for (const auto& participant : data) {
    fprintf(fout, "%s\n", participant->toString().c_str());
    delete participant;
  }
  fclose(fout);
}

void readerThread(std::vector<std::string>* inputsPaths, BlockingQueue<Participant>* bq, ParticipantsSyncList* participants, int id) {
  for (int i = id; i < inputsPaths->size(); i += readersCount) {
    auto inputPath = inputsPaths->at(i);
    FILE* fin = fopen(inputPath.c_str(), "r");
    while (!feof(fin)) {
      int idParticipant, score;
      if (fscanf(fin, "%d%d", &idParticipant, &score) == -1) {
        break;
      }
      Participant* participant = new Participant(idParticipant, score);
      bq->push(participant);
    }
    fclose(fin);
  }
  bq->writerFinished();
}

void workerThread(BlockingQueue<Participant>* bq, ParticipantsSyncList* participants) {
  while (auto participant = bq->pop()) {
    participants->push(participant);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid syntax!\nUsage: %s <num threads readers> <num threads workers>", argv[0]);
    exit(1);
  }
  readersCount = atoi(argv[1]);
  workersCount = atoi(argv[2]);
  BlockingQueue<Participant> bq(100, readersCount);
  ParticipantsSyncList participants;

  std::vector<std::string> inputsPaths;
  for (const auto& input : fs::directory_iterator(INPUTS_DIR)) {
    inputsPaths.push_back(input.path());
  }

  std::vector<std::thread> threads;
  std::string output_dir = OUTPUTS_DIR + "threads_" + std::to_string(readersCount) + "_" + std::to_string(workersCount) + ".txt";

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < readersCount; i++) {
    threads.push_back(std::thread(readerThread, &inputsPaths, &bq, &participants, i));
  }
  for (int i = 0; i < workersCount; i++) {
    threads.push_back(std::thread(workerThread, &bq, &participants));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  writeInFileAndDelete(participants.sorted(), output_dir);
  auto end = std::chrono::high_resolution_clock::now();
  double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
  std::cout << elapsedTimeMs << std::endl;

  return 0;
}