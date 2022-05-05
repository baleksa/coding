#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./csv.h"

enum { NOMEM = -2 };
static char *line = NULL;
static char *sline = NULL;
// static char *currpos = NULL;
static int maxline = 0;
static char **field = NULL;
static int maxfield = 0;
static int nfield = 0;
static int nsplitted = 0;
static bool splitted = false;
static bool nfield_valid = false;
static enum splittype _spt = GREEDY;
static char *fieldsep = ",";
static int fieldseplen = 1;
static int maxfieldsep = 2;
static enum septype _sept = STRING;

char *csvgetline(FILE *f, enum splittype st);
char *csvfield(int n);
int csvnfield(void);
int chfieldsep(const char *sep, enum septype st);
static bool endline(char c, FILE *fin);
static void reset(void);
static char *advanceq(char *p, bool split_it, int n);
static bool issep(char c, int n);
static int split_all(void);
static int split_upton(int n);
static int split_onlyn(int n);
static int calculate_nfield(void);
static int resize_field(void);
static int init_storage(int size);
static void init_variables_for_next_line(void);

int resize_field(void)
{
	maxfield *= 2;
	char **newfield = (char **)malloc(maxfield * sizeof(field[0]));
	if (newfield == NULL)
		return NOMEM;
	field = newfield;
	return 0;
}

int chfieldsep(const char *sep, enum septype st)
{
	if (st < STRING || st > REGEXP)
		return -1;
	if (strchr(sep, '"') != NULL)
		return -1;
	int new_seplen = strlen(sep);
	if (new_seplen + 1 >= maxfieldsep) {
		maxfieldsep *= 2;
		char *new_fsep = (char *)malloc(maxfieldsep);
		if (new_fsep == NULL)
			return -1;
		fieldsep = new_fsep;
	}

	strcpy(fieldsep, sep);
	fieldseplen = new_seplen;
	_sept = st;
	return 0;
}

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

int strnsepn(char *p, int n)
{
	if (_sept == STRING)
		return strcspn(p, fieldsep);
	char tmpsep[2];
        tmpsep[0] = fieldsep[n];
        tmpsep[1] = '\0';
        return strcspn(p, tmpsep);
}

char *advanceq(char *p, bool split_it, int n)
{
	int i, j;
	for (i = j = 0; p[j]; ++i, ++j) {
		if (p[j] == '"') {
			if (p[++j] != '"') {
				int nch;
                                if (_sept == STRING)
                                        nch = strnsepn(p+j, n);
                                else
                                        nch = strcspn(p + j, fieldsep);

				if (split_it)
					memmove(p + i, p + j, nch);
				i += nch;
				j += nch;
				break;
			}
		}
		if (split_it)
			p[i] = p[j];
	}
	if (split_it)
		p[i] = '\0';
	return p + j;
}

bool issep(char c, int n)
{
	if (_sept == STRING)
		return strchr(fieldsep, c) != NULL;
	else if (_sept == MAPEACH)
		return c == fieldsep[n % fieldseplen];

	return 0;
}

int split_all(void)
{
	if (line[0] == '\0')
		return 0;

	nfield = 0;
	strcpy(sline, line);

	char *p = sline;
	char sepc;
	do {
		if (nfield >= maxfield) {
			if (resize_field() == NOMEM)
				return NOMEM;
		}

		char *sepp;
		if (*p == '"')
			sepp = advanceq(++p, true, nfield);
		else
			sepp = p + strnsepn(p, nfield);
		sepc = sepp[0];
		sepp[0] = '\0';
		field[nfield++] = p;
		p = sepp + 1;
	} while (issep(sepc, nfield - 1));
	nfield_valid = true;
	splitted = true;
	return nfield;
}

