#include "structs.h"

void insertTail(DLList **listPtr, customer *c);
DLList *deleteDLList(DLList **, DLList *, DLList *, int);
DLList *makeDLList(customer *, DLList *, DLList *);
void printDLList(DLList *);
void printList(DLList *);
void freeDLList(DLList *);
void insertTail(struct DLList **head_ref, customer *newCustomer);
DLList *readFile(char *fileName);
DLList * searchListByName(DLList * list, char * name);
void deleteByName(DLList **, char *);
