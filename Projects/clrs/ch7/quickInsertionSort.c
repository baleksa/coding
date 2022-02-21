#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define K 500
#define swap(a, b)                                                             \
  do {                                                                         \
    float tmp = a;                                                             \
    a = b;                                                                     \
    b = tmp;                                                                   \
  } while (0)
void adaptedQuickSort(float[], int);
void quickInsertionSort(float[], int);
int partition(float[], int, int);
void insertionSort(float[], int);

void insertionSort(float A[], int n) {
  for (int i = 1; i < n; i++) {
    float tmp = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > tmp) {
      A[j + 1] = A[j];
      j--;
    }
    A[j + 1] = tmp;
  }
}

int partition(float A[], int p, int q) {
  int pivot = p + rand() % (q - p + 1);
  /* printf("%d %d %d\n", p, q, pivot); */
  swap(A[pivot], A[q]);
  int l = p - 1;
  for (int j = p; j < q; j++) {
    if (A[j] > A[q])
      continue;
    l++;
    swap(A[j], A[l]);
  }
  l++;
  swap(A[q], A[l]);
  return l;
}

void qSortK(float A[], int p, int q) {
  if (q - p + 1 > K) {
    int pivot = partition(A, p, q);
    qSortK(A, p, pivot - 1);
    qSortK(A, pivot + 1, q);
  }
}
void adaptedQuickSort(float A[], int n) {
  qSortK(A, 0, n - 1);
  insertionSort(A, n);
}

bool isSorted(float A[], int n) {
  for (int i = 1; i < n; i++)
    if (A[i] < A[i - 1])
      return false;
  return true;
}

#define LEN 4000
#define PRINT_LEN 25
int main(int argc, char *argv[]) {
  srand(time(0));
  float A[LEN];
  int n = (sizeof(A) / sizeof(A[0]));
  for (int i = 0; i < n; i++)
    A[i] = rand() % 1000;

  /* printf("%s\n", isSorted(A, n) ? "Good":"Bad"); */
  adaptedQuickSort(A, n);
  int jump = LEN / PRINT_LEN;
  for (int i = 0; i < PRINT_LEN; i++)
    printf("%.0f ", A[i * jump]);
  printf("\n");
  /* printf("%s\n", isSorted(A, n) ? "Good":"Bad"); */

  return 0;
}
