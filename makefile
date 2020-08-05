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

win_compile:
	x86_64-w64-mingw32-g++ -Wall -o main.exe main.cpp && mv main.exe '/home/artem/Dropbox/ФФ книги  ярлыки материалы/5сем/coarse_works_shared_executables/CUDA/CPU'

win_clean:
	rm -rf '/home/artem/Dropbox/ФФ книги  ярлыки материалы/5сем/coarse_works_shared_executables/CUDA/CPU/'main.exe
