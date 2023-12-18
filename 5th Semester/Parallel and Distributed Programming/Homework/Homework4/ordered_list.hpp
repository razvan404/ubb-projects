#pragma once
#include <string>

// T: should have getId() and toString() methods,
// should also have the operator< and a default constructor defined
template <class T>
class OrderedList {
private:
  struct OrderedListNode {
    T data;
    OrderedListNode* next;
    OrderedListNode(T data) {
      this->data = data;
      this->next = nullptr;
    }
  };
  OrderedListNode* root;
public:
  OrderedList() {
    this->root = nullptr;
  }

  void add(T const& elem);
  T removeById(int const& id);
  std::string toString() const;

  ~OrderedList();
};

template <class T>
void OrderedList<T>::add(T const& elem) {
  auto node = new OrderedListNode(elem);
  if (root == nullptr) {
    root = node;
    return;
  }
  if (elem < root->data) {
    node->next = root;
    root = node;
    return;
  }
  auto crt = root;
  while (crt->next != nullptr && !(elem < crt->next->data)) {
    crt = crt->next;
  }
  node->next = crt->next;
  crt->next = node;
}

template <class T>
T OrderedList<T>::removeById(int const& id) {
  if (root == nullptr) return T{};
  if (root->data.getId() == id) {
    auto next = root->next;
    auto data = root->data;
    delete root;
    root = next;
    return data;
  }
  auto crt = root;
  while (crt->next != nullptr && crt->next->data.getId() != id) {
    crt = crt->next;
  }
  if (crt->next == nullptr) return T{};
  auto next = crt->next->next;
  auto data = crt->next->data;
  delete crt->next;
  crt->next = next;
  return data;
}

template <class T>
std::string OrderedList<T>::toString() const {
  std::string str = "";
  auto crt = root;
  while (crt != nullptr) {
    str += crt->data.toString();
    if (crt->next != nullptr) str += "\n";
    crt = crt->next;
  }
  return str;
}

template <class T>
OrderedList<T>::~OrderedList() {
  while (root != nullptr) {
    auto next = root->next;
    delete root;
    root = next;
  }
}