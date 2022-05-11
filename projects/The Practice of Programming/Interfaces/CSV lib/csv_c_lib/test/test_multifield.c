#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../src/multi_field-splitting/csv.h"

int main(int argc, char *argv[])
{
	char *line;
	// printf("%d\n", opt);
	// bool PRINT_FLAG = (argv[2][0] == '1');
	while ((line = csvgetline(stdin, 0)) != NULL) {
		int nfield = csvnfield();
		// if (PRINT_FLAG)
		printf("line with %d fields\n", nfield);
		for (int i = 0; i < nfield; ++i) {
			// if (PRINT_FLAG)
			printf("field[%d] = '%s'\n", i, csvfield(i));
		}
	}
	return 0;
}
