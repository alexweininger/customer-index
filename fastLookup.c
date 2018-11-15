/**
 * fastLookup.c
 * Alex Weininger
 * Martin Cenek
 * 11/14/2018
 */

#include "tree.h"

int main(int argc, char *argv[]) {
  struct timeval start, end;
  unsigned long long total;

  if (argc != 2) {
    printf("Wrong number of arguments. Use ./fs fileName\n");
    return -1;
  }

  gettimeofday(&start, NULL);
  DLList *list = (DLList *)readFile(argv[1]);
  gettimeofday(&end, NULL);
  total = ((unsigned long long)end.tv_sec * 1000000ULL -
           (unsigned long long)start.tv_sec * 1000000ULL) +
          ((unsigned long long)end.tv_usec - (unsigned long long)start.tv_usec);
  printf("It took %ld uS to load the file.\n", total);

  printf("------------------------------------------------------\n\n");

  TNode *nameTree = createNameTree(list);   // make a search tree by name
  TNode *phoneTree = createPhoneTree(list); // make a phone tree
  commands(nameTree, phoneTree, &list);     // start the user input loop
}

int commands(TNode *nameTreePtr, TNode *phoneTreePtr, DLList **customerList) {
  struct timeval start, end; // time structs
  unsigned long long total;  // total time

  char *token, *filename, c, lineCopy[255], line2[255], *phoneStr, *name;
  char *line = (char *)NULL;
  long int phoneNumber;

  name = "";
  phoneNumber = -1;

  line = (char *)readline("> ");
  if (!line)
    return commands(nameTreePtr, phoneTreePtr, customerList);

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
  case 'n': // search and return the customer by name
    name = strtok(lineCopy, " ");
    name = strtok(NULL, " ");
    if (name == "") {
      printf("Please enter a name to search for.\n");
      break;
    }

    printf("Searching for customer with name: %s\n", name);
    gettimeofday(&start, NULL);
    TNode *cust2Node = searchTreeByName(nameTreePtr, name);
    gettimeofday(&end, NULL);
    total =
        ((unsigned long long)end.tv_sec * 1000000ULL -
         (unsigned long long)start.tv_sec * 1000000ULL) +
        ((unsigned long long)end.tv_usec - (unsigned long long)start.tv_usec);

    if (cust2Node != NULL) {
      printf("Found customer.\n");
      printf("It took %ld uS to find the customer in the tree by name.\n",
             total);
      printCustomer(cust2Node->data->data);
    } else {
      printf("Customer was not found.\n");
      printf("It took %ld uS to try to the customer in the tree by name.\n",
             total);
    }
    break;

  case 'p': // search and return the customer by phone number
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

    gettimeofday(&start, NULL);
    customer *cust = searchTreeByPhone(phoneTreePtr, phoneNumber);
    gettimeofday(&end, NULL);
    total =
        ((unsigned long long)end.tv_sec * 1000000ULL -
         (unsigned long long)start.tv_sec * 1000000ULL) +
        ((unsigned long long)end.tv_usec - (unsigned long long)start.tv_usec);
    if (cust != NULL) {
      printf("It took %ld uS to find the customer by phone.\n", total);
      printCustomer(cust);
    } else {
      printf("It took %ld uS to try and find the customer.\n", total);
    }
    break;

  case 'd': // delete customer by name
    name = strtok(lineCopy, " ");
    name = strtok(NULL, " ");
    if (name == "") {
      printf("Please enter a name to search for.\n");
      break;
    }

    gettimeofday(&start, NULL);
    deleteByName(customerList, name);
    gettimeofday(&end, NULL);
    total =
        ((unsigned long long)end.tv_sec * 1000000ULL -
         (unsigned long long)start.tv_sec * 1000000ULL) +
        ((unsigned long long)end.tv_usec - (unsigned long long)start.tv_usec);
    printf(
        "It took %ld uS to delete the customer from the linked list by name.\n",
        total);

    gettimeofday(&start, NULL);
    nameTreePtr = deleteTreeByName(nameTreePtr, name);
    gettimeofday(&end, NULL);
    total =
        ((unsigned long long)end.tv_sec * 1000000ULL -
         (unsigned long long)start.tv_sec * 1000000ULL) +
        ((unsigned long long)end.tv_usec - (unsigned long long)start.tv_usec);

    TNode *check = searchTreeByName(nameTreePtr, name);
    if (check == NULL) {
      printf("Deleted customer from tree.\n");
      printf("It took %ld uS to delete the customer from the tree by name.\n",
             total);
    } else {
      printf("Did not delete.\n");
      printf("It took %ld uS to try and delete the customer from the tree by "
             "name.\n",
             total);
    }
    break;

  case 'q': // quit and free linked list
    printf("Quitting...\n");
    freeDLList(*customerList); // free double linked list
    freeTree(nameTreePtr);
    freeTree(phoneTreePtr);
    exit(0);
    break;

  case '\n': // new line
    break;

  default: // invalid command
    printf("\nInvalid command \"%c\".\n", c);
    break;
  }
  return commands(nameTreePtr, phoneTreePtr, customerList); // loop
}
