.PHONY: all test clean 

all:
	@[ -d ./tmp_for_testing ] || mkdir ./tmp_for_testing
	sudo ./main.sh qw zx.zx 100Mb

data_test:
	# all kind of errors exist there
	./main.sh qwertyuyui 5 qwertyud.mil; 111Mb 0

clean:
	clear
	@rm -rf l *.log tmp_for_testing


