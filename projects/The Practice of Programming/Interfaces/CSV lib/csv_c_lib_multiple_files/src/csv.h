/* csv.h: interface for csv library */
#ifndef CSV_H
#define CSV_H
#include <stdio.h>

struct csv_parser {
	void *state;
};

extern struct csv_parser *csvnew();
extern char *csvgetline(struct csv_parser *, FILE *);
extern char *csvfield(struct csv_parser *, int);
extern int csvnfield(struct csv_parser *);
extern void free_csv_parser(struct csv_parser *);
#endif /* CSV_H */
