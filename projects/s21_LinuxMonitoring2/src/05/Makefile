.PHONY: all test clean 

CFLAGS= -std=c11 -fsanitize=address -g -O0 

all:
	@clear
	@echo "========================>"
	gcc $(CFLAGS) log_analysis.c -o l
	./l
	rm l

clean:
	rm -rf l *.log