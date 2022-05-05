CFLAGS := -Wall -g3 -Werror -std=c99 -pedantic
SRCDIR := ./src
MULTILIBDIR := ./src/multi_field-splitting
MULTILIBSRC := ${MULTILIBDIR}/csv.c

all: test_multifield test_chfieldsep


test_chfieldsep: ./test/test_chfieldsep.c libcsv.a
	clang ${CFLAGS} ./test/test_chfieldsep.c -L. -lcsv -o test_chfieldsep

test_multifield: ./test/test_multifield.c libcsv.a
	clang ${CFLAGS} ./test/test_multifield.c -L. -lcsv -o test_multifield

libcsv.a: ${MULTILIBDIR}/csv.c ${MULTILIBDIR}/csv.h
	clang ${CFLAGS} -c ${MULTILIBDIR}/csv.c -ocsv.o
	ar -rcs  libcsv.a csv.o

clean:
	rm *.o libcsv.a test_multifield

.PHONY: clean all test
