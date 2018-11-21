#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

customer *parseLine(customer *t, char *line);
DLList *deleteDLList(DLList **, DLList *, DLList *, int);
DLList *makeDLList(customer *, DLList *, DLList *);
DLList *readFile(char *fileName);
DLList *searchListByName(DLList *list, char *name);
DLList *searchListByPhone(DLList *list, long int phone);
void deleteByName(DLList **, char *);
void deleteByPhone(DLList **, long int);
void freeCustomer(customer *c);
void freeDLList(DLList *);
void freeTree(TNode **);
void insertTail(DLList **listPtr, customer *c);
void insertTail(struct DLList **head_ref, customer *newCustomer);
void printCustomer(customer *c);
void printDLList(DLList *);
void printList(DLList *);
