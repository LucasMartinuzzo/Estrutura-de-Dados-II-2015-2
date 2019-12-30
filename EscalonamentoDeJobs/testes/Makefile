all: trab3 clean
trab3: main.o tads.o beamSearch.o branchBound.o
	gcc -o trab3 main.o tads.o beamSearch.o branchBound.o
main.o: main.c tads.h beamSearch.h branchBound.h
	gcc -o main.o -c main.c -Wall -ansi
tads.o: tads.c tads.h
	gcc -o tads.o -c tads.c -Wall -ansi
beamSearch.o: beamSearch.c beamSearch.h tads.h
	gcc -o beamSearch.o -c beamSearch.c -Wall -ansi
branchBound.o: branchBound.c beamSearch.h tads.h
	gcc -o branchBound.o -c branchBound.c -Wall -ansi
clean:
	rm -rf *.o
