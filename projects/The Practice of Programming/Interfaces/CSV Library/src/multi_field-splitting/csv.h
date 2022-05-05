/* csv.h: interface for csv library */
#include <stdio.h>

enum splittype { GREEDY = 0, LAZY_ALL = 1, LAZY_UP_TO_N = 2, LAZY_ONLY_N = 3 };
enum septype { STRING = 0, MAPEACH = 1, REGEXP = 2 };

extern char *csvgetline(FILE *f, enum splittype st);
extern char *csvfield(int n);
extern int csvnfield(void);
extern int chfieldsep(const char *sepn, enum septype st);
