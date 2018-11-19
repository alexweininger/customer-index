/**
 * fastLookup.c
 * Alex Weininger
 * Martin Cenek
 * 11/14/2018
 */

#include "tree.h"

static char *line = (char *)NULL;

int main(int argc, char *argv[]) {
  struct timeval start, end;
  if (argc != 2) {
    printf("Wrong number of arguments. Use ./fs fileName\n");
    return -1;
  }
  gettimeofday(&start, NULL);
  DLList *list = (DLList *)readFile(argv[1]);
  gettimeofday(&end, NULL);
  printf("It took %ld uS to load the file.\n", totalTime(start, end));
  printf("------------------------------------------------------\n\n");
  TNode *nameTree = createTree(list, 0);  // make a search tree by name
  TNode *phoneTree = createTree(list, 1); // make a phone tree
  commands(&nameTree, &phoneTree, &list); // start the user input loop
}

// method to read and execute commands from user input
int commands(TNode **nameTreePtr, TNode **phoneTreePtr, DLList **customerList) {
  struct timeval start, end; // time structs
  char *token, *filename, lineCopy[255], line2[255], *phoneStr, *name;
  long int phoneNumber;
  DLList *nodeToDelete = NULL;
  name = "";
  phoneNumber = -1;

  line = (char *)readline("> ");
  if (!line)
    commands(nameTreePtr, phoneTreePtr, customerList);

  strncpy(lineCopy, line, 254); // make copy of line for later
  strncpy(line2, line, 254);    // make copy of line for later

  // getting command from first letter of line
  token = strtok(line2, " ");
  if (NULL == token)
    commands(nameTreePtr, phoneTreePtr, customerList);

  // switch statement for handling commands
  switch (token[0]) {
  case 'n': // search and return the customer by name
    name = strtok(lineCopy, " ");
    name = strtok(NULL, " ");

    if (name == "") {
      printf("Please enter a name to search for.\n");
      break;
    } else
      printf("Searching for customer with name: %s\n", name);

    gettimeofday(&start, NULL);
    TNode *node = searchTreeByName(*nameTreePtr, name);
    gettimeofday(&end, NULL);

    if (node != NULL) {
      if (node->data->data != NULL) {
        printCustomer(node->data->data);
        printf("Found customer by name from tree");
      }
    } else
      printf("Customer was not found. Completed search in");
    printf(" in %ld uS.\n", totalTime(start, end));
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
    TNode *cust = searchTreeByPhone(*phoneTreePtr, phoneNumber);
    gettimeofday(&end, NULL);

    if (cust != NULL) {
      if (cust->data->data != NULL) {
        printf("%ld uS to find customer by phone.\n", totalTime(start, end));
        printCustomer(cust->data->data);
      }
    } else {
      printf("%ld uS to try and find customer.\n", totalTime(start, end));
    }
    break;

  case 'd': // delete customer by name
    name = strtok(lineCopy, " ");
    name = strtok(NULL, " ");
    if (name == NULL || name == "") {
      printf("Please enter a name to delete.\n");
      break;
    }

    nodeToDelete = searchListByName(*customerList, name);

    if (nodeToDelete == NULL) {
      printf("Could not find customer with name: %s\n", name);
      break;
    }

    // delete from linked list
    gettimeofday(&start, NULL);
    deleteByName(customerList, name);
    gettimeofday(&end, NULL);

    printf("Took %ld uS to delete from list by name.\n",
           totalTime(start, end));

    // delete from tree
    gettimeofday(&start, NULL);
    *nameTreePtr = deleteTreeByName(*nameTreePtr, nodeToDelete->data->lname);
    gettimeofday(&end, NULL);

    *phoneTreePtr = deleteTreeByPhone(*phoneTreePtr, nodeToDelete->data->phone);
    *nameTreePtr = deleteTreeByName(*nameTreePtr, nodeToDelete->data->lname);

    printf("Deleted customer from tree. ");
    printf("Took %ld uS.\n", totalTime(start, end));
    break;
  case 'k': // delete customer by phone

    phoneStr = strtok(lineCopy, " ");
    phoneStr = strtok(NULL, " ");
    if (phoneStr == NULL || phoneStr == "") {
      printf("Please enter a number to delete.\n");
      break;
    }
    phoneNumber = atol(phoneStr);
    if (phoneNumber < 0) {
      printf("Please enter a valid number to delete.\n");
      break;
    }

    // find node to delete
    nodeToDelete = searchListByPhone(*customerList, phoneNumber);
    if (nodeToDelete == NULL) {
      printf("Could not find customer with phone: %ld.\n", phoneNumber);
      break;
    }

    // delete node from list and time it
    gettimeofday(&start, NULL);
    deleteByPhone(customerList, phoneNumber);
    gettimeofday(&end, NULL);

    printf("Took %ld uS to delete from list.\n", totalTime(start, end));

    *nameTreePtr = deleteTreeByName(*nameTreePtr, nodeToDelete->data->lname);
    gettimeofday(&start, NULL);
    *phoneTreePtr = deleteTreeByPhone(*phoneTreePtr, nodeToDelete->data->phone);
    gettimeofday(&end, NULL);

    printf("Deleted customer from tree by phone. ");
    printf("Took %ld uS\n", totalTime(start, end));

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
    printf("\nInvalid command \"%c\".\n", token[0]);
  }
  return commands(nameTreePtr, phoneTreePtr, customerList); // loop
}

unsigned long long totalTime(struct timeval start, struct timeval end) {
  return ((unsigned long long)end.tv_sec * 1000000ULL -
          (unsigned long long)start.tv_sec * 1000000ULL) +
         ((unsigned long long)end.tv_usec - (unsigned long long)start.tv_usec);
}
