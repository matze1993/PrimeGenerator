#include <stdio.h>
#include "simpleintegerlist.h"

struct integerlist* integerlist_init(int value){
  struct integerlist* temp = calloc(1, sizeof(struct integerlist));
  temp->value = value;
  return temp;
}

void integerlist_free(struct integerlist* list){
  struct integerlist* temp = (*list).next;
  while(temp != NULL){
    free(list);
    list = temp;
    temp = list->next;
  }
}

void integerlist_add(struct integerlist* list, int value){
  struct integerlist* temp = list;
  while(temp->next != NULL){
    temp = temp->next;
  }
  (*temp).next = integerlist_init(value);
}

int integerlist_get(struct integerlist* list, int index){
  int i = index;
  struct integerlist* temp = list;
  while(i > 0 && temp->next != NULL){
    i--;
    temp = temp->next;
  }
  if(i != 0){
    printf("List not big enough, return zero information");
    return 0;
  } else {
    return temp->value;
  }
}

int integerlist_getLast(struct integerlist* list){
  struct integerlist* temp = list;
  while(temp->next != NULL){
    temp = temp->next;
  }
  return temp->value;
}

int integerlist_size(struct integerlist* list){
  int count = 1;
  struct integerlist* temp = list;
  while(temp->next != NULL){
    temp = temp->next;
    count++;
  }
  return count;
}

void integerlist_print(struct integerlist* list){
  int size = integerlist_size(list);
  int i = 0;
  for(i; i < size; i++){
    printf("\t%d\t\t:\t\t%d\r\n", (i+1), integerlist_get(list, i));
  }
}

void integerlist_tofile(struct integerlist* list, FILE* file){
  int size = integerlist_size(list);
  int i = 0;
  for(i; i < size; i++){
    fprintf("%d\t%d\n", i, integerlist_get(list, i));
  }
}
