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
  sl->skipSearch(98);
  sl->skipDelete(98);
  sl->skipSearch(98);
  return 0;
}