int split_upton(int n)
{
	// printf("split_upton(%d) start:\n", n);

	if (line[0] == '\0')
		return 0;

	// printf("split_upton(): pre strcpy line='%s'\n", line);
	// printf("split_upton(): pre strcpy sline='%s'\n", sline);

	static char *currpos;
	if (nsplitted == 0) {
		// printf("split_upton(): line='%s'\n", line);
		// printf("CALLING SNPRINTF\n");
		snprintf(sline, maxline, "%s", line);
		currpos = sline;
		// printf("split_upton(): sline='%s'\n", sline);
	}

	char *p = currpos;
	// printf("p = '%s'\n", p);
	char sepc;
	do {
		if (n >= maxfield) {
			if (resize_field() == NOMEM)
				return NOMEM;
		}

		char *sepp;
		if (*p == '"')
			sepp = advanceq(++p, true, nsplitted);
		else
			sepp = p + strnsepn(p, nsplitted);
		sepc = sepp[0];
		sepp[0] = '\0';
		field[nsplitted++] = p;
		// printf("field[%d]='%p'\n", nsplitted-1, (void*)p);
		p = sepp + 1;
	} while (nsplitted <= n && issep(sepc, nsplitted - 1));
	currpos = p;
	if (!issep(sepc, nsplitted - 1)) {
		if (!nfield_valid) {
			nfield_valid = splitted;
			nfield_valid = true;
		}
		splitted = true;
	}
	return 0;
}

int split_onlyn(int n)
{
	if (line[0] == '\0')
		return 0;

	// if (field[n] != NULL)
	// 	return 0;

	if (nsplitted == 0)
		strcpy(sline, line);
	// printf("split_onlyn(): line = '%s'\n", line);
	// printf("split_onlyn(): sline = '%s'\n", sline);
	char *tmp_line = (char *)malloc(maxline);
	if (tmp_line == NULL)
		return NOMEM;
	strcpy(tmp_line, line);

	int i = 0; /* counter for do while loop */
	char sepc; /* separator after current field */
	char *p = tmp_line; /* current position in sline */
	do {
		bool split_it = (i == n);

		if (n >= maxfield) {
			if (resize_field() == NOMEM)
				return NOMEM;
		}

		char *sepp;
		if (*p == '"')
			sepp = advanceq(++p, split_it, i);
		else
			sepp = p + strnsepn(p, i);
		sepc = sepp[0];
		if (split_it) {
			sepp[0] = '\0';
			++nsplitted;
			field[i] = p;
			memmove(sline + (p - tmp_line), p, (sepp - p) + 1);
		}
		p = sepp + 1;
		++i;
	} while (issep(sepc, i - 1));

	if (!issep(sepc, i - 1)) {
		nfield = i;
		nfield_valid = true;
	}
	return 0;
}

int calculate_nfield(void)
{
	char sepc;
	char *p, *sepp;

	if (line[0] == '\0')
		return 0;

	// strcpy(sline, line);

	p = line;

	do {
		if (*p == '"')
			sepp = advanceq(++p, false, nfield);
		else
			sepp = p + strnsepn(p, nfield);
		sepc = sepp[0];
		p = sepp + 1;
		nfield++;
	} while (issep(sepc, nfield - 1));

	nfield_valid = true;
	return 0;
}

int init_storage(int size)
{
	if (size == 0)
		size = 10;
	maxline = maxfield = size;
	line = (char *)malloc(maxline);
	sline = (char *)malloc(maxline);
	field = (char **)malloc(maxfield * sizeof(field[0]));
	if (line == NULL || sline == NULL || field == NULL) {
		reset();
		return NOMEM;
	}
	return 0;
}

void init_variables_for_next_line(void)
{
	nfield = 0;
	nsplitted = 0;
	splitted = false;
	nfield_valid = false;
}

char *csvgetline(FILE *fin, enum splittype st)
{
	if (st < GREEDY || st > LAZY_ONLY_N)
		return NULL;

	init_variables_for_next_line();
	_spt = st;

	if (!line) {
		if (init_storage(0) == NOMEM)
			return NULL;
	}

	char c;
	int i;
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

	if (_spt == GREEDY) {
		if (split_all() == NOMEM) {
			reset();
			return NULL;
		}
	}

	return (c == EOF && i == 0) ? NULL : line;
}

