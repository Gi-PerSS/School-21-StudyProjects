.PHONY: all clean test s21_matrix.a check rebuild open gcov_report

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 
LINUX_FLAGS= `pkg-config --cflags --libs check`
TST_LIBS :=  -lcheck -lm -lpthread

OS := $(shell uname -s)

ifeq ($(OS),Linux)
		CHK_FLGS=`pkg-config --cflags --libs check`
else
	ifeq ($(OS),Darwin)
		CHK_FLGS= -lcheck -lm -lpthread
	endif
endif

all: clean test s21_matrix.a gcov_report

test: s21_matrix.a s21_test.o
	$(CC) $(CFLAGS) s21_test.o s21_matrix.a $(CHK_FLGS) -o test
	./test

s21_test.o: s21_matrix_test.c
	$(CC) $(CFLAGS) -c s21_matrix_test.c -o s21_test.o

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o: s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

gcov_report: gcov_test.info
	genhtml -o report/ gcov_test.info
	open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: s21_matrix_test.c s21_matrix.c
	$(CC) $(CFLAGS) --coverage s21_matrix_test.c s21_matrix.c $(CHK_FLGS) -o gcov_test

gcov_test.gcda:
	chmod +x *
	./gcov_test

clean: 
	rm -rf test gcov_test *.txt *.gcno *.gcda *.info report *.o *.a main *.out
	
leaksT: test
	CK_FORK=no leaks -atExit -- ./test


USERNAME=$(shell whoami)

brew:
	eval /opt/goinfre/$(USERNAME)/homebrew/bin/brew shellenv; \
	brew update --force --quiet; \
	chmod -R go-w "$(brew --prefix)/share/zsh"

install_brew:
	cd /opt/goinfre/$(USERNAME); \
	mkdir homebrew; \
	git clone https://github.com/Homebrew/brew homebrew; \
	make brew

lcov:
	if [ "$(OS)" = "Linux" ]; then \
		sudo apt-get update; \
    	sudo apt-get -y install lcov; \
	else \
   		brew install lcov;\
	fi 	

# Далее цели отладки
SHELL := /bin/bash
production_test:
	clear
	make style_test
	@read -n 1 -s -r -p "Next => tests. Press any key to continue."
	clear
	make test
	@read -n 1 -s -r -p "Next => valgrind. Press any key to continue"
	clear
	@if [ "$(OS)" = "Linux" ]; then \
		make valgrind; \
	else \
  		CK_FORK=no leaks -atExit -- ./test ; \
	fi 
	@read -n 1 -s -r -p "Next => docker. Press any key to continue"
	clear
	@make docker_test
	@read -n 1 -s -r -p "Next => gcov_report. Press any key to continue"
	make gcov_report

docker_test:
	@if [ "$(OS)" = "Linux" ]; then \
		cd "../materials/build"; \
    	sudo bash "./run.sh"; \
	else \
		echo "Sorry. Docker only for Linux." ;\
	fi 

style_format:
	@echo "=> Formatting the code to the Google-style."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -i -style=file:"../materials/linters/.clang-format"

style_test:
	@echo "=> Testing the code for the Google-style."
	@echo "If you don't see any error messages, then everything is fine."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -n -style=file:"../materials/linters/.clang-format"

valgrind_full:  test
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./test
         #./$(OUT)

valgrind:  test
	valgrind --tool=memcheck --leak-check=yes ./test #./$(OUT)		 

push:
	# make valgrind
	make style_format
	make clean
	git checkout develop
	git add .
	git commit -m "up"
	git push
