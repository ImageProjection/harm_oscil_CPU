compile:
	g++ -Wall -o main main.cpp

debug_compile:
	g++ -g -Wall -o main main.cpp

run:
	./main

clean:
	rm main && find . -name 'out*' -delete
#to find regular expressions, rm can't
