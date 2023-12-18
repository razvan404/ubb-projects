#include <semaphore>
#include <thread>
#include <exception>

template <class T>
class BlockingQueue {
private:
  struct BlockingQueueNode {
    T* data;
    BlockingQueueNode* next;
    BlockingQueueNode(T* data) {
      this->data = data;
      this->next = nullptr;
    }
  };
  BlockingQueueNode* root;
  BlockingQueueNode* last;
  std::condition_variable readersCV, writersCV;
  std::mutex mtx;
  std::mutex writersMutex;
  int currentLength;
  int capacity;
  int writersCount;
public:
  BlockingQueue(int capacity, int writersCount) {
    this->root = nullptr;
    this->last = nullptr;
    currentLength = 0;
    this->capacity = capacity;
    this->writersCount = writersCount;
  }

  void push(T* elem);
  T* pop();
  void writerFinished();
};

template <class T>
void BlockingQueue<T>::push(T* elem) {
  auto node = new BlockingQueueNode(elem);
  {
    std::unique_lock<std::mutex> lock(mtx);
    while (currentLength == capacity) {
      writersCV.wait(lock);
    }
    if (root == nullptr) {
      root = node;
      last = node;
    } else {
      last->next = node;
      last = node;
    }
    currentLength += 1;
  }
  readersCV.notify_one();
}

template <class T>
T* BlockingQueue<T>::pop() {
  BlockingQueueNode* node;
  {
    std::unique_lock<std::mutex> lock(mtx);
    while (root == nullptr) {
      if (writersCount == 0) {
        return nullptr;
      }
      readersCV.wait(lock);
    }
    node = root;
    root = root->next;
    if (root == nullptr) {
      last = nullptr;
    }
    currentLength -= 1;
  }
  writersCV.notify_one();
  auto data = node->data;
  delete node;
  return data;
}

template <class T>
void BlockingQueue<T>::writerFinished() {
  writersMutex.lock();
  writersCount--;
  if (writersCount == 0) {
    readersCV.notify_all();
  }
  writersMutex.unlock();
}