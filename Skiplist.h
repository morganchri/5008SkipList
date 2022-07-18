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
  node* down;
  int data;
  explicit node(int k) {
    next = nullptr;
    down = nullptr;
    data = k;
  }

} node_t;

class Skiplist {

 private:
  int height;
  node_t** head;
  node_t** end;
 public:
  explicit Skiplist() {
    this->height = 1;
    this->head = new node_t*[100];
    this->end = new node_t*[100];
    for (int i = 0; i < 100; ++i) {
      head[i] = new node(-std::numeric_limits<int>::max());
      end[i] = new node(std::numeric_limits<int>::max());
      head[i]->next = end[i];
      if (i != 0) {
        head[i]->down = head[i - 1];
        end[i]->down = end[i - 1];
      }
    }
  }
  node_t* skipSearch(int k);
  int findHeight(int k);
  void skipInsert(int k);
  void skipDelete(int k);
  static int coinFlip();
  void downSet(int i, int k);
};

void lInsert(node_t* list, int k);
int lDelete(node_t* list, int k);
node_t* lFind(node_t* list, int k);

#endif//INC_5008SKIPLIST__SKIPLIST_H_
