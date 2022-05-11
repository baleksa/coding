CC := clang
CFLAGS := -Wall -g3 -Werror -pedantic -std=c11
all: libcsv.a testlib

testlib: ./test/testlib.c libcsv.a
	${CC} ${CFLAGS} ./test/testlib.c -L./bin/static  -lcsv -otestlib

libcsv.a: ./src/csv.c ./src/csv.h
	${CC} ${CFLAGS} -c ./src/csv.c -o ./bin/static/csv.o
	ar rcs ./bin/static/libcsv.a ./bin/static/csv.o

clean:
	rm testlib ./bin/static/csv.o ./bin/static/libcsv.a
.PHONY:
	all clean

