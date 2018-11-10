#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
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
void printList(DLList *list);
DLList *readFile(char *fileName);
void printCustomer(customer *c);
void insertTree(DLList *d, TNode **tptr);
TNode *newTNode(DLList *d, int isPhone);
int commands(DLList **listPtr);
customer *searchList(DLList *list, char *name);
void sleep(int);

int main(int argc, char *argv[]) {
  clock_t start_t, end_t, total1_t, total2_t;

  if (argc != 2) {
    printf("wrong number of arguments. Usage ./fastLookup fileName\n");
    return -1;
  }
  start_t = clock();
  DLList *list = (DLList *)readFile(argv[1]);
  end_t = clock();

  printf("It took= %LF seconds to load the file\n ", (long double)(end_t -
  start_t) / CLOCKS_PER_SEC);

  printf("------------------------------------------------------\n");

  // make a search tree by name
  TNode *nameTree = createNameTree(list);
  // print(nameTree);

  // make a search tree by phone number
  TNode *phoneTree = createPhoneTree(list);
  // print(phoneTree);

  char *name = "Motley";
  long int phone = 4074134842;

  char action = getchar();

  if (action == 'd') {
    // start_t = clock();

    customer *res = searchTreeByName(nameTree, name);

    customer *res2 = searchTreeByPhone(phoneTree, phone);

    // end_t = clock();

    // total1_t =  (float)(end_t - start_t) / CLOCKS_PER_SEC;

    if (res != NULL) {
      printf("searching for customer in linked list\n");
      // printCustomer(res);

      start_t = clock();
      time_t s = start_t;

      // customer *res = searchList(list, name);

      end_t = clock();
      time_t e = end_t;
      // printf("end time: %ld\n", end_t);

      // total2_t =  (long double)(end_t - start_t) / CLOCKS_PER_SEC;

      printf("Search by name using tree took %Lf seconds, st %ld en %ld and "
             "searching DLList \n",
             //"took: %ld\n",
             (long double)(end_t - start_t) / CLOCKS_PER_SEC, s, e);
      printCustomer(res);
      printf("Customer 2 (by phone):\n");
      printCustomer(res2);
    } else {
      printf("Customer not found\n");
    }
  }
}

customer *searchList(DLList *list, char *name) {
  if (list == NULL) {
    printf("list is empty\n");
    return NULL;
  }

  while (list != NULL) {
    if (strcmp(list->data->lname, name) == 0) {
      return list->data;
    }
    list = list->next;
  }
}

int commands(DLList **listPtr) {
  char *token, *filename, c, lineCopy[255], line2[255];
  char *line = (char *)NULL;

  line = (char *)readline("> ");
  if (!line) {
    return commands(listPtr);
  }
  strncpy(lineCopy, line, 254); // make copy of line for later
  strncpy(line2, line, 254);    // make copy of line for later

  // getting command from first letter of line
  token = strtok(line2, " ");
  if (NULL == token) {
    free(token);
    return commands(listPtr);
  }
  c = token[0];

  // switch statement for handling commands
  switch (c) {
  case 'n':
    // search for customer by name
    break;
  case 'p':
    // search and return the customer by phone number
    // deleteFlight(listPtr, lineCopy);
    break;
  case 'd':
    // todo delete customer by name from the tree and the linked list
    break;
  case 'q':
    printf("\nQuitting...\n");
    // todo FREE
    exit(0);
    break;
  case '\n':
    break;
  default:
    printf("\nInvalid command \"%c\".\n", c);
    break;
  }
  return commands(listPtr); // call commands again
}

customer *searchTreeByPhone(TNode *tree, long int phoneNum) {
  // printf("searching name tree for %s...\n", name);
  if (tree == NULL) {
    printf("Customer with phone number %ld not found.\n", phoneNum);
    return NULL;
  }
  // check if found customer
  if (tree->phone == phoneNum) {
    printf("Customer with phone number %ld found.\n", phoneNum);
    return tree->data->data;
  }
  // if name we're searching for is after the root name go right
  if (tree->phone < phoneNum) {
    return searchTreeByPhone(tree->left, phoneNum);
  } else {
    return searchTreeByPhone(tree->right, phoneNum);
  }
}

