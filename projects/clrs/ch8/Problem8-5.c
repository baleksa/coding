#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Range {
	int start;
	int end;
};
typedef struct Range range;


range qSortStepPartition(int *array, int start, int end, int step)
{
	srand(time(NULL));
	int pivot_ind = start + step * (rand() % ((end - start) / step + 1));
	int pivot = array[pivot_ind];
	// printf("pivot: %d pivot_ind: %d\n", pivot, pivot_ind);
	// return (range){};
	int tmp = array[start]; array[start] = array[pivot_ind]; array[pivot_ind] = tmp;
	int p = start - step;
	int m = start;
	for(int i = start + step; i <= end; i += step){
		if (array[i] < pivot) {
			int tmp = array[i];
			array[i] = array[m + step];
			array[m + step] = pivot;
			array[p + step] = tmp;
			p = p + step;
			m = m + step;
		}
		else if (array[i] == pivot){
			array[i] = array[m + step];
			array[m + step] = pivot;
			m = m + step;
		}
	}

	return (range){.start = p + step, .end = m};
}


void qSortStep(int *array, int start, int end, int step)
{
	if(start + step > end || start < 0) return;
	range pivot = qSortStepPartition(array, start, end, step);
	// printf("range.start: %d range.end: %d\n", pivot.start, pivot.end);
	// printf("-1\n");
	// return;
	qSortStep(array, start, pivot.start - step, step);
	qSortStep(array, pivot.end + step, end, step);
}

void kSort(int *array, int n, int k)
{
	if (k >= n) return;
	for(int i = 0; i < k; i++) {
		// printf("step %d start:\n", i);
		qSortStep(array, i, n - 1, k);
		// printf("step %d end:\n", i);
		// return;
	}
}

bool chechKSorted(int *array, int n, int step)
{
	for(int i = 0; i < step; i++) {
		for (int j = i + step; j < n; j += step)
			if (array[j] < array[j - step]) {
				printf("a[%d]/%d >= a[%d]/%d\n", j - step, array[j - step], j, array[j]);
				return false;
			}
	}

	return true;
}

void kSortStdIn(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	int *array = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++) array[i] = atoi(argv[2 + i]);
	int k = atoi(argv[argc - 1]);
	printf("n: %d step: %d\n", n, k);
	printf("Array:"); for(int i = 0; i < n; i++) printf(" %d", array[i]); printf("\n");
	kSort(array, n, k);
	printf("Array:"); for(int i = 0; i < n; i++) printf(" %d", array[i]); printf("\n");
	printf("%s\n", chechKSorted(array, n, k) ? "OK" : "NOT OK");
	free(array);
}

int main (int argc, char *argv[])
{
	kSortStdIn(argc, argv);
	return 0;
}
