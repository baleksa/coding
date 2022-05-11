/* csv.h: interface for csv library */
#include <stdio.h>

extern char *csvgetline(FILE *f);
extern char *csvfield(int n);
extern int csvnfield(void);

enum { NOMEM = -2 };

static char *line      = NULL;
static char *sline     = NULL;
static int maxline     = 0;
static char **field    = NULL;
static int maxfield   = 0;
static int nfield      = 0;
static char fieldsep[] = ",";
