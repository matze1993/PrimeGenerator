#ifndef SIMPLEINTEGERLIST_H
#define SIMPLEINTEGERLIST_H

struct integerlist{
  struct integerlist* next;
  int value;
} integerlist;

extern struct integerlist* integerlist_init(int value);
extern void integerlist_free(struct integerlist* list);
extern void integerlist_add(struct integerlist* list, int value);
extern int integerlist_get(struct integerlist* list, int index);
extern int integerlist_getLast(struct integerlist* list);
extern int integerlist_size(struct integerlist* list);
extern void integerlist_print(struct integerlist* list);
extern void integerlist_tofile(struct integerlist* list, FILE* file);

#endif /* SIMPLEINTEGERLIST_H */
