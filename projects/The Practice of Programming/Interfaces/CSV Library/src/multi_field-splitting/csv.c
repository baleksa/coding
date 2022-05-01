#define _POSIX_C_SOURCE 200809L

#include "./csv.h"

#include <stdio.h>
#include <stdlib.h>
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

void set_split_type(splittype st)
{
	_st = st;
}

char *advanceq(char *p, bool splitit)
{
	int i, j;
	for (i = j = 0; p[j]; ++i, ++j) {
		if (p[j] == '"') {
			if (p[++j] != '"') {
				int n = strcspn(p + j, fieldsep);
				if (splitit)
					memmove(p + i, p + j, n);
				i += n;
				j += n;
				break;
			}
		}
		if (splitit)
			p[i] = p[j];
	}
	if (splitit)
		p[i] = '\0';
	return p + j;
}

int split_all()
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
			sepp = advanceq(++p, true);
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		sepp[0] = '\0';
		field[nfield++] = p;
		p = sepp + 1;
	} while (sepc == ',');
	nfield_valid = true;
	splitted = true;
	return nfield;
}

int split_upton(int n)
{
        // printf("split_upton(%d) start:\n", n);
	char sepc;
	char *p, *sepp;

	if (line[0] == '\0')
		return 0;

        // printf("split_upton(): pre strcpy line='%s'\n", line);
        // printf("split_upton(): pre strcpy sline='%s'\n", sline);

	if (nsplitted == 0) {
                // printf("split_upton(): line='%s'\n", line);
                // printf("CALLING SNPRINTF\n");
                snprintf(sline, maxline, "%s", line);
                currpos = sline;
                // printf("split_upton(): sline='%s'\n", sline);
	}

        
        
	p = currpos;
        // printf("p = '%s'\n", p);
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
			sepp = advanceq(++p, true);
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		sepp[0] = '\0';
		field[nsplitted++] = p;
                // printf("field[%d]='%p'\n", nsplitted-1, (void*)p);
		p = sepp + 1;
	} while (sepc == ',' && nsplitted < n);
        currpos = p;
	if (sepc != ',') {
                if (!nfield_valid){
                        nfield_valid = splitted;
                        nfield_valid = true;
                }
		splitted = true;
	}
	return 0;
}

int split_onlyn(int n)
{
        return 0;
	char sepc;
	char *p, *sepp;
	int i;

	if (line[0] == '\0')
		return 0;

	if (nsplitted == 0) {
		strcpy(sline, line);
	}

	p = sline;

	i = 0;
	do {
		bool split_it = (i == n);

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
			sepp = advanceq(++p, split_it);
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		if (split_it) {
			sepp[0] = '\0';
			field[nfield++] = split_it ? p : NULL;
			++nsplitted;
		}
		p = sepp + 1;
		++i;
	} while (sepc == ',' && i < n);

	if (sepc != ',') {
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
			sepp = advanceq(++p, false);
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		p = sepp + 1;
		nfield++;
	} while (sepc == ',');

	nfield_valid = true;
	return 0;
}

char *csvgetline(FILE *fin)
{
	char c;
	int i;

	nfield = 0;
	nsplitted = 0;
	splitted = false;
	nfield_valid = false;

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

	if (_st == GREEDY) {
		if (split_all() == NOMEM) {
			reset();
			return NULL;
		}
	}

	return (c == EOF && i == 0) ? NULL : line;
}

char *csvfield(int n)
{

	if (n < 0)
		return NULL;
	switch (_st) {
	case GREEDY:
		if (n >= nfield)
			return NULL;
		break;
	case LAZY_ALL:
		if (!splitted)
			split_all();
		if (nfield_valid && n >= nfield)
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
			split_upton(n);
                }
		break;
	case LAZY_ONLY_N:
		split_onlyn(n);
		break;
        };
        // printf("csvfield() ent: return %p\n", (void *)field[n]);
	return field[n];
}

int csvnfield()
{
	switch (_st) {
	case GREEDY:
		break;
	case LAZY_ALL:
		if (!nfield_valid)
			calculate_nfield();
		break;
	case LAZY_UP_TO_N:
		if (!nfield_valid)
			calculate_nfield();
		break;
	case LAZY_ONLY_N:
		if (!nfield_valid)
			calculate_nfield();
		break;
	};

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
