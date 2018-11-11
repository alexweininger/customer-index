#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

const int LINE_LEN = 2000;
// prints all fields of the customer struct
void printCustomer(customer *t) {
  if (t != NULL) {
    printf("%s, %s, %s, %s, %s, %s, %s, %s, %ld, %ld, %s, %s\n", t->fname,
           t->lname, t->company, t->address, t->city, t->county, t->state,
           t->zip, t->phone, t->fax, t->email, t->web);
  }
}
/*
  parse a line from a file and load the customer object
  strtok - tokenizes the line
        the csv file has the delimiter -- "," since each field
        starts and ends with " and individual fields are separated by ,
  strdup - used for char* fields, makes a memory copy of
           the tokenized fields (tokens) from stack to heap
*/
customer *parseLine(customer *t, char *line) {
  // printf("line: %s \n", line);
  const char *tokens;
  tokens = strtok(line, "\",\"");
  t->fname = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->lname = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->company = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->address = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->city = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->county = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->state = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->zip = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->phone = atol(tokens);
  tokens = strtok(NULL, "\",\"");
  t->fax = atol(tokens);
  tokens = strtok(NULL, "\",\"");
  t->email = strdup(tokens);
  tokens = strtok(NULL, "\",\"");
  t->web = strdup(tokens);
  return t;
}

void freeCustomer(customer *t) {
  free(t->fname);
  free(t->lname);
  free(t->company);
  free(t->address);
  free(t->city);
  free(t->county);
  free(t->state);
  free(t->zip);
  free(t->email);
  free(t->web);
  free(t);
}

DLList *readFile(char *fileName) {

  FILE *fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("Could not open file\n");
    return NULL;
  }

  DLList *top = NULL;
  DLList **listPtr = &top;

  char line[LINE_LEN]; // temporary stack buffer to read lines into
  while (fgets(line, LINE_LEN, fp)) {
    customer *tmp = malloc(sizeof(struct customer));
    if (tmp == NULL) {
      printf("Could not allocate mamory for a customer\n");
      return NULL;
    }

    customer *c = parseLine(tmp, line);
    // printCustomer(c);
    // printf("phoen: %ld\n", c->phone);
    append(listPtr, c);

    // freeCustomer(tmp); //for testing purposes, comment out as needed
  }
  fclose(fp);
  // printf("printing list:--------------------------\n\n");
  // printList(*listPtr);
  return *listPtr;
}

/* Given a reference (pointer to pointer) to the head
   of a DLL and an int, appends a new node at the end  */
void append(struct DLList **head_ref, customer *newCustomer) {

  // allocate new node
  struct DLList *new_node = makeDLList(newCustomer, NULL, NULL);

  struct DLList *last = *head_ref;

  // if the list is empty set the new nodes prev pointer to NULL
  if (*head_ref == NULL) {
    new_node->prev = NULL;
    *head_ref = new_node;
    return;
  }

  // go to the last node of the dllist
  while (last->next != NULL)
    last = last->next;

  // set the last node's next pointer to the new node
  last->next = new_node;

  // set the new node's prev pointer to the current last node
  new_node->prev = last;

  return;
}

void deleteByName(DLList ** listPtr, char * name) {
  DLList *node = NULL;
  node = searchListByName(*listPtr, name);

  printf("here 2\n");

  DLList * prevNode = node->prev;

  prevNode->next = node->next;

  if (node->next != NULL) {
    node->next->prev = prevNode;
  }
}

DLList * searchListByName(DLList * list, char * name) {
  printf("Searching for customer with name: %s\n", name);

  while (list != NULL) {
    if (strcmp(list->data->lname, name) == 0) {
      printf("found customer in list\n");
      return list;
    }
    list = list->next;
  }
  printf("Did not find customer in list.\n");
  return NULL;
}

/*
 * allocates a node with given flight and returns the node
 */
DLList *makeDLList(customer *c, DLList *next, DLList *prev) {

  DLList *np = (DLList *)malloc(sizeof(struct DLList));
  np->data = (struct customer *)malloc(sizeof(struct customer));

  np->data->fname = c->fname;
  np->data->lname = c->lname;
  np->data->company = c->company;
  np->data->address = c->address;
  np->data->city = c->city;
  np->data->county = c->county;
  np->data->state = c->state;
  np->data->phone = c->phone;
  np->data->fax = c->fax;
  np->data->zip = c->zip;
  np->data->email = c->email;
  np->data->web = c->web;

  np->next = prev;
  np->prev = prev;

  return np;
}

/*
 * prints the linked list of customers
 */
void printList(DLList *node) {

  if (node == NULL) {
    printf("customer list is null\n");
    return;
  }

  printf("\n----- Customer list -----\n");
  while (node != NULL) {
    printCustomer(node->data);
    node = node->next;
  }
  printf("-----------------------\n\n");
}

/*
 * frees the linked list of customers
 */
void freeDLList(DLList *top) {
  DLList *curr = top;
  DLList *temp = NULL;
  while (curr != NULL) {
    temp = curr;
    curr = curr->next;
    freeCustomer(temp->data);
    free(temp);
  }
}
