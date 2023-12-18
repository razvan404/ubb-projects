#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <filesystem>
#include "consts.hpp"
#include "participant.hpp"
#include "ordered_list.hpp"
#include "blocking_queue.hpp"

namespace fs = std::filesystem;
int readersCount;
int workersCount;

void writeInFile(std::string data, std::string& outputPath) {
  FILE* fout = fopen(outputPath.c_str(), "w");
  fprintf(fout, "%s", data.c_str());
  fclose(fout);
}

void readerThread(std::vector<std::string>* inputsPaths, BlockingQueue<Participant>* bq, OrderedList<Participant>* participants, int id, std::string* output_dir) {
  for (int i = id; i < inputsPaths->size(); i += readersCount) {
    auto inputPath = inputsPaths->at(i);
    FILE* fin = fopen(inputPath.c_str(), "r");
    while (!feof(fin)) {
      int idParticipant, score;
      fscanf(fin, "%d%d", &idParticipant, &score);
      Participant participant;
      participant.setId(idParticipant);
      participant.setScore(score);
      bq->push(participant);
    }
    fclose(fin);
  }
  bq->writerFinished();
  if (id == 0) {
    bq->waitForReadersToFinish();
    writeInFile(participants->toString(), *output_dir);
  }
}

void workerThread(BlockingQueue<Participant>* bq, OrderedList<Participant>* participants, std::mutex* mutex) {
  while (true) {
    try {
      auto participant = bq->pop();
      mutex->lock();
      auto participantInList = participants->removeById(participant.getId());
      if (participantInList.getId() == Participant::INVALID_ID) {
        participants->add(participant);
      } else if (participantInList.getScore() == -1) {
        participants->add(participantInList);
      } else if (participant.getScore() == -1) {
        participants->add(participant);
      } else {
        participant.addScore(participantInList.getScore());
        participants->add(participant);
      }
      mutex->unlock();
    } catch (...) {
      break;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid syntax!\nUsage: %s <num threads readers> <num threads workers>", argv[0]);
    exit(1);
  }
  readersCount = atoi(argv[1]);
  workersCount = atoi(argv[2]);
  BlockingQueue<Participant> bq(workersCount, readersCount);
  OrderedList<Participant> participants;
  std::mutex workersMutex;
  std::vector<std::string> inputsPaths;
  for (const auto& input : fs::directory_iterator(INPUTS_DIR)) {
    inputsPaths.push_back(input.path());
  }
  std::vector<std::thread> threads;
  std::string output_dir = OUTPUTS_DIR + "threads_" + std::to_string(readersCount) + "_" + std::to_string(workersCount) + ".txt";

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < readersCount; i++) {
    threads.push_back(std::thread(readerThread, &inputsPaths, &bq, &participants, i, &output_dir));
  }
  for (int i = 0; i < workersCount; i++) {
    threads.push_back(std::thread(workerThread, &bq, &participants, &workersMutex));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  auto end = std::chrono::high_resolution_clock::now();
  double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
  std::cout << elapsedTimeMs << std::endl;

  return 0;
}