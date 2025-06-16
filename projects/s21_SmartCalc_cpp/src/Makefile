.PHONY: all install uninstall clean dvi dist tests style_format style_test push_g push leaksT valgrind valgrind_full production_test build latex_install dist

CXX = gcc 
DBG_FLGS = -fsanitize=address -fsanitize=undefined
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic 
LINUX_FLAGS= `pkg-config --cflags --libs check`
TST_LIB_FLGS = -lgtest -lgmock -pthread
MAC_FLGS = 

OS := $(shell uname -s)

ifeq ($(OS),Linux)
		LEAKS_CHECKER=valgrind		
else
	ifeq ($(OS),Darwin)
		LEAKS_CHECKER=leaksT
		MAC_FLGS = $(pkg-config --cflags --libs Qt5Core)
	endif
endif

SRC := $(wildcard ./sources/Model/sources/*.cpp)
# SRC += $(wildcard ./sources/Controller/sources/*.cpp)

TST_SRC = ./tests/model_tests.cpp
OBJ = $(SRC:%.cpp=%.o)
BCK_END_LIB = ./sources/Model/s21_calc_backend.a
CONTROLLER = ./sources/Controller/sources/*.cpp 

HDRS = ./sources/Model/headers/backend.h  ./sources/Controller/headers/controller.h 

all: clean calc_start tests #valgrind

s21_calc_backend.a: $(OBJ)
	ar rcs s21_calc_backend.a $(OBJ)
	ranlib s21_calc_backend.a
	# rm -f $(OBJ)
	mv s21_calc_backend.a ./sources/Model/

QT_PATH = ./sources/View/Qt_files/UltraCalculator
INSTALL_PATH = .
build: s21_calc_backend.a
	cd $(QT_PATH) && qmake UltraCalculator.pro
	make -C $(QT_PATH)

calc_start: build install
		# open $(INSTALL_PATH)
	$(INSTALL_PATH)/UltraCalculator

%.o:%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) $(MAC_FLGS) -c $< -o $@

tests: s21_calc_backend.a $(BCK_END_LIB) $(TST_SRC)
	g++ $(CXXFLAGS) $(TST_SRC) $(BCK_END_LIB) $(CONTROLLER) $(TST_LIB_FLGS) -o tests.t # 2>compilation_errors.txt
	./tests.t
	@rm tests.t

clean: 
	make uninstall
	rm -f tests.t $(BCK_END_LIB) valgrind-out.txt *.aux *.dvi *.log
	find . -name "*.o" -type f -delete
	if [ -f "$(QT_PATH)/Makefile" ]; then \
		make -C $(QT_PATH) clean; \
	fi
	rm -f $(QT_PATH)/UltraCalculator
	rm -f SmartCalc_v2.0.tgz
	rm -f readme.pdf

install: build
ifeq ($(OS),Linux)
	cp $(QT_PATH)/UltraCalculator $(INSTALL_PATH)/UltraCalculator
else
ifeq ($(OS),Darwin)
	cp -R $(QT_PATH)/UltraCalculator.app $(INSTALL_PATH)/UltraCalculator.app
endif
endif

uninstall: 
ifeq ($(OS),Linux)
	rm -f ~$(INSTALL_PATH)/UltraCalculator	
else
ifeq ($(OS),Darwin)
	rm -fr ~$(INSTALL_PATH)/UltraCalculator.app
endif
endif

latex_install: # ubuntu only
	echo "Enter the password to install the latex package"
	sudo apt-get update && sudo apt-get install texlive-latex-base texlive-lang-cyrillic -y

dvi:  # ubuntu only
ifeq ($(OS),Linux)
	make latex_install && latex readme.tex && dvipdf readme.dvi && xdg-open readme.pdf
else
ifeq ($(OS),Darwin)
	@echo "Sorry, target for linux-system only. Check the comments below for more information."
endif
endif
	# Generate documentation files in the given format. These targets should always exist, but any or all can be a no-op if the given output format cannot be generated.
	# Перевод:
	# Генерировать файлы документации в заданном формате. Эти цели должны существовать всегда, но любой из них или все они могут быть недействительными, если заданный выходной формат не может быть сгенерирован.
	# https://www.gnu.org/software/make/manual/html_node/Standard-Targets.html

FILES_FOR_DISTR = Makefile readme.tex
FOLDERS_FOR_DISTR = sources
dist: clean
	rm -rf ./SmartCalc_v2.0/
	mkdir SmartCalc_v2.0/
	cp $(FILES_FOR_DISTR) ./SmartCalc_v2.0/
	cp -r $(FOLDERS_FOR_DISTR) ./SmartCalc_v2.0/
	tar cvzf SmartCalc_v2.0.tgz SmartCalc_v2.0/  
	rm -rf SmartCalc_v2.0/

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

style_format:
	@echo "=> Formatting the code to the Google-style."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -i -style=Google

style_test:
	@echo "=> Testing the code for the Google-style."
	@echo "If you don't see any error messages, then everything is fine."
	@find . -iname "*.h" -o -iname "*.c" | xargs clang-format -n -style=Google

valgrind_full:  $(BCK_END_LIB)
	g++ $(CXXFLAGS) $(TST_SRC) $(BCK_END_LIB) $(CONTROLLER) $(TST_LIB_FLGS) -o test
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./test
	@rm test

# для корректной работы компилировать отключив флаги санитайзера
valgrind:  $(BCK_END_LIB)
	@echo "=> valgrind"
	g++ $(CXXFLAGS) $(TST_SRC) $(BCK_END_LIB) $(CONTROLLER) $(TST_LIB_FLGS) -o test
	valgrind --tool=memcheck --leak-check=yes ./test 		 
	@rm test

leaksT:  $(BCK_END_LIB)
	g++ $(CXXFLAGS) $(TST_SRC) $(BCK_END_LIB) $(CONTROLLER) $(TST_LIB_FLGS) -o test
	CK_FORK=no leaks -atExit -- ./test
	@rm test

push: style_format clean
	git pull
	git checkout develop
	git add .
	git commit -m "up"
	git push
