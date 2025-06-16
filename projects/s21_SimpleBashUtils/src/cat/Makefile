.PHONY: all clean test short_test valgrind

all: s21_cat

TEST_CASES_FILES = $(wildcard ./cat-tests/test-files/*.tst)
COMMON_FUNCTIONS = "../common/common_functions.c"
COMMON_HEADER = "../common/common.h"
HEADER_FILES = $(wildcard *.h)

test: s21_cat
	bash ./cat-tests/cat-tests-short.sh $(TEST_CASES_FILES)

GCC_FLAGS =  -Werror -Wextra -Wall -std=c11 #-O0 -g -fsanitize=address

s21_cat: s21_cat.c
	gcc $(GCC_FLAGS) $(HEADER_FILES) $(COMMON_HEADER) $(COMMON_FUNCTIONS) s21_cat.c  -o s21_cat

valgrind: s21_cat
	valgrind ./s21_cat

clean:
	rm -f cat_output s21_cat_output cat_test_report.txt s21_cat ./*.tst
