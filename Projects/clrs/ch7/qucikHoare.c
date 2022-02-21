#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LEN(x)                                                                 \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))
#define N 1000000
#define MAX 1000
#define PRINT_LEN 30
#define swap(x, y)                                                             \
  do {                                                                         \
    unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1];  \
    memcpy(swap_temp, &y, sizeof(x));                                          \
    memcpy(&y, &x, sizeof(x));                                                 \
    memcpy(&x, swap_temp, sizeof(x));                                          \
  } while (0)

int hoarePartition(int A[], int p, int q) {
  int x = A[p], i = p - 1, j = q + 1;
  while (true) {
    do {
      j--;
    } while (A[j] > x);
    do {
      i++;
    } while (A[i] < x);
    if (i < j)
      swap(A[i], A[j]);
    else
      return j;
  }
}
void quickHoare(int A[], int p, int q) {
  if (p < q) {
    int j = hoarePartition(A, p, q);
    quickHoare(A, p, j);
    quickHoare(A, j + 2, q);
  }
}
bool isSorted(int A[], int n) {
  for (int i = 1; i < n; i++) {
    if (A[i - 1] > A[i])
      return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  int A[N];
  int n = N;
  for (int i = 0; i < n; i++) {
    A[i] = rand() % (MAX + 1);
  }
  int tmp_len = 10;
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  quickHoare(A, 0, n - 1);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  int step = (n - 1) / PRINT_LEN;
  printf("%s%s in %g sec\n", isSorted(A, n) ? "Not " : "", "Sorted",
         cpu_time_used);
  for (int i = 0; i < PRINT_LEN; i++) {
    printf("%d ", A[i * step]);
  }
  printf("\n");

  return 0;
}
