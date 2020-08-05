compile:
	g++ -Wall -o main main.cpp

debug_compile:
	g++ -g -Wall -o main main.cpp

test_file_compile_run:
	g++ -g -Wall -o testing_functions testing_functions.cpp && ./testing_functions

run:
	./main

clean:
	rm main && find . -name 'out*' -delete
#to find regular expressions, rm can't

git_log:
	git log --all --graph --decorate
