#include <mutex>
#include <vector>
#include <algorithm>
#include "participant.hpp"

class ParticipantsSyncList {
private:
  struct Node {
    Participant* data;
    Node* next;
    std::mutex mtx;
    Node(Participant* data) {
      this->data = data;
      this->next = nullptr;
    }
  };
  Node* first, *last;
public:
  ParticipantsSyncList() {
    first = new Node(nullptr);
    last = new Node(nullptr);
    first->next = last;
  }

  void push(Participant* participant);
  std::vector<Participant*> sorted();
};

void ParticipantsSyncList::push(Participant* participant) {
  // because I declared both on one line, I wasted like 2-3 hours :)
  auto prev = first;
  prev->mtx.lock();
  auto current = first->next;
  current->mtx.lock();
  while (current != last) {
    if (current->data->getId() < participant->getId()) {
      prev->mtx.unlock();
      prev = current;
      current = current->next;
      current->mtx.lock();
    } else if (current->data->getId() == participant->getId()) {
      prev->mtx.unlock();
      if (current->data->getScore() == -1 || participant->getScore() == -1) {
        current->data->setScore(-1);
      } else {
        current->data->addScore(participant->getScore());
      }
      delete participant;
      current->mtx.unlock();
      return;
    } else {
      break;
    }
  }
  auto node = new Node(participant);
  prev->next = node;
  node->next = current;
  current->mtx.unlock();
  prev->mtx.unlock();
}

std::vector<Participant*> ParticipantsSyncList::sorted() {
  std::vector<Participant*> result;
  auto current = first->next;
  while (current != last) {
    result.push_back(current->data);
    current = current->next;
  }
  std::sort(result.begin(), result.end(), [](Participant* a, Participant* b) {
    return *a < *b;
  });
  return result;
}
