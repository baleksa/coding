#define _POSIX_C_SOURCE 200809L

#include "./csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool endline(char c, FILE *fin)
{
	bool eol;

	eol = (c == '\n' || c == '\r');
	if (c == '\r') {
		c = getc(fin);
		if (c != '\n' && c != EOF)
			ungetc(c, fin);
	}
	return eol;
}

void reset(void)
{
	free(line);
	line = NULL;
	free(sline);
	sline = NULL;
	maxline = 0;
	free(field);
	field = NULL;
	maxfield = nfield = 0;
}

char *advanceq(char *p)
{
	int i, j;
	for (i = j = 0; p[j]; ++i, ++j) {
		if (p[j] == '"') {
			if (p[++j] != '"') {
				int n = strcspn(p + j, fieldsep);
				memmove(p + i, p + j, n);
				i += n;
				j += n;
				break;
			}
		}
		p[i] = p[j];
	}
	p[i] = '\0';
	return p + j;
}

int split()
{
	char sepc;
	char *p, *sepp;

	if (line[0] == '\0')
		return 0;

	nfield = 0;
	strcpy(sline, line);

	p = sline;

	do {
		if (nfield >= maxfield) {
			maxfield *= 2;
			char **newfield =
				realloc(field, maxfield * sizeof(field[0]));
			if (newfield == NULL) {
				return NOMEM;
			}
			field = newfield;
		}

		if (*p == '"')
			sepp = advanceq(++p);
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		sepp[0] = '\0';
		field[nfield++] = p;
		p = sepp + 1;
	} while (sepc == ',');

	return nfield;
}

char *csvgetline(FILE *fin)
{
	char c;
	int i;

	if (!line) {
		maxline = maxfield = 1;
		line = (char *)malloc(maxline);
		sline = (char *)malloc(maxline);
		field = (char **)malloc(maxfield * sizeof(field[0]));
		if (line == NULL || sline == NULL || field == NULL) {
			reset();
			return NULL;
		}
	}

	for (i = 0; (c = getc(fin)) != EOF && !endline(c, fin); ++i) {
		if (i >= maxline - 1) {
			maxline *= 2;
			char *nline = realloc(line, maxline);
			char *nsline = realloc(sline, maxline);
			if (line == NULL || sline == NULL) {
				reset();
				return NULL;
			}
			line = nline;
			sline = nsline;
		}
		line[i] = c;
	}
	line[i] = '\0';

	if (split() == NOMEM) {
		reset();
		return NULL;
	}

	return (c == EOF && i == 0) ? NULL : line;
}

char *csvfield(int n)
{
	if (n < 0 || n >= nfield)
		return NULL;
	return field[n];
}

int csvnfield()
{
	return nfield;
}

// char *csvgetline_builtin(FILE *fin) {
// 	size_t line_bsize = 0;
//
// 	maxline = getline(&line, &line_bsize, fin);
// 	if (maxline == -1)
// 		reset();
// 	return NULL;
// 	if (line[maxline - 1] == '\n')
// 		line[--maxline] = '\0';
// 	if (split_manually() == NOMEM) {
// 		reset();
// 		return NULL;
// 	}
// 	return (maxline == 0 || (maxline == 1 && line[0] == '\n')) ? NULL :
// 									   line;
int split_manually()
{
	bool infield, inquotes;
	int slinepos, fstart;

	nfield = 0;

	if (line[0] == '\0')
		return 0;

	slinepos = 0;
	fstart = 0;
	infield = inquotes = false;
	for (int i = 0; i < maxline; i++) {
		char c = line[i];
		if (c == ',') {
			if (nfield >= maxfield) {
				maxfield *= 2;
				char **newfield = realloc(
					field, maxfield * sizeof(field[0]));
				if (newfield == NULL) {
					reset();
					return NOMEM;
				}
				field = newfield;
			}

			if (inquotes) {
				sline[slinepos] = c;
			} else {
				sline[slinepos] = '\0';
				if (infield) {
					field[nfield++] = sline + fstart;
					infield = false;
				} else {
					field[nfield++] = sline + slinepos;
				}
			}
			slinepos++;
		} else if (c == '"') {
			if (inquotes) {
				if (line[i + 1] == '"') {
					sline[slinepos++] = '"';
					i++;
				} else {
					inquotes = false;
				}
			} else {
				inquotes = true;
			}
		} else if (c == '\0') {
			if (nfield >= maxfield) {
				maxfield *= 2;
				char **newfield = realloc(
					field, maxfield * sizeof(field[0]));
				if (newfield == NULL) {
					return NOMEM;
				}
				field = newfield;
			}
			if (infield) {
				sline[slinepos++] = '\0';
				field[nfield++] = sline + fstart;
				infield = false;
			} else {
				sline[slinepos] = '\0';
				field[nfield++] = sline + slinepos;
				slinepos++;
			}
			break;
		} else {
			sline[slinepos] = c;
			if (!infield) {
				fstart = slinepos;
				infield = true;
			}
			slinepos++;
		}
	}
	return nfield;
}
// }
