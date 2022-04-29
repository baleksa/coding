#!/bin/awk -f
BEGIN { MAXGEN = 10000; NONWORD = "\n"; w1 = w2 = NONWORD}
{
    for (i = 1; i <= NF; i++) {
        statetab[w1, w2, ++nsuffix[w1, w2]] = $i
        w1 = w2
        w2 = $i
    }
}
END {
    statetab[w1, w2, ++nsuffix[w1, w2]] = NONWORD
    w1 = w2 = NONWORD
    for (i = 0; i < MAXGEN; i++) {
        r =  int(rand() * nsuffix[w1,w2]) + 1
        p = statetab[w1, w2, r]
        if (p == NONWORD)
            exit
        print p
        w1 = w2
        w2 = p
    }
}
