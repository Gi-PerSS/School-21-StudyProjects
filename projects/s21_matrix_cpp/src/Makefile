.PHONY: all clean test style_format style_test

CXX = gcc 
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic 
DBG_FLGS = -fsanitize=address -fsanitize=undefined
TST_LIB_FLGS = -lgtest -lgmock -pthread

OS := $(shell uname -s)

ifeq ($(OS),Linux)
		LEAKS_CHECKER=valgrind		
else
	ifeq ($(OS),Darwin)
		LEAKS_CHECKER=leaksT
	endif
endif

# пути поиска исходных файлов
VPATH = ./sources 

SRC =	\
accessors_and_mutators.cpp	\
constructors_and_destructor.cpp	\
data_checker.cpp	\
debugging_and_auxiliary.cpp	\
operator_overloading.cpp	\
s21_matrix_oop.cpp 

TST_SRC = ./tests/tests.cpp
OBJ = $(SRC:%.cpp=%.o)
MX_LIB = s21_matrix_oop.a

all: clean test $(LEAKS_CHECKER)

s21_matrix_oop.a: $(OBJ)
	ar rcs $(MX_LIB) $(OBJ)
	ranlib $(MX_LIB)
	@rm -f $(OBJ)

%.o:%.cpp "./headers/s21_matrix_oop.h"
	$(CC) $(CFLAGS) $(DBG_FLGS) -c $< -o $@

test: $(MX_LIB)
	g++ $(CFLAGS) $(TST_SRC) $(MX_LIB) $(TST_LIB_FLGS) -o test
	./test
	@rm test

clean: 
	rm -rf test *.o *.a valgrind-out.txt

# Далее цели отладки

SHELL := /bin/bash
production_test:
	clear
	make style_test
	@read -n 1 -s -r -p "Next => tests. Press any key to continue."
	clear
	make test
	@read -n 1 -s -r -p "Next => a leak test. Press any key to continue"
	clear
	make $(LEAKS_CHECKER)

style_format:
	@echo "=> Formatting the code to the Google-style."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -i -style=Google

style_test:
	@echo "=> Testing the code for the Google-style."
	@echo "If you don't see any error messages, then everything is fine."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -n -style=Google

valgrind_full:  $(MX_LIB)
	g++ $(CFLAGS) $(TST_SRC_V) $(MX_LIB) $(TST_LIB_FLGS) -o test
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./test
	@rm test

# для корректной работы компилировать отключив флаги санитайзера
valgrind:  $(MX_LIB)
	@echo "=> valgrind"
	g++ $(CFLAGS) $(TST_SRC) $(MX_LIB) $(TST_LIB_FLGS) -o test
	valgrind --tool=memcheck --leak-check=yes ./test 		 
	@rm test

leaksT:  $(MX_LIB)
	g++ $(CFLAGS) $(TST_SRC) $(MX_LIB) $(TST_LIB_FLGS) -o test
	CK_FORK=no leaks -atExit -- ./test
	@rm test

push: style_format clean
	# make valgrind
	git checkout develop
	git add .
	git commit -m "up"
	git push
