build:
	g++ -g -std=c++11 -Wall -o main.exe main.cpp

run:
	./main.exe

clean:
	rm main.exe

valgrind:
	valgrind --leak-check=yes ./main.exe