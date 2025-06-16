.PHONY: all test clean 

all:
	@[ -d ./tmp_for_testing ] || mkdir ./tmp_for_testing
	sudo ./main.sh 1

data_test:
	# all kind of errors exist there
	./main.sh qwertyuyui 5 qwertyud.mil; 111Mb 0

t1:
	sudo ./main.sh 1

t2:
	sudo ./main.sh 2

t3: 
	sudo ./main.sh 3

clean:
	clear
	@rm -rf l *.log tmp_for_testing