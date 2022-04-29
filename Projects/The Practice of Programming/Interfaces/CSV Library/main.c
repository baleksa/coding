#include <stdio.h>

#include "./firsttry/prototype.h"

int main (int argc, char *argv[])
{
        int nf, j;

        j = 0;
        while((nf = csvgetline(stdin)) != -1) {
                j++;
                printf("%dth line:\n",j);
                for (int i = 0; i < nf; i++) {
                        printf("\tfield[%d]='%s'\n", i, field[i]);
                }
        }
        return 0;
}
