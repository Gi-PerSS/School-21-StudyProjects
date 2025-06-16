# Версия для Ubuntu 

.PHONY: all clean test short_test valgrind

all: s21_grep

TEST_FILES = s21_grep.c s21_grep.h Makefile "./grep-tests/patterns"
HEADER_FILES = $(wildcard *.h)
COMMON_FUNCTIONS = "../common/common_functions.c"
COMMON_HEADER = "../common/common.h"

test: s21_grep
	bash ./grep-tests/t_grep.sh $(TEST_FILES)

GCC_FLAGS = -Wextra  -std=c11 -D_GNU_SOURCE  -Werror -Wall # -fsanitize=address   -O0 -g

s21_grep: s21_grep.c
	gcc $(GCC_FLAGS) $(HEADER_FILES) s21_grep.c $(COMMON_HEADER) $(COMMON_FUNCTIONS) -o s21_grep

valgrind: s21_grep
	valgrind ./s21_grep

clean:
	rm -f patterns s21_grep 21o go log.txt s21_grep.txt 21.out report.txt