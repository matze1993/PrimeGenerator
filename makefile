PrimeGenerator2_0.1: main.o simpleintegerlist.o
	gcc -o linux/PrimeGenerator2_0_2 main.o simpleintegerlist.o -w -std=gnu11
	rm main.o
	rm simpleintegerlist.o

main.o: main.c
	gcc -c main.c -w -std=gnu11 -o main.o

simpleintegerlist.o: simpleintegerlist.c
	gcc -c simpleintegerlist.c -w -std=gnu11 -o simpleintegerlist.o
