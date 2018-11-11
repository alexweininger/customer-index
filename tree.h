#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"

customer *searchTreeByPhone(TNode *tree, long int number);
customer *searchTreeByName(TNode *tree, char *name);
TNode *createNameTree(DLList *list);
TNode *createPhoneTree(DLList *list);
void insertTreePhone(DLList *d, TNode **tptr);
void printR(int n, TNode *t);
void print(TNode *t);
void printWithTab(int n, customer *data);
void insertTreeName(DLList *d, TNode **tptr);
TNode *newTNode(DLList *d, int isPhone);
void deleteTreeByName(struct TNode **, DLList **, char *);
void freeTree(TNode *);
DLList *searchListByName(DLList *list, char *name);
void printList(DLList *list);
void freeCustomer(customer *t);

DLList *readFile(char *fileName);
void printCustomer(customer *c);

int commands(TNode *, TNode *, DLList **);
void freeDLList(DLList *top);
