PrimeGenerator2_0.1: main.o simpleintegerlist.o
	gcc -o PrimeGenerator2_0.2 main.o simpleintegerlist.o -w -std=gnu11

main.o: main.c
	gcc -c main.c -w -std=gnu11

simpleintegerlist.o: simpleintegerlist.c
	gcc -c simpleintegerlist.c -w -std=gnu11
