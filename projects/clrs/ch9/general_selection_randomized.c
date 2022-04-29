#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int *array;
	int size;
}Array;

Array *readArray(char **stream, int size)
{
	Array *array = malloc(sizeof(Array));
	array->array = malloc(size * sizeof(int));
	array->size = size;
	for(int i = 0; i < size; i++) array->array[i] = atoi(stream[i]);
	return array;
}

void printI(int *A, int size, const char intro[])
{
	if (intro[0]) printf("%s ", intro);
	printf("array:");
	for(int i = 0; i < size; i ++) printf(" %d", A[i]);
	printf("\n");
}

int partition(int *A, int p, int r, int pivot)
{
	// printf("partitioning...\n");
	// printI(A, r - p + 1, "prepartiton");
	int pivot_ind;
	int l = p - 1;
	for(int i = p; i <= r; i++){
		if(A[i] <= pivot){
			l++;
			int tmp = A[l];
			A[l] = A[i];
			A[i] = tmp;
			if (A[l] == pivot)
				pivot_ind = l;
		}
	}
	// printI(A, r - p + 1, "postpartiton1");
	if (A[l] != pivot) {
		A[pivot_ind] = A[l];
		A[l] = pivot;
	}
	// printI(A, r - p + 1, "postpartiton2");
	return l;
}

// int _selectK(int *A, int p, int r, int i)
// {
// 	int q = partition(A, p, r);
// 	int k = q - p + 1;
// 	if (k == i)
// 		return A[q];
// 	else if (k > i)
// 		return _selectK(A, p,  q - 1, i);
// 	else
// 		return _selectK(A, q + 1, r, i - k);
// }

void isort(int *A, int size)
{
	// printI(A, size, "isort()");
	if (size == 1) return;
	for(int i = 1; i < size; i++){
		int curr_value = A[i];
		int j;
		for(j = i - 1; j >= 0 && A[j] > curr_value; j--)
			A[j + 1] = A[j];
		A[j + 1] = curr_value;
	}
	// printI(A, size, "isort()");
}

int find_median(int *A, int size)
{
	if (!size) return -1;
	if (size == 1) return A[0];
	isort(A, size);
	if (size % 2) return A[size / 2];
	else return A[size / 2 - 1];
}

int find_pivot(int *A, int p, int r, int chunk_size)
{
	// printf("finding pivot...\n");
	int size = r - p + 1;
	int last_chunk_size = size % 5;
	int nmedians, median;
	int *medians;
	if (last_chunk_size) { nmedians = size / chunk_size + 1; }
	else { nmedians = size / chunk_size; };
	// printf("nmedians = %d\n", nmedians);
	medians = malloc(sizeof(int) * nmedians);
	for(int i = 0; i < nmedians - 1; i++)
		medians[i] = find_median(A + p + i * chunk_size, chunk_size);
	medians[nmedians - 1] = find_median(A + p + (nmedians - 1) * chunk_size, last_chunk_size ? last_chunk_size : 5);
	// printI(medians, nmedians, "medians");
	median = find_median(medians, nmedians);	
	// printf("median = %d\n", median);
	free(medians);
	return median;
}

int _selectK(int *A, int p, int r, int i, int chunk_size)
{
	if (p == r) return A[p];
	int pivot = find_pivot(A, p, r, chunk_size);
	int q = partition(A, p, r, pivot);	
	int k = q - p + 1;
	if (k == i) return A[q];
	else if (k > i) return _selectK(A, p, q - 1, i, chunk_size);
	else return _selectK(A, q + 1, r, i - k, chunk_size);
}


void selectK(char **stream)
{
	int k = atoi(stream[0]);
	int n = atoi(stream[1]);
	int chunk_size = 5;
	Array * array = readArray(stream + 2, n);
	printI(array->array, array->size, "");
	int key = _selectK(array->array, 0, array->size - 1, k, chunk_size);
	printf("%d-th smallest = %d\n", k, key);
	printI(array->array, array->size, "");
	free(array->array);
	free(array);
}


int main (int argc, char *argv[])
{
	if (argc < 4) return 0;
	if (argc < 3 + atoi(argv[2])) return 0;
	selectK(argv + 1);
	return 0;
}
