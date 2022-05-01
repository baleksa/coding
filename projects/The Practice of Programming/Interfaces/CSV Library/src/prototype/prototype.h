#include <stdio.h>
enum { BUF_SIZE = 200, NFIELD = 20 };
extern char buf[BUF_SIZE];
extern char *field[NFIELD];
int csvgetline(FILE *in);
char *unquote(char *p);
