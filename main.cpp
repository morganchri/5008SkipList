#include "Skiplist.cpp"

int main() {
  int nums[10] = {10, 34, 64, 45, 98, 34, 65, 23, 1, 87};
  auto* sl = new Skiplist();
  for (int num : nums) {
    sl->skipInsert(num);
  }
  sl->skipSearch(10);
  sl->skipDelete(10);
  sl->skipSearch(10);
  sl->skipSearch(64);
  sl->skipDelete(64);
  sl->skipSearch(64);
  return 0;
}
