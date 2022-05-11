#include <stdio.h>

#include "../src/csv.h"

int main(int argc, char *argv[])
{
	FILE *test = fopen(
		"/home/baleksa/coding/projects/The Practice of Programming/Interfaces/CSV lib/data/csv/test.csv",
		"r");
	if (test == NULL) {
		perror("fopen failed!");
		return -1;
	}

	struct csv_parser *par = csvnew();
	struct csv_parser *par2 = csvnew();

	while (1) {
		char *line = csvgetline(par, stdin);
		char *line2 = csvgetline(par2, test);
		if (line != NULL) {
			int nfield = csvnfield(par);
			printf("line with %d fields:\n", nfield);
			for (int i = 0; i < nfield; i++)
				printf("\tfield[%d] = '%s'\n", i,
				       csvfield(par, i));
		}

		if (line2 != NULL) {
			int nfield2 = csvnfield(par2);
			printf("line with %d fields:\n", nfield2);
			for (int i = 0; i < nfield2; i++)
				printf("\tfield[%d] = '%s'\n", i,
				       csvfield(par2, i));
		}
		if (line == NULL && line2 == NULL)
			break;
	}
	free_csv_parser(par);
	par = NULL;
	free_csv_parser(par2);
	par2 = NULL;
	return 0;
}
