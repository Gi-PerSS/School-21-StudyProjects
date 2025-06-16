.PHONY: all test clean 

CFLAGS= -std=c11 -fsanitize=address -g -O0 

all:
	@[ -d ./tmp_for_testing ] || mkdir ./tmp_for_testing
	./main.sh ./tmp_for_testing 3 qw 4 zxcvbn.zxc 1K

data_test:
	# all kind of errors exist there
	./main.sh T 5 qwertyud 11 zxcvbnmc.zxcc 101K

c:
	@clear
	@echo "========================>"
	@make clean
#	gcc $(CFLAGS) filenames_generator.c -o l
	@gcc $(CFLAGS) recursive_filename_generator.c -o l
	@./l
	@rm l

clean:
	clear
	@rm -rf l *.log tmp_for_testing