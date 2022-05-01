CFLAGS := -Wall -g3 -Werror -pedantic -std=c11
SRCDIR := ./src
MULTILIBDIR := ./src/multi_field-splitting
MULTILIBSRC := ${MULTILIBDIR}/csv.c

all: test_multifield

run: test_multifield
	./test_multifield

# test: test_multifield do_test.sh
# 	./do_test.sh

test_multifield: ${SRCDIR}/test/performance/test_multifield.c libcsv.a
	clang ${CFLAGS} ${SRCDIR}/test/performance/test_multifield.c -L. -lcsv -o test_multifield

libcsv.a: ${MULTILIBDIR}/csv.c ${MULTILIBDIR}/csv.h
	clang ${CFLAGS} -c ${MULTILIBDIR}/csv.c -ocsv.o
	ar -rcs  libcsv.a csv.o

clean:
	rm *.o libcsv.a test_multifield

.PHONY: clean all test
