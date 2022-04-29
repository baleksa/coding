#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
	int a;
	char s[20];
}Test;

void prints(Test *t)
{
	printf("a:%d msg:%s\n", t->a, t->s);	
}

void * f(void *ptr)
{
	if(ptr)
		return *(Test**)ptr;
	return NULL;
}

int main (int argc, char *argv[])
{
	srand(time(0));
	Stack *s = stack(sizeof(Test *), 100);
	int cycles = 1000;
	for(int i = 0; i < cycles; i++){
		Test *t = malloc(sizeof(Test));
		t->a = rand();
		char a[20] = "test";
		a[5] = '\0';
		a[4] = '0' + i % 10;
		strcpy(t->s, a);
		push(s, &t);
	}
	for(int i = 0; i < cycles; i++){
		Test *t = pop(s, f);
		prints(t);
		free(t);
	}
	pop(s, f);
	delStack(s);
	return 0;
}
