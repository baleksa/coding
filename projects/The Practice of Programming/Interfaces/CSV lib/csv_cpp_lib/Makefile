CPPFLAGS := -Wall -g3 -Werror -std=c++20 -pedantic
SRCDIR := ./src
TESTDIR := ./test
STATIC_LIB_DIR := ./bin/static

all: libcsv.a testcpp

testcpp: ${TESTDIR}/test.cpp libcsv.a
	clang++ ${CPPFLAGS} -otestcpp ${TESTDIR}/test.cpp -L${STATIC_LIB_DIR} -lcsv

libcsv.a: ${SRCDIR}/csv.cpp ${SRCDIR}/csv.hpp
	clang++ ${CPPFLAGS} -c ${SRCDIR}/csv.cpp -o ${STATIC_LIB_DIR}/csv.o
	ar -rcs  ${STATIC_LIB_DIR}/libcsv.a ${STATIC_LIB_DIR}/csv.o

clean:
	rm ${STATIC_LIB_DIR}/* ./test

.PHONY: clean all test
