#ifndef INC_5008SKIPLIST__SKIPLIST_H_
#define INC_5008SKIPLIST__SKIPLIST_H_

#include <iostream>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <random>
using namespace std;

typedef struct node {

  node* next;
  node* prev;
  node* up;
  node* down;
  int data;
  node(int k) {
    next = nullptr;
    up = nullptr;
    down = nullptr;
    data = 0;
  }

} node_t;

class Skiplist {

 private:
  int height;
  node_t** head;
  node_t** end;
 public:
  Skiplist(int height) {
    this->head = new node_t*[height];
    this->end = new node_t*[height];
    for (int i = 0; i < height; ++i) {
      head[i] = new node(-std::numeric_limits<int>::max());
      end[i] = new node(std::numeric_limits<int>::max());
      head[i]->next = end[i];
    }
  }
  node_t* skipSearch(int k);
  void skipInsert(int k);
  void skipDelete(int k);
  int coinFlip();
};

void lInsert(node_t* list, int k);

#endif//INC_5008SKIPLIST__SKIPLIST_H_
