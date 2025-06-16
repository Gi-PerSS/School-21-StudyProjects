# тестировалось на Ubuntu

WWW = -Wall -Wextra -Werror
LDFLAGS = -lcheck -lm -lsubunit -lrt
GCOV_FLAGS = --coverage

all: clean test

test: s21_string.a
	gcc $(WWW) unit_tests.c s21_string.a -o s21_test $(LDFLAGS)
	./s21_test

gcov_report: test clean_gcov
	mkdir -p report
	gcc $(WWW) $(GCOV_FLAGS) unit_tests.c s21_string.c -o gcov_report $(LDFLAGS)
	./gcov_report
	lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1
	genhtml coverage.info -o report --branch-coverage
	@echo "Report generated at report/index.html"

s21_string.a: s21_string.o
	ar rc s21_string.a s21_string.o
	ranlib s21_string.a

s21_string.o:
	gcc $(WWW) -c s21_string.c

clean_gcov:
	rm -f *.gcda *.gcno *.info gcov_report

clean: clean_gcov
	rm -f *.o *.a s21_test
	rm -rf report

install_deps:
	@echo "Installing dependencies..."
	@if [ -f /etc/debian_version ]; then \
		sudo apt-get update && sudo apt-get install -y build-essential check lcov; \
	elif [ -f /etc/redhat-release ]; then \
		sudo yum groupinstall -y "Development Tools" && \
		sudo yum install -y check-devel lcov; \
	elif [ "$$(uname)" = "Darwin" ]; then \
		brew install check lcov; \
	fi
	@echo "Dependencies installed"