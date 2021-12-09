all: plumbing.o
	gcc -o pipe plumbing.o

plumbing.o: plumbing.c
	gcc -c plumbing.c

run:
	./pipe

clean:
	rm *.o
	rm pipe

