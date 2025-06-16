.PHONY: all install uninstall clean dvi dist tests gcov_report t check_deps

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror 
LINUX_FLAGS= `pkg-config --cflags --libs check`
DBG_FLAGS = -fsanitize=address -g 

OS := $(shell uname -s)

ifeq ($(OS),Linux)
    CHK_FLGS=`pkg-config --cflags --libs check`
else ifeq ($(OS),Darwin)
    CHK_FLGS= -lcheck -lm -lpthread
endif

# Тесты.
TSTs = ./Tests/smartcalc_backend_tests.c

BACKEND_PATH=./BackEnd/
BACKEND_FILENAMES = API.c data_check.c token_extraction.c stack_functions.c postfix_calculator.c infix_to_postfix.c global_variables.c function_graph_formula_parser.c debug_functions.c 
CALC_BACKEND = $(addprefix $(BACKEND_PATH),$(BACKEND_FILENAMES))

all: compile
	./GUI/calculator_GUI &

check_deps:
	@./install_deps.sh

compile: 
	@./GTK-compilator.sh "$(CALC_BACKEND)"

brew:
	bash ./Auxiliary/brew_install_gfr.sh

brew_gtk_install:
	brew install gtk+3
	brew install librsvg
	brew install cairo

brew_minimum:
	brew install lcov
	brew install clang-format

debian_dependencies:
	bash ./Auxiliary/debian_dependencies.sh

tests:
	make clean
	$(CC) $(CFLAGS) $(CALC_BACKEND) $(TSTs) $(CHK_FLGS) -o t -lm -ldl 
	./t

install: compile
	cp ./GUI/calculator_GUI ~/UltraCalculator

uninstall: 
	rm ~/UltraCalculator

clean: 
	rm -f *.log *.aux *.dvi 
	rm -f readme.pdf
	rm -f t
	rm -f ./GUI/calculator_GUI SmartCalc_v1.0.tgz
	rm -f gcov_test t
	rm -f expressions_with_answers.txt e.txt
	rm -f smartcalc_backend_tests.check smartcalc_backend_tests.c
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css *.dSYM *.info report/ .DS_Store ../.DS_Store .clang-format

dvi: 
ifeq ($(OS),Linux)
	latex readme.tex && dvipdf readme.dvi && mupdf readme.pdf
else ifeq ($(OS),Darwin)
	@echo "Sorry, target for linux-system only. Check the comments below for more information."
endif

dist: compile
	rm -rf ./SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/
	cp ./GUI/calculator_GUI ./SmartCalc_v1.0/UltraCalculator
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/  
	rm -rf SmartCalc_v1.0/

gcov_report: gcov_test.info
	genhtml -o report/ gcov_test.info
	open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test:  
	$(CC) $(CFLAGS) --coverage $(TSTs) $(CALC_BACKEND) $(CHK_FLGS) -o gcov_test

gcov_test.gcda:
	chmod +x *
	./gcov_test

style_format:
	@echo "=> Formatting the code to the Google-style."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -i -style=file:"../materials/linters/.clang-format"

style_test:
	@echo "=> Testing the code for the Google-style."
	@echo "If you don't see any error messages, then everything is fine."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -n -style=file:"../materials/linters/.clang-format"

valgrind_full: 
	# No memory allocation has use

valgrind:  
	# No memory allocation has use		 

push:
	make style_format
	make clean
	git checkout develop
	git add .
	git commit -m "up"
	git push