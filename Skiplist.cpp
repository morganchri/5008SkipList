#include "Skiplist.h"

inline int Skiplist::coinFlip() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  return round(dis(gen));
}

inline node_t* Skiplist::skipSearch(int k){
  node_t* temp = this->head[this->height];
  while (temp != nullptr) {
    if (k == temp->data) {
      return temp;
    } else if (k < temp->next->data) {
      temp = temp->down;
    } else if (k >= temp->next->data) {
      temp = temp->next;
    } else {
      cout << k << " is not in the Skiplist\n";
      return nullptr;
    }
  }
  return nullptr;
}

inline void lInsert(node_t* list, int k) {
  auto* newNode = new node(k);
  while (list != nullptr) {
    if (list->data <= k && list->next->data > k) {
      newNode->next = list->next;
      list->next = newNode;
    } else {
      list = list->next;
    }
  }
}

inline void Skiplist::skipInsert(int k) {
  lInsert(this->head[0], k);
  int i = 1;
  while(coinFlip() != 0) {
    lInsert(this->head[i], k);
    i++;
  }
}

inline void lDelete(node_t* list, int k) {
  node_t* temp = list;
  node_t* prev = nullptr;
  if (temp != nullptr && temp->data == k) {
    temp = temp->next;
    delete(temp);
    return;
  } else {
    while (temp != nullptr && temp->data != k) {
      prev = temp;
      temp = temp->next;
    }
    if (temp == nullptr) {
      return;
    }
    prev->next = temp->next;
    delete(temp);
  }
}

inline void Skiplist::skipDelete(int k) {
  while(this->skipSearch(k) != nullptr) {
    lDelete(this->head[this->height], k);
  }
}