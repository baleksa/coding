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

int partition(int *A, int p, int r)
{
	srand(time(0));
	int pivot_ind = p + rand() % (r - p + 1);
	int pivot = A[pivot_ind];
	int tmp = A[p]; A[p] = A[pivot_ind]; A[pivot_ind] = tmp;
	int l = p;
	for(int i = p + 1; i <= r; i++){
		if(A[i] <= pivot){
			l++;
			int tmp = A[l];
			A[l] = A[i];
			A[i] = tmp;
		}
	}
	A[p] = A[l];
	A[l] = pivot;
	return l;
}

int _selectK(int *A, int p, int r, int i)
{
	int q = partition(A, p, r);
	int k = q - p + 1;
	if (k == i)
		return A[q];
	else if (k > i)
		return _selectK(A, p,  q - 1, i);
	else
		return _selectK(A, q + 1, r, i - k);
}

int _selectK_iterative(int *A, int p, int r, int i)
{
	while(p < r){
		int q = partition(A, p, r);
		int k = q - p + 1;
		if (k == i) return A[q];
		else if (k < i) {
			p = q + 1;
			i -= k;
		} else {
			r = q - 1;
		}
	}
	return A[p];
}

void printI(int *A, int size)
{
	printf("Array:");
	for(int i = 0; i < size; i ++) printf(" %d", A[i]);
	printf("\n");
}

void selectK(char **stream)
{
	int k = atoi(stream[0]);
	int n = atoi(stream[1]);
	Array * array = readArray(stream + 2, n);
	int key = _selectK_iterative(array->array, 0, array->size - 1, k);
	printf("%d-th smallest = %d\n", k, key);
	printI(array->array, array->size);
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
