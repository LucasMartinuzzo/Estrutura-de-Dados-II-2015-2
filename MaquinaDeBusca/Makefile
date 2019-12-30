all: trab2 clean
trab2: main.o tads.o encadeamento.o linear.o rehash.o buscas.o arquivos.o
	gcc -o trab2 main.o tads.o encadeamento.o linear.o rehash.o buscas.o arquivos.o
main.o: main.c tads.h encadeamento.h linear.h rehash.h arquivos.h buscas.h
	gcc -o main.o -c main.c -Wall -ansi
arquivos.o: arquivos.c arquivos.h linear.h encadeamento.h tads.h rehash.h buscas.h
	gcc -o arquivos.o -c arquivos.c -Wall -ansi
buscas.o: buscas.c buscas.h tads.h encadeamento.h linear.h rehash.h
	gcc -o buscas.o -c buscas.c -Wall -ansi
rehash.o: rehash.c rehash.h encadeamento.h tads.h linear.h
	gcc -o rehash.o -c rehash.c -Wall -ansi
linear.o: linear.c linear.h encadeamento.h tads.h tads.h
	gcc -o linear.o -c linear.c -Wall -ansi
encadeamento.o: encadeamento.c encadeamento.h tads.h
	gcc -o encadeamento.o -c encadeamento.c -Wall -ansi
tads.o: tads.c tads.h
	gcc -o tads.o -c tads.c -Wall -ansi

clean:
	rm -rf *.o
