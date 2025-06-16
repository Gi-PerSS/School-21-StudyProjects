CC = clang++ -std=c++20
CFLAGS = -c -Wall -Wextra -Werror -I./headers
BUILD_DIR = build
INSTALL_DIR = 3DViewer_v1_0
APP = 3dViewer_v1_0
GCOV = -fprofile-arcs -ftest-coverage
LIBCPP = ./sources/model_parser.cpp
LIBH = ./headers/model_parser.h ./headers/obj_data.h ./headers/observer.h
LIBO = ./model_parser.o
TESTCPP = ./tests/unit_tests.cpp

OS = $(shell uname)

QT_VERSION ?= 5

ifeq ($(QT_VERSION), 6)
	QMAKE = qmake6
else
	QMAKE = qmake
endif

ifeq ($(OS), Linux)
	OS_FLAGS = -lgtest -lgtest_main -pthread
	CC += -D OS_LINUX -g
	DIR = 
	QTFLAGS = -spec linux-g++
	CHECK_LEAKS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt
	OPEN = firefox
else
	OS_FLAGS = -lgtest -lgtest_main -lpthread
	CC += -D OS_MAC -g -stdlib=libc++
	DIR = /$(APP).app/Contents/MacOS/
	QTFLAGS =
	CHECK_LEAKS = leaks --atExit --
	OPEN = open
endif

SOURCES = \
	./sources/model_parser.cpp \
	./sources/view_glview.cpp \
	./sources/view_settings.cpp \
	./sources/presenter_mainviewer.cpp \
	./sources/main.cpp \
	./sources/command.cpp \
	./sources/observer.cpp

HEADERS = \
	./headers/model_parser.h \
	./headers/view_glview.h \
	./headers/view_settings.h \
	./headers/presenter_mainviewer.h \
	./headers/command.h \
	./headers/observer.h \
	./headers/obj_data.h

OBJECTS = \
	$(BUILD_DIR)/model_parser.o \
	$(BUILD_DIR)/view_glview.o \
	$(BUILD_DIR)/view_settings.o \
	$(BUILD_DIR)/presenter_mainviewer.o \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/command.o \
	$(BUILD_DIR)/observer.o

all: build

build: $(BUILD_DIR)/Makefile
	make -C $(BUILD_DIR)/ first

$(BUILD_DIR)/Makefile: $(APP).pro
	mkdir -p $(BUILD_DIR)
	$(QMAKE) -o $(BUILD_DIR)/Makefile ./$(APP).pro $(QTFLAGS) CONFIG+=qtquickbuilder

rebuild: clean all

install: build
	mkdir -p $(INSTALL_DIR)
ifeq ($(OS), Darwin)
	cp -r $(BUILD_DIR)/$(APP).app $(INSTALL_DIR)/
	$(BUILD_DIR)/$(APP).app/Contents/MacOS/$(APP)
else
	cp -r $(BUILD_DIR)/$(APP) $(INSTALL_DIR)/$(APP)
	./$(INSTALL_DIR)/$(APP)
endif

dist: install
	tar -czvf $(INSTALL_DIR).tgz $(INSTALL_DIR)/

uninstall:
	rm -rf $(INSTALL_DIR)

parser.a: $(LIBCPP) $(LIBH)
	$(CC) $(CFLAGS) $(LIBCPP) -o $(LIBO)
	ar -rcs parser.a $(LIBO)
	ranlib $@
	cp $@ lib$@
	rm -rf *.o

# эта цель нужна только для s21_tests - тестов для школьного мака
GTEST_DIR = googletest
GTEST_BUILD_DIR = $(GTEST_DIR)/build
GTEST_LIB_DIR = $(GTEST_DIR)/lib
GTEST_INCLUDE_DIR = googletest/googletest/include

