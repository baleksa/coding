#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// TODO: write this in C retarde

// #define CHAR_RANGE ('z' - 'A' + 1)
#define CHAR_RANGE ('z' - 'a' + 1)

#define MAX_LEN 100

void printS(char **A, int start, int size, const char *name)
{
	printf("%s:", name);
	for(int i = start; i < size; i++) printf(" %s", A[i]);
	printf("\n");
}


void printI(int* A, int start, int size, const char *name)
{
	printf("%s:", name);
	for(int i = start; i < size; i++) printf(" %d", A[i]);
	printf("\n");
}

void sort_size(char **words, int size, int max_len, char **tmp)
{
	int count[MAX_LEN];
	for(int i = 0; i <= max_len; i++) count[i] = 0;
	for(int i = 0; i < size; i++) count[strlen(words[i])]++;
	for(int i = 1; i <= max_len; i++) count[i] += count[i - 1];
	// printI(count, 0, max_len, "count");
	for(int i = 0; i < size; i++) tmp[i] = words[i];
	// printS(tmp, 0, size, "tmp");
	for(int i = size - 1; i >= 0; i--){
		int index = count[strlen(tmp[i])] - 1;
		words[index] = tmp[i];
		count[strlen(tmp[i])] -= 1;
	}
	// printS(words, 0, size, "words");

}

void countSort(char **words, int start, int end, int j, char **tmp)
{
	// printS(words, start, end, "words");
	// printf("start: %d end: %d char_pas: %d \n", start, end, j);
	int count[CHAR_RANGE];
	for(int i = 0; i < CHAR_RANGE; i++) count[i] = 0;
	// for(int i = start; i < end; i++) count[words[i][j] - 'A']++;
	for(int i = start; i < end; i++) count[tolower(words[i][j]) - 'a']++;
	for(int i = 1; i < CHAR_RANGE; i++) count[i] += count[i - 1];
	// printI(count, 0, CHAR_RANGE, "countChar");
	for(int i = start; i < end; i++) tmp[i] = words[i];
	for(int i = end - 1; i >= start; i--){
		// int index = count[tmp[i][j] - 'A'] - 1;
		int index = count[tolower(tmp[i][j]) - 'a'] - 1;
		words[start + index] = tmp[i];
		// count[tmp[i][j] - 'A'] -= 1;
		count[tolower(tmp[i][j]) - 'a'] -= 1;
	}	
}

void cSort(char **words, int size, int *indices, char **tmp)
{
	int max_len = 0,
		len = 0;
	for(int i = 0; i < size; i++) if (strlen(words[i]) > max_len) max_len = strlen(words[i]);
	sort_size(words, size, max_len, tmp);
	for(int i = 0; i <= max_len; indices[i++] = 0);
	for(int i = 0; i < size; i++) indices[strlen(words[i])]++;
	for(int i = 1; i <= max_len; i++) indices[i] += indices[i - 1];
	for(int i = max_len - 1; i >= 0; i--)
		countSort(words, indices[i], size, i, tmp);

}

int main(int argc, char *argv[]) {
	char **tmp = malloc(argc * sizeof(char*));
	for(int i = 1; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");

	int indices[200];
	cSort(argv + 1, argc - 1, indices, tmp);

	for(int i = 1; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");


	return 0;
}
