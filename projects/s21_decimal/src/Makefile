.PHONY: all test clean decimal run s21_decimal.a run

OS = $(shell uname)
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
LDFLAGS = -lcheck -lm -lsubunit
GCOVFLAGS = -fprofile-arcs -ftest-coverage
HDRS = s21_decimal.h
SRC = s21_basic.c s21_compare.c s21_conversions.c s21_other_functions.c arithmetic_functions/*.c
CC = gcc

all: clean s21_decimal.a

s21_decimal.a:
	@$(CC) $(CFLAGS) -c $(SRC)
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a

run:
	@$(CC) $(CFLAGS) $(SRC) -o s21_decimal
	@./s21_decimal

test:
	checkmk s21_decimal_tests.check > s21_decimal_tests.c
	$(CC) $(CFLAGS) s21_decimal_tests.c $(SRC) $(LDFLAGS) -o s21_decimal_tests
	./s21_decimal_tests

gcov_report: clean gcov_lib gcov_test
	./s21_decimal_tests
	lcov -t "s21_decimal_tests" -o s21_decimal_tests.info -c -d .
	genhtml -o report s21_decimal_tests.info
	open report/index.html

gcov_lib:
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $(SRC)
	ar -rc libs21_decimal.a *.o
	ranlib libs21_decimal.a

gcov_test: s21_decimal_tests.check gcov_lib
	checkmk ./s21_decimal_tests.check > s21_decimal_tests.c
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c s21_decimal_tests.c
	$(CC) $(GCOVFLAGS) s21_decimal_tests.o -L. -ls21_decimal $(LDFLAGS) -o s21_decimal_tests

format:
	cp ../materials/linters/.clang-format .
	clang-format -i $(SRC)
	clang-format -n $(SRC)

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css s21_decimal *.dSYM tests *.info s21_decimal_tests s21_decimal_tests.c report/ .DS_Store ../.DS_Store .clang-format