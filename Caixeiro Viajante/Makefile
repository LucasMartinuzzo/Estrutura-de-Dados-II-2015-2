all: trab1
trab1: main.o exato.o nn2opt.o convexHull.o latex
	gcc -o trab1 main.o exato.o nn2opt.o convexHull.o -lm
main.o: main.c exato.h nn2opt.h convexHull.h
	gcc -o main.o -c main.c
exato.o: exato.c exato.h
	gcc -o exato.o -c exato.c -Wall -ansi
nn2opt.o: nn2opt.c nn2opt.h exato.h
	gcc -o nn2opt.o -c nn2opt.c -Wall -ansi
convexHull.o: convexHull.c convexHull.h nn2opt.h
	gcc -o convexHull.o -c convexHull.c -Wall -ansi
clean:
	rm -rf *.o
