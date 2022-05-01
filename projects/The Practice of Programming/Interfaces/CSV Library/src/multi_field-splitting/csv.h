/* csv.h: interface for csv library */
#include <stdio.h>
#include <stdbool.h>

typedef enum { GREEDY = 0, LAZY_ALL = 1, LAZY_UP_TO_N = 2, LAZY_ONLY_N = 4 } splittype;
enum { NOMEM = -2 };

extern char *csvgetline(FILE *f);
extern char *csvfield(int n);
extern int csvnfield(void);
extern void set_split_type(splittype st);


static char *line      = NULL;
static char *sline     = NULL;
static char *currpos = NULL;
static int maxline     = 0;
static char **field    = NULL;
static int maxfield    = 0;
static int nfield      = 0;
static int nsplitted   = 0;
static bool splitted = false;
static bool nfield_valid = false;
static splittype _st   = GREEDY;
static char fieldsep[] = ",";
