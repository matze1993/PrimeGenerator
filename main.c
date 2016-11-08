#include <stdio.h>
#include <time.h>
#include "simpleintegerlist.h"

int debug = 1;

//default modus: 0
//modus 0: using primeGen
//modus 1: using stupidPrimeGen
//modus 2: using betterPrimeGen
int modus = 0;

//default outputmode: 0
//outputmode 0: writing stats to console
//outputmode 1: writing stats+primes to console
//outputmode 1: writing stats+primes to console in formated way
//outputmode 3: writing stats to file
//outputmode 4: writing stats+primes to console
int outputmode = 0;

//upper boundary
int upperBoundary = 100;

FILE* outputfile;

//time meassuring variables
clock_t startcomputing;
clock_t endcomputing;
clock_t begin;
clock_t finish;

void debugmsg(char* msg){
  if(debug){
    printf("Debug:\t%s\r\n", msg);
  }
}

void primeGen(int maxNumber, struct integerlist* list){
  int actNumber = 3;
  for(actNumber; actNumber < maxNumber; actNumber++){
    int isPrime = 1;
    int size = integerlist_size(list);
    int i = 0;
    while(i < size && isPrime){
      printf("%2.1f%%\r", 100*((double) (actNumber+1) / (double) maxNumber));
      int rem = actNumber%integerlist_get(list, i);
      if(rem == 0){
        isPrime = 0;
      }
      i++;
    }
    if(isPrime){
      integerlist_add(list, actNumber);
    }
  }
  printf("\n\n");
}

void stupidPrimeGen(int maxNumber, struct integerlist* list){
  int actNumber = 3;
  for(actNumber; actNumber < maxNumber; actNumber++){
    int isPrime = 1;
    int size = integerlist_size(list);
    int i = 0;
    while(i < actNumber && isPrime){
      printf("%2.1f%%\r", 100*((double) (actNumber+1) / (double) maxNumber));
      int rem = actNumber%i;
      if(rem == 0){
        isPrime = 0;
      }
      i++;
    }
    if(isPrime){
      integerlist_add(list, actNumber);
    }
  }
  printf("\n\n");
}

void betterPrimeGen(int maxNumber, struct integerlist* list){
  int actNumber = 3;
  for(actNumber; actNumber < maxNumber; actNumber++){
    int isPrime = 1;
    int finished = 0;
    int size = integerlist_size(list);
    int uppertestlimit = actNumber;
    int i = 0;
    while(i < size && isPrime && !finished){
      printf("%2.1f%%\r", 100*((double) (actNumber+1) / (double) maxNumber));
      int testNumber = integerlist_get(list, i);
      if(testNumber < uppertestlimit){
        int rem = actNumber%testNumber;
        if(rem == 0){
          isPrime = 0;
          finished = 1;
        } else {
          uppertestlimit = actNumber/testNumber;
        }
      } else {
        isPrime = 1;
        finished = 1;
      }
      i++;
    }
    if(isPrime){
      integerlist_add(list, actNumber);
    }
  }
  printf("\n\n");
}

void printhelp(){
  //TODO
  printf("\nPlaceholder.\n\n");
}

char* statstring(int primescount){
  double timeBegintoFin = (double)(finish-begin) / CLOCKS_PER_SEC;
  double timePrimeCalc = (double)(endcomputing-startcomputing) / CLOCKS_PER_SEC;
  char* buffer = malloc(sizeof(char)*255);
  sprintf(buffer, "Stats:\r\nInterval:\t\t\t[2,%d)\r\nFound:\t\t\t\t%d\r\nComplete Runtime:\t\t%fs\r\nPrimecalculation:\t\t%fs\r\n",upperBoundary, primescount, timeBegintoFin, timePrimeCalc);
  return buffer;
}

void argumentsparser(int argc, char* argv[]){
  int i = 1;
  for(i; i<argc; i++){
    if(strcmp(argv[i], "-m") == 0){
      i++;
      modus = atoi(argv[i]);
    }else if(strcmp(argv[i], "-o") == 0){
      i++;
      outputmode = atoi(argv[i]);
    }else if(strcmp(argv[i], "-ub") == 0){
      i++;
      upperBoundary = atoi(argv[i]);
    }else if(strcmp(argv[i], "-f") == 0){
      i++;
      outputfile = fopen(argv[i], "w");
    }else if(strcmp(argv[i], "-h") == 0){
      printhelp();
      exit(0);
    }else{
      i++;
      printf("Couldn't understand %s", argv[i]);
    }
  }
}

int main(int argc, char* argv[]){
  begin = clock();
  void (*primalgorithm)(int, struct integerlist*);
  if(argc > 1){
    argumentsparser(argc, argv);
  }
  if(modus == 0){
    primalgorithm = &primeGen;
  }else if(modus == 1){
    primalgorithm = &stupidPrimeGen;
  }else if(modus == 2){
    primalgorithm = &betterPrimeGen;
  }
  printf("\nmodus\t\t%d\r\noutputmode\t%d\r\nupperBoundary\t%d\r\n", modus, outputmode, upperBoundary);
  printf("init list");
  struct integerlist* list = integerlist_init(2);  //initializing with 2
  printf(" successful\r");
  printf("starting                       \r");
  printf("                               \n");
  startcomputing = clock();
  primalgorithm(upperBoundary, list);
  endcomputing = clock();
  finish = clock();
  char* stats = statstring(integerlist_size(list));
  if(outputmode == 0){
    puts(stats);
  }else if(outputmode == 1){
    puts(stats);
    integerlist_print(list);
  }else if(outputmode == 2){
    puts(stats);
    printf("How many columns??\n");
    int columns;
    scanf("%i", &columns);
    printf("\n");
    integerlist_printformated(list, columns);
  }else if(outputmode == 3){
    //TODO
  }else if(outputmode == 4){
    //TODO
  }
  integerlist_free(list);
  free(stats);
  return 0;
}
