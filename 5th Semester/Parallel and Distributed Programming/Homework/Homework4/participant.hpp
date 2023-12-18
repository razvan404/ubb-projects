#pragma once
#include <string>

class Participant {
private:
  int id;
  int score;
public:
  static const int INVALID_ID = -1;
  Participant() {
    this->id = INVALID_ID;
  }

  inline int getId() const {
    return id;
  }

  inline void setId(int id) {
    this->id = id;
  }

  inline int getScore() const {
    return score;
  }

  inline void setScore(int score) {
    this->score = score;
  }

  inline void addScore(int score) {
    this->score += score;
  }

  inline std::string toString() const {
    return std::to_string(id) + " -> " + std::to_string(score);
  }

  inline bool operator<(const Participant& other) const {
    return score > other.score || (score == other.score && id < other.id);
  }
};