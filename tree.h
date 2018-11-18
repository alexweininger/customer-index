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

TNode *searchTreeByPhone(TNode *tree, long int number);
DLList *readFile(char *fileName);
DLList *searchListByName(DLList *list, char *name);
int commands(TNode **, TNode **, DLList **);
TNode *createNameTree(DLList *list);
TNode *createPhoneTree(DLList *list);
TNode *deleteTreeByName(struct TNode *, char *);
TNode * deleteTreeByPhone(TNode *, long int);
TNode *getSmallestNode(TNode *node);
TNode *newTNode(DLList *d, int isPhone);
TNode *searchTreeByName(TNode *tree, char *name);
void freeCustomer(customer *t);
void freeDLList(DLList *top);
void freeTree(TNode **);
void insertTreeName(DLList *d, TNode **);
void insertTreePhone(DLList *d, TNode **);
void print(TNode *t);
void printCustomer(customer *c);
void printList(DLList *list);
void printR(int n, TNode *t);
void printWithTab(int n, customer *data);
void traverseInOrder(TNode *);
