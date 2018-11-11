#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <time.h>
#include "tree.h"

int main(int argc, char *argv[]) {
  clock_t start_t, end_t, total1_t, total2_t;

  if (argc != 2) {
    printf("Wrong number of arguments. Use ./fs fileName\n");
    return -1;
  }
  start_t = clock();
  DLList *list = (DLList *)readFile(argv[1]);
  end_t = clock();
  long double t = (long double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("It took %LF seconds to load the file.\n", t);

  printf("------------------------------------------------------\n\n");

  TNode *nameTree = createNameTree(list); // make a search tree by name
  // print(nameTree);

  TNode *phoneTree = createPhoneTree(list); // make a phone tree
  // print(phoneTree);

  commands(nameTree, phoneTree, &list);
}

int commands(TNode *nameTreePtr, TNode *phoneTreePtr, DLList **customerList) {
  char *token, *filename, c, lineCopy[255], line2[255], *phoneStr, *name;
  char *line = (char *)NULL;
  long int phoneNumber;

  name = "";
  phoneNumber = -1;

  line = (char *)readline("> ");

  if (!line) {
    return commands(nameTreePtr, phoneTreePtr, customerList);
  }

  strncpy(lineCopy, line, 254); // make copy of line for later
  strncpy(line2, line, 254);    // make copy of line for later

  // getting command from first letter of line
  token = strtok(line2, " ");
  if (NULL == token) {
    free(token);
    return commands(nameTreePtr, phoneTreePtr, customerList);
  }
  c = token[0];

  // switch statement for handling commands
  switch (c) {
  case 'n':
    // search and return the customer by name
    name = strtok(lineCopy, " ");
    name = strtok(NULL, " ");
    if (name == "") {
      printf("Please enter a name to search for.\n");
      break;
    }

    printf("Searching for customer with name: %s\n", name);
    time_t start_t = clock();
    customer *cust2 = searchTreeByName(nameTreePtr, name);
    time_t end_t = clock();
    long double t = (long double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("It took= %LF seconds to find the customer by name.\n ", t);
    printCustomer(cust2);
    break;

  case 'p':
    // search and return the customer by phone number

    phoneStr = strtok(lineCopy, " ");
    phoneStr = strtok(NULL, " ");

    if (phoneStr == NULL) {
      printf("Please enter a number to search for.\n");
      break;
    }
    phoneNumber = atol(phoneStr);
    if (phoneNumber == -1) {
      printf("Please enter a number to search for.\n");
      break;
    }

    printf("Searching for customer with phoneNumber: %ld\n", phoneNumber);
    start_t = clock();
    customer *cust = searchTreeByPhone(phoneTreePtr, phoneNumber);
    end_t = clock();
    long double tt = (long double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nIt took %LF seconds to find customer by phone number.\n\n", t);
    printCustomer(cust);
    break;

  case 'd':
    name = strtok(lineCopy, " ");
    name = strtok(NULL, " ");
    if (name == "") {
      printf("Please enter a name to search for.\n");
      break;
    }
    deleteTreeByName(&nameTreePtr, customerList, name);

    break;

  case 'q':
    printf("\nQuitting...\n");
    freeDLList(*customerList); // free double linked list
    freeTree(nameTreePtr);
    freeTree(phoneTreePtr);
    exit(0);
    break;

  case '\n':
    break;

  default:
    printf("\nInvalid command \"%c\".\n", c);
    break;
  }
  return commands(nameTreePtr, phoneTreePtr,
                  customerList); // call commands again
}
