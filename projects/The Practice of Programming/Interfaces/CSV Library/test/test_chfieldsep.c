#include <stdio.h>
#include <stdlib.h>

#include "../src/multi_field-splitting/csv.h"

int main(int argc, char *argv[])
{
	char *line;
	int opt = strtol(argv[1], NULL, 10);
	// printf("%d\n", opt);
		char *fs = ",:.";
		if (chfieldsep(fs, MAPEACH) == -1) {
			printf("Failed to change field separators!\n");
			exit(1);
		}
	while ((line = csvgetline(stdin, opt)) != NULL) {
		int nfield = csvnfield();
		if (argv[2][0] == '1')
			printf("line with %d fields\n", nfield);
		for (int i = 0; i < nfield; ++i) {
			char *field = csvfield(i);
			if (argv[2][0] == '1')
				printf("filed[%d] = '%s'\n", i, field);
		}
	}
	return 0;
}