customer *searchTreeByName(TNode *tree, char *name) {
  // printf("searching name tree for %s...\n", name);
  if (tree == NULL) {
    printf("Name not found, returning NULL.\n");
    return NULL;
  }

  if (!strcmp(tree->lname, name)) {
    return tree->data->data;
  }
  // if name we're searching for is before the root name go left
  if (strcmp(tree->data->data->lname, name) < 0) {
    // printf("%s is right of %s\n", name, tree->lname);
    return searchTreeByName(tree->left, name);
  } else {
    // printf("%s is left of %s\n", name, tree->lname);
    return searchTreeByName(tree->right, name);
  }
}

/* newTNode
 * helper function, creates a new tree node with value d
 * returns the address of the new node
 */
TNode *newTNode(DLList *d, int isPhone) {
  TNode *toReturn = (TNode *)malloc(sizeof(TNode));
  toReturn->data = (DLList *)malloc(sizeof(DLList));

  toReturn->data = d;

  if (isPhone) {
    toReturn->phone = d->data->phone;
  } else {
    toReturn->lname = d->data->lname;
  }

  toReturn->left = NULL;
  toReturn->right = NULL;

  return toReturn;
}

/* createNameTree
 * creates a binary search tree with data stored in array a
 */
TNode *createNameTree(DLList *list) {
  TNode *toReturn = newTNode(list, 0); // insert first item from list
  while (list != NULL) {
    insertTree(list, &toReturn);
    list = list->next;
  }
  return toReturn;
}

TNode *createPhoneTree(DLList *list) {
  TNode *toReturn = newTNode(list, 1); // insert first item from list
  while (list != NULL) {
    insertTreePhone(list, &toReturn);
    list = list->next;
  }
  return toReturn;
}
/* insert
 * inserts data item d into tree; note that this is a BST so it is ordered
 */
void insertTreePhone(DLList *d, TNode **tptr) {
  // create new node for data
  TNode *toInsert = newTNode(d, 0);
  // printf("toInsert->data->name: %s\n", toInsert->data->data->lname);
  TNode *curr = *tptr;
  if (curr == NULL) {
    *tptr = toInsert; // make this the tree
    printR(0, *tptr);
    return;
  }
  // check valSue of t to see if new node should be to the right or left of
  // curr
  while (curr != NULL) {
    if (d->data->phone > curr->data->data->phone) { // goes to left
      if (curr->left == NULL) {
        curr->left = toInsert;
        return;
      }
      // keep going left
      curr = curr->left;
    } else { // goes to right
      if (curr->right == NULL) {
        curr->right = toInsert;
        return;
      }
      // keep going right
      curr = curr->right;
    }
  }
}

/* insert
 * inserts data item d into tree; note that this is a BST so it is ordered
 */
void insertTree(DLList *d, TNode **tptr) {
  // create new node for data
  TNode *toInsert = newTNode(d, 0);
  // printf("toInsert->data->data->name: %s\n", toInsert->data->data->lname);
  // printf("toInsert->data->data->phone: %ld\n",
  // toInsert->data->data->phone);

  TNode *curr = *tptr;
  if (curr == NULL) {
    *tptr = toInsert; // make this the tree
    printR(0, *tptr);
    return;
  }
  // check valSue of t to see if new node should be to the right or left of
  // curr
  while (curr != NULL) {
    if (strcmp(d->data->lname, curr->data->data->lname) > 0) { // goes to left
      if (curr->left == NULL) {
        curr->left = toInsert;
        return;
      }
      // keep going left
      curr = curr->left;
    } else { // goes to right
      if (curr->right == NULL) {
        curr->right = toInsert;
        return;
      }
      // keep going right
      curr = curr->right;
    }
  }
}

void printWithTab(int n, customer *data) {
  int i = 0;
  for (i = 0; i < n; i++) {
    printf("   ");
  }
  printf("%s\n", data->lname);
}

void printR(int n, TNode *t) {
  if (t == NULL) {
    // printWithTab(n, 0);  // note: value 0 is used to indicate null
    return;
  }

  // printWithTab(n, t->data);
  printR(n + 1, t->right);
  printf("lname: %s\n", t->data->data->lname);
  printf("%ld\n", t->data->data->phone);
  printR(n + 1, t->left);
}

void print(TNode *t) {
  printf("\nTREE:\n");
  printR(0, t);
}
