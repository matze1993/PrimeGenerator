all: main.obj simpleintegerlist.obj
	cl main.obj simpleintegerlist.obj -FePrimeGenerator_0_2
	del main.obj
	del simpleintegerlist.obj

main.obj: ../main.c
	cl -c ../main.c

simpleintegerlist.obj: ../simpleintegerlist.c
	cl -c ../simpleintegerlist.c
