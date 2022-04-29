#include <string.h>

#include "prototype.h"


char buf[BUF_SIZE];
char *field[NFIELD];

int csvgetline(FILE *in)
{
	int nfield;
	char *p, *q;

	if (!fgets(buf, BUF_SIZE, in))
		return -1;

	nfield = 0;
	for (q = buf; (p = strtok(q, ",\n\r")); q = NULL) {
		field[nfield++] = unquote(p);
	}

        return nfield;
}

char *unquote(char *p)
{
	if (!p)
		return NULL;
	if (p[0] == '"') {
		size_t len = strlen(p);
		if (p[len - 1] == '"') {
			p[len - 1] = '\0';
		}
		p++;
	}
	return p;
}
