.PHONY: all test clean 

CFLAGS= -std=c11 -fsanitize=address -g -O0 



all:
	@clear	

	make clean
	gcc $(CFLAGS) log_generator.c -o l
	./l
	rm l

clean:
	rm -rf l *.log
	
gcc:
	sudo apt update
	sudo apt install build-essential
	sudo apt-get install manpages-dev
	gcc --version
