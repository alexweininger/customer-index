#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

DLList *deleteDLList(DLList **, DLList *, DLList *, int);
DLList *makeDLList(customer *, DLList *, DLList *);
DLList *readFile(char *fileName);
DLList *searchListByName(DLList *list, char *name);
void deleteByName(DLList **, char *);
void freeDLList(DLList *);
void insertTail(DLList **listPtr, customer *c);
void insertTail(struct DLList **head_ref, customer *newCustomer);
void printDLList(DLList *);
void printList(DLList *);
