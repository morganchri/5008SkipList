#include "Skiplist.h"

inline int Skiplist::coinFlip() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  return round(dis(gen));
}

inline node_t* Skiplist::skipSearch(int k){
  node_t* temp = this->head[this->height];
  int tempHeight = this->height;
  while (temp != nullptr) {
    if (k == temp->data) {
      cout << temp->data << " at height: "
           << tempHeight << "\n";
      return temp;
    } else if (k < temp->next->data) {
      temp = temp->down;
      tempHeight--;
    } else if (k >= temp->next->data) {
      temp = temp->next;
    }
  }
  cout << k << " is not in the Skiplist\n";
  return nullptr;
}

inline int Skiplist::findHeight(int k) {
  node_t* temp = this->head[this->height];
  int tempHeight = this->height;
  while (temp != nullptr) {
    if (k == temp->data) {
      return tempHeight;
    } else if (k < temp->next->data) {
      temp = temp->down;
      tempHeight--;
    } else if (k >= temp->next->data) {
      temp = temp->next;
    }
  }
  cout << k << " is not in the Skiplist\n";
  return -9999;
}

inline void lInsert(node_t* list, int k) {
  auto* newNode = new node(k);
  node_t* temp = list;
  while (temp != nullptr) {
    if (temp->data < k && temp->next->data >= k) {
      newNode->next = temp->next;
      temp->next = newNode;
      return;
    } else {
      temp = temp->next;
    }
  }
}

inline void Skiplist::skipInsert(int k) {
  node_t* temp = this->head[0];
  lInsert(temp, k);
  int tempHeight = 1;
  int i = 1;
  while(coinFlip() != 0) {
    node_t* temp2 = this->head[i];
    lInsert(temp2, k);
    this->downSet(i, k);
    tempHeight++;
    i++;
  }
  if (tempHeight > this->height) {
    this->height = tempHeight;
  }
}

inline node_t* lFind(node_t* list, int k) {
  node_t* temp = list;
  while (temp != nullptr) {
    if (temp->data == k) {
      return temp;
    } else {
      temp = temp->next;
    }
  }
  return nullptr;
}

inline void Skiplist::downSet(int i, int k) {
  node_t* upper = lFind(this->head[i], k);
  node_t* lower = lFind(this->head[i - 1], k);
  if (upper != nullptr && lower != nullptr) {
    upper->down = lower;
  }
}

inline int lDelete(node_t* list, int k) {
  node_t* temp = list;
  node_t* prev = nullptr;
  if (temp != nullptr && temp->data == k) {
    temp = temp->next;
    delete(temp);
    return 1;
  } else {
    while (temp != nullptr && temp->data != k) {
      prev = temp;
      temp = temp->next;
    }
    if (temp == nullptr) {
      return 0;
    }
    prev->next = temp->next;
    delete(temp);
    return 1;
  }
}


inline void Skiplist::skipDelete(int k) {
  int i;
  int j = this->findHeight(k);
  for (i = j; i >= 0; i--) {
    lDelete(this->head[i], k);
  }
  cout << "Deleted: " << k << "\n";
}