#include <stdio.h>

int binaryS(int A[], int n, int key) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int mid = (r + l) / 2;
    if (A[mid] == key)
      return mid;
    if (A[mid] < key)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return -1;
}

int binaryBitWiseS(int A[], int n, int key) {
  int index, power;
  for (power = 1; power < n; power <<= 1)
    ;
  for (index = 0; power; power >>= 1) {
    if (index + power < n && A[index + power] <= key)
      index += power;
  }
  if (A[index] == key)
    return index;
  return -1;
}

int main(int argc, char *argv[]) {
  int A[] = {2, 3, 4, 5, 5, 5, 6, 7, 8, 9, 10};
  int key = 5;
  scanf("%d", &key);
  size_t n = sizeof(A) / sizeof(A[0]);
  int index = binaryBitWiseS(A, n, key);
  printf("A[%d] = %d\n", index, index == -1 ? 0 :A[index]);
  return 0;
}
