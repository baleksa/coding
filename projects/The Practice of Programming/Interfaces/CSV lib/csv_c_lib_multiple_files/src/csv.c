#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./csv.h"

#define STATE(csv) ((struct csv_parser_state *)((csv)->state))

enum { NOMEM = -2 };

struct csv_parser_state {
	char *line;
	char *sline;
	int maxline;
	char **field;
	int maxfield;
	int nfield;
	char *fieldsep;
};

static int split(struct csv_parser *par);
static char *advanceq(struct csv_parser *par, char *p);
static void reset(struct csv_parser *par);
static bool endline(char c, FILE *fin);

struct csv_parser *csvnew();

struct csv_parser *csvnew()
{
	struct csv_parser *newparser =
		(struct csv_parser *)malloc(sizeof(struct csv_parser));
	if (newparser == NULL)
		return NULL;

	newparser->state = (struct csv_parser_state *)malloc(
		sizeof(struct csv_parser_state));
	if (newparser->state == NULL) {
		free(newparser);
		return NULL;
	}

	STATE(newparser)->line = NULL;
	STATE(newparser)->sline = NULL;
	STATE(newparser)->maxline = 0;
	STATE(newparser)->field = NULL;
	STATE(newparser)->maxfield = STATE(newparser)->nfield = 0;
	STATE(newparser)->fieldsep = (char *)malloc(2);
	STATE(newparser)->fieldsep[0] = ',';
	STATE(newparser)->fieldsep[1] = '\0';

	return newparser;
}

static bool endline(char c, FILE *fin)
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

static void reset(struct csv_parser *par)
{
	free(STATE(par)->line);
	STATE(par)->line = NULL;
	free(STATE(par)->sline);
	STATE(par)->sline = NULL;
	STATE(par)->maxline = 0;
	free(STATE(par)->field);
	STATE(par)->field = NULL;
	STATE(par)->maxfield = STATE(par)->nfield = 0;
}

static char *advanceq(struct csv_parser *par, char *p)
{
	int i, j;
	for (i = j = 0; p[j]; ++i, ++j) {
		if (p[j] == '"') {
			if (p[++j] != '"') {
				int n = strcspn(p + j, STATE(par)->fieldsep);
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

int split(struct csv_parser *par)
{
	char sepc;
	char *p, *sepp;

	if (STATE(par)->line[0] == '\0')
		return 0;

	STATE(par)->nfield = 0;
	strcpy(STATE(par)->sline, STATE(par)->line);

	p = STATE(par)->sline;

	do {
		if (STATE(par)->nfield >= STATE(par)->maxfield) {
			STATE(par)->maxfield *= 2;
			char **newfield =
				realloc(STATE(par)->field,
					STATE(par)->maxfield *
						sizeof(STATE(par)->field[0]));
			if (newfield == NULL) {
				return NOMEM;
			}
			STATE(par)->field = newfield;
		}

		if (*p == '"')
			sepp = advanceq(par, ++p);
		else
			sepp = p + strcspn(p, STATE(par)->fieldsep);
		sepc = sepp[0];
		sepp[0] = '\0';
		STATE(par)->field[STATE(par)->nfield++] = p;
		p = sepp + 1;
	} while (sepc == ',');

	return STATE(par)->nfield;
}

char *csvgetline(struct csv_parser *par, FILE *fin)
{
	char c;
	int i;

	if (!STATE(par)->line) {
		STATE(par)->maxline = STATE(par)->maxfield = 1;
		STATE(par)->line = (char *)malloc(STATE(par)->maxline);
		STATE(par)->sline = (char *)malloc(STATE(par)->maxline);
		STATE(par)->field = (char **)malloc(
			STATE(par)->maxfield * sizeof(STATE(par)->field[0]));
		if (STATE(par)->line == NULL || STATE(par)->sline == NULL ||
		    STATE(par)->field == NULL) {
			reset(par);
			return NULL;
		}
	}

	for (i = 0; (c = getc(fin)) != EOF && !endline(c, fin); ++i) {
		if (i >= STATE(par)->maxline - 1) {
			STATE(par)->maxline *= 2;
			char *nline =
				realloc(STATE(par)->line, STATE(par)->maxline);
			char *nsline =
				realloc(STATE(par)->sline, STATE(par)->maxline);
			if (STATE(par)->line == NULL ||
			    STATE(par)->sline == NULL) {
				reset(par);
				return NULL;
			}
			STATE(par)->line = nline;
			STATE(par)->sline = nsline;
		}
		STATE(par)->line[i] = c;
	}
	STATE(par)->line[i] = '\0';

	if (split(par) == NOMEM) {
		reset(par);
		return NULL;
	}

	return (c == EOF && i == 0) ? NULL : STATE(par)->line;
}

char *csvfield(struct csv_parser *par, int n)
{
	if (n < 0 || n >= STATE(par)->nfield)
		return NULL;
	return STATE(par)->field[n];
}

int csvnfield(struct csv_parser *par)
{
	return STATE(par)->nfield;
}

void free_csv_parser(struct csv_parser *par)
{
	free(STATE(par)->line);
	free(STATE(par)->sline);
	free(STATE(par)->field);
	free(STATE(par)->fieldsep);
	free(par->state);
	free(par);
}
