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

//write to file?
int writeToFile = 0;
//write to console?
int writeToConsole = 1;

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
      writeToFile = 1;
    }else if(strcmp(argv[i], "-c") == 0){
      i++;
      writeToConsole = atoi(argv[i]);
    }else if(strcmp(argv[i], "-h") == 0){
      printhelp();
      exit(0);
    }else{
      printf("Couldn't understand %s\r\n", argv[i]);
    }
  }
}

int main(int argc, char* argv[]){
  printf("\n");
  begin = clock();
  void (*primalgorithm)(int, struct integerlist*);
  if(argc > 1){
    argumentsparser(argc, argv);
  }
  switch(modus){
    case 0:
    primalgorithm = &primeGen;
    printf("Using the standard Generator.\r\n");
    break;
    case 1:
    primalgorithm = &stupidPrimeGen;
    printf("Using the slow Generator.\r\n");
    break;
    case 2:
    primalgorithm = &betterPrimeGen;
    printf("Using the faster Generator.\r\n");
    break;
    default:
    modus = 0;
    printf("Using the standard Generator.\r\n");
    break;
  }
  switch(outputmode){
    case 0:
    printf("Only printing stats.\r\n");
    break;
    case 1:
    printf("Printing stats and primes.\r\n");
    break;
    case 2:
    printf("Printing stats and the primes to a table.\r\n");
    break;
    default:
    outputmode = 0;
    printf("Only printing stats.\r\n");
    break;
  }
  switch(writeToConsole){
    case 1:
    printf("Output to console.\r\n");
    break;
    case 0:
    default:
    writeToConsole = 0;
    printf("Do not write to console.\r\n");
    break;
  }
  switch(writeToFile){
    case 1:
    printf("Output to file.\r\n");
    case 0:
    default:
    writeToFile = 0;
    printf("Do not write to file.\r\n");
    break;
  }
  if(upperBoundary > 2){
    printf("Upper boundary is %d.\r\n", upperBoundary);
  } else {
    upperBoundary = 100;
    printf("Invalid upper boundary value. Defaulting to 100\r\n");
  }
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
  if(writeToConsole)
    switch(outputmode){
      case 0:
      puts(stats);
      break;
      case 1:
      puts(stats);
      integerlist_print(list);
      break;
      case 2:
      puts(stats);
      printf("How many columns??\n");
      int columns;
      scanf("%i", &columns);
      printf("\n");
      integerlist_printformated(list, columns);
      break;
      default:
      printf("Oops, something went wrong :(\r\n)");
    }
  if(writeToFile && outputfile != NULL)
    switch(outputmode){
      case 0:
      fputs(outputfile, "Hallo Welt\r\n");
      fputs(outputfile, stats);
      break;
      case 1:
      fputs(outputfile, stats);
      integerlist_tofile(list, outputfile);
      break;
      case 2:
      puts(stats);
      printf("How many columns??\n");
      int columns;
      scanf("%i", &columns);
      printf("\n");
      integerlist_tofileformated(list, outputfile, columns);
      break;
      default:
      printf("Oops, something went wrong :(\r\n)");
    }
  if(outputfile != NULL){
    fputs(outputfile, "\0");
    fclose(outputfile);
  }
  integerlist_free(list);
  free(stats);
  return 0;
}
