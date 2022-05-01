CFLAGS=-Wall -g3 -Werror -pedantic -std=c11
srcdir=./src

all: test_multifield

run: test_multifield
	./test_multifield

test: test_multifield do_test.sh
	./do_test.sh

test_multifield: ${srcdir}/test/performance/test_multifield.c libcsv.a
	clang ${CFLAGS} ${srcdir}/test/performance/test_multifield.c -L. -lcsv -o test_multifield

libcsv.a: ${srcdir}/multi_field-splitting/csv.c ${srcdir}/multi_field-splitting/csv.h
	clang ${CFLAGS} -c ${srcdir}/multi_field-splitting/csv.c -ocsv.o
	ar -rcs  libcsv.a csv.o

clean:
	rm *.o libcsv.a test_multifield

.PHONY: clean all test