setup_gtest:
	@if [ ! -d "$(GTEST_DIR)" ]; then \
        git clone https://github.com/google/googletest.git $(GTEST_DIR); \
	fi
	@mkdir -p $(GTEST_BUILD_DIR)
	@cd $(GTEST_BUILD_DIR) && cmake .. \
		-DCMAKE_CXX_STANDARD=20 \
		-DCMAKE_CXX_FLAGS="-stdlib=libc++" \
		-DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -lpthread" \
		-DCMAKE_OSX_DEPLOYMENT_TARGET=13.0
	@cd $(GTEST_BUILD_DIR) && make
	@mkdir -p $(GTEST_LIB_DIR)
	@cp $(GTEST_BUILD_DIR)/lib/*.a $(GTEST_LIB_DIR)/

# это тесты для школьных маков
s21_tests: clean parser.a setup_gtest $(TESTCPP)
	$(CC) $(CFLAGS) -I$(GTEST_INCLUDE_DIR) $(TESTCPP) -o unit_tests.o
	$(CC) -std=c++20 -D OS_MAC -stdlib=libc++ -mmacosx-version-min=13.0 \
		unit_tests.o parser.a -L$(GTEST_LIB_DIR) -lgtest_main -lgtest -pthread -lc++ -o Test
	./Test

# тесты для не-школьного мака
tests: clean parser.a $(TESTCPP)
	@echo "\nUse s21_tests on school Mac ==="
	$(CC) $(CFLAGS) $(TESTCPP) -o unit_tests.o
	$(CC) unit_tests.o parser.a -o Test $(OS_FLAGS)
	./Test
	# rm -rf *.o *.a ./Test

gcov_report: $(LIBCPP) $(TESTCPP) $(LIBH)
	$(CC) $(CFLAGS) $(GCOV) $(LIBCPP) -c -o $(LIBO)
	$(CC) $(CFLAGS) $(GCOV) $(TESTCPP) -c -o unit_tests.o
	$(CC) $(LIBO) unit_tests.o -o Test $(OS_FLAGS) $(GCOV)
	./Test
	mkdir -p report
	gcovr -r . --html --html-details -o report/index.html
	$(OPEN) ./report/index.html
	rm -rf *.o *.gcno *.gcda Test

## install_gcov_deps_linux: установка зависимостей для Ubuntu
install_gcov_deps_linux:
	sudo apt-get install -y lcov gcc-13 g++-13 
	sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-13 90 # вес для приоритизации версии при обновлениях
	sudo update-alternatives --set gcov /usr/bin/gcov-13

gcov_report_linux: install_gcov_deps_linux
	g++-13 $(CFLAGS) $(GCOV) $(LIBCPP) -o $(LIBO)
	ar -rcs parser.a $(LIBO) -v
	g++-13 $(CFLAGS) $(GCOV) $(TESTCPP) -o unit_tests.o
	g++-13 unit_tests.o parser.a -o Test $(OS_FLAGS) $(GCOV)
	./Test --gtest_output="xml:report/test_results.xml"
	mkdir -p report
	lcov --capture --directory . --output-file report/coverage.info \
		--gcov-tool /usr/bin/gcov-13 \
		--rc branch_coverage=1 \
		--ignore-errors mismatch,incompatible,unused
	lcov --remove report/coverage.info \
		'/usr/*' \
		'*/tests/*' \
		'*/headers/*' \
		-o report/filtered.info
	genhtml report/filtered.info \
		--output-directory report \
		--branch-coverage \
		--title "3DViewer Coverage" \
		--prefix $(shell pwd) \
		--demangle-cpp \
		--ignore-errors unmapped
	xdg-open ./report/index.html || echo "Open report: $$(pwd)/report/index.html"
	rm -rf *.o *.gcno *.gcda Test parser.a

# install_gcov_deps_macos: Установка зависимостей через Brew
install_gcov_deps_macos:
	brew install llvm
	brew install gcovr

s21_gcov_report_macos: parser.a setup_gtest $(TESTCPP)
	$(CC) $(CFLAGS) $(GCOV) $(LIBCPP) -o $(LIBO)
	ar -rcs parser.a $(LIBO)
	$(CC) $(CFLAGS) $(GCOV) -I$(GTEST_INCLUDE_DIR) $(TESTCPP) -o unit_tests.o
	$(CC) -std=c++20 -D OS_MAC -stdlib=libc++ -mmacosx-version-min=13.0 \
		unit_tests.o parser.a -L$(GTEST_LIB_DIR) -lgtest_main -lgtest -pthread -lc++ $(GCOV) -o Test
	./Test
	mkdir -p report
	gcovr -r . \
		--exclude tests/ \
		--exclude 'googletest/' \
		--gcov-executable "$(shell brew --prefix llvm)/bin/llvm-cov gcov" \
		--gcov-ignore-errors all \
		--html --html-details  -o report/index.html
	$(OPEN) report/index.html
	rm -rf *.o *.gcno *.gcda Test

leaks: clean parser.a $(TESTCPP)
	$(CC) $(TESTCPP) parser.a $(OS_FLAGS) -o ./Test
	$(CHECK_LEAKS) ./Test
	rm -f *.o *.a Test

style_formatter:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -style=Google -i $(SOURCES) $(HEADERS)
	rm -rf .clang-format

style:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -style=Google -n $(SOURCES) $(HEADERS)
	rm -rf .clang-format

cppcheck:
	cppcheck $(SOURCES) $(HEADERS)

check: style cppcheck leaks

clean:
	rm -rf *.o *.a *.out *.txt *.gcno *.gch *.gcda *.info *.tgz *.obj report coverage \
		$(APP).pro.user Test $(BUILD_DIR) $(INSTALL_DIR) Test.dSYM ui/*.autosave
	rm -rf $(GTEST_DIR)

.PHONY: all build rebuild install dist uninstall tests gcov_report leaks style_formatter style cppcheck check clean parser.a