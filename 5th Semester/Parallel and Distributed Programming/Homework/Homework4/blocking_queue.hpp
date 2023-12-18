#include <semaphore>
#include <thread>
#include <exception>

// T: should have a default constructor defined
template <class T>
class BlockingQueue {
private:
  struct BlockingQueueNode {
    T data;
    BlockingQueueNode* next;
    BlockingQueueNode(T data) {
      this->data = data;
      this->next = nullptr;
    }
  };
  BlockingQueueNode* root;
  BlockingQueueNode* last;
  std::counting_semaphore<1> readersSemaphore{0};
  std::counting_semaphore<1> writersSemaphore{0};
  std::mutex mtx;
  std::mutex countMtx;
  int readerThreadsCount;
  int writerThreadsCount;
public:
  BlockingQueue(int readerThreadsCount, int writerThreadsCount) {
    this->root = nullptr;
    this->last = nullptr;
    this->readerThreadsCount = readerThreadsCount;
    this->writerThreadsCount = writerThreadsCount;
  }

  void push(T const& elem);
  T pop();
  void writerFinished();
  void waitForReadersToFinish();

  bool empty() const;
};

template <class T>
void BlockingQueue<T>::push(T const& elem) {
  auto node = new BlockingQueueNode(elem);
  mtx.lock();
  if (root == nullptr) {
    root = node;
    last = node;
    readersSemaphore.release(readerThreadsCount);
  } else {
    last->next = node;
    last = node;
  }
  mtx.unlock();
}

template <class T>
T BlockingQueue<T>::pop() {
  mtx.lock();
  while (root == nullptr) {
    mtx.unlock();
    if (writerThreadsCount == 0) {
      countMtx.lock();
      readerThreadsCount--;
      readersSemaphore.release(readerThreadsCount);
      countMtx.unlock();
      if (readerThreadsCount == 0) {
        writersSemaphore.release();
      }
      throw std::exception();
    }
    readersSemaphore.acquire();
    mtx.lock();
  }
  auto next = root->next;
  auto data = root->data;
  delete root;
  root = next;
  mtx.unlock();
  return data;
}

template <class T>
void BlockingQueue<T>::writerFinished() {
  countMtx.lock();
  writerThreadsCount--;
  countMtx.unlock();
}

template <class T>
bool BlockingQueue<T>::empty() const {
  return root == nullptr;
}

template <class T>
void BlockingQueue<T>::waitForReadersToFinish() {
  writersSemaphore.acquire();
}
