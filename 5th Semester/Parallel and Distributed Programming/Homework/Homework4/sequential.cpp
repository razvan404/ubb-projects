#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>
#include "consts.hpp"
#include "participant.hpp"
#include "ordered_list.hpp"

namespace fs = std::filesystem;

void addParticipantsFromFile(OrderedList<Participant>* participants, std::string inputPath) {
  FILE* fin = fopen(inputPath.c_str(), "r");
  while (!feof(fin)) {
    int idParticipant, score;
    fscanf(fin, "%d%d", &idParticipant, &score);
    auto participant = participants->removeById(idParticipant);
    if (participant.getId() == Participant::INVALID_ID) {
      participant.setId(idParticipant);
      participant.setScore(score);
      participants->add(participant);
    } else if (participant.getScore() == -1) {
      participants->add(participant);
    } else if (score == -1) {
      participant.setScore(-1);
      participants->add(participant);
    } else {
      participant.addScore(score);
      participants->add(participant);
    }
  }
  fclose(fin);
}

void writeInFile(std::string data, std::string outputPath) {
  FILE* fout = fopen(outputPath.c_str(), "w");
  fprintf(fout, "%s", data.c_str());
  fclose(fout);
}

int main(int argc, char* argv[]) {
  OrderedList<Participant> participants;
  
  auto start = std::chrono::high_resolution_clock::now();
  for (const auto& input : fs::directory_iterator(INPUTS_DIR)) {
    addParticipantsFromFile(&participants, input.path());
  }
  auto str = participants.toString();
  writeInFile(str, OUTPUTS_DIR + "sequential.txt");
  auto end = std::chrono::high_resolution_clock::now();
  double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
  std::cout << elapsedTimeMs << std::endl;
  return 0;
}