/* csvfield: returns pointer to n-th field of the line .csv file */
char *csvfield(int n)
{
	if (n < 0)
		return NULL;
	switch (_spt) {
	case GREEDY:
		if (n >= nfield)
			return NULL;
		break;
	case LAZY_ALL:
		if (!splitted)
			if (split_all() == NOMEM)
				return NULL;
		if (n >= nfield)
			return NULL;
		break;
	case LAZY_UP_TO_N:
		// printf("_st==LAZY_UP_TO_N:\n");
		// printf("if (nfield_valid && n >= nfield): nfield_valid=%d n=%d nfield=%d\n", nfield_valid, n, nfield);
		if (nfield_valid && n >= nfield) {
			// printf("NOOO!\n");
			return NULL;
		}
		// printf("if (!splitted && n >= nsplitted): splitted=%d n=%d nsplitted=%d\n", splitted, n, nsplitted);
		if (!splitted && n >= nsplitted) {
			// printf("YESSS!\n");
			if (split_upton(n) == NOMEM)
				return NULL;
		}
		break;
	case LAZY_ONLY_N:
		// printf("csvnfield(): _st = LAZY_ONLY_N\n");
		if (split_onlyn(n) == NOMEM)
			return NULL;
		break;
	};
	// printf("csvfield() ent: return %p\n", (void *)field[n]);
	return field[n];
}

int csvnfield()
{
	// nfield may not be valid if splitting isn't greedy
	if (_spt != GREEDY) {
		if (!nfield_valid)
			calculate_nfield();
	}

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
// }
// int split_manually()
// {
// 	bool infield, inquotes;
// 	int slinepos, fstart;
//
// 	nfield = 0;
//
// 	if (line[0] == '\0')
// 		return 0;
//
// 	slinepos = 0;
// 	fstart = 0;
// 	infield = inquotes = false;
// 	for (int i = 0; i < maxline; i++) {
// 		char c = line[i];
// 		if (c == ',') {
// 			if (nfield >= maxfield) {
// 				maxfield *= 2;
// 				char **newfield = realloc(
// 					field, maxfield * sizeof(field[0]));
// 				if (newfield == NULL) {
// 					reset();
// 					return NOMEM;
// 				}
// 				field = newfield;
// 			}
//
// 			if (inquotes) {
// 				sline[slinepos] = c;
// 			} else {
// 				sline[slinepos] = '\0';
// 				if (infield) {
// 					field[nfield++] = sline + fstart;
// 					infield = false;
// 				} else {
// 					field[nfield++] = sline + slinepos;
// 				}
// 			}
// 			slinepos++;
// 		} else if (c == '"') {
// 			if (inquotes) {
// 				if (line[i + 1] == '"') {
// 					sline[slinepos++] = '"';
// 					i++;
// 				} else {
// 					inquotes = false;
// 				}
// 			} else {
// 				inquotes = true;
// 			}
// 		} else if (c == '\0') {
// 			if (nfield >= maxfield) {
// 				maxfield *= 2;
// 				char **newfield = realloc(
// 					field, maxfield * sizeof(field[0]));
// 				if (newfield == NULL) {
// 					return NOMEM;
// 				}
// 				field = newfield;
// 			}
// 			if (infield) {
// 				sline[slinepos++] = '\0';
// 				field[nfield++] = sline + fstart;
// 				infield = false;
// 			} else {
// 				sline[slinepos] = '\0';
// 				field[nfield++] = sline + slinepos;
// 				slinepos++;
// 			}
// 			break;
// 		} else {
// 			sline[slinepos] = c;
// 			if (!infield) {
// 				fstart = slinepos;
// 				infield = true;
// 			}
// 			slinepos++;
// 		}
// 	}
// 	return nfield;
// }
