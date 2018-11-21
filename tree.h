#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "structs.h"
#include "parser.h"

DLList *searchListByName(DLList *list, char *name);
TNode *createTree(DLList *clist, int phoneTree);
TNode *deleteTreeByName(struct TNode *, char *);
TNode *deleteTreeByPhone(TNode *, long int);
TNode *getSmallestNode(TNode *node);
TNode *newTNode(DLList *d, int isPhone);
TNode *searchTreeByName(TNode *tree, char *name);
TNode *searchTreeByPhone(TNode *tree, long int number);
void freeCustomer(customer *t);
void freeDLList(DLList *top);
void freeTree(TNode **);
void insertTreeName(TNode *, TNode **);
void insertTreePhone(TNode *, TNode **);
void print(TNode *t);
void printCustomer(customer *c);
void printList(DLList *list);
void printR(int n, TNode *t);
void printWithTab(int n, customer *data);
void traverseInOrder(TNode *);
