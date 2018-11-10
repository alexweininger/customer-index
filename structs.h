#ifndef STRUCTS
#define STRUCTS

typedef struct customer {
  char *fname;
  char *lname;
  char *company;
  char *address;
  char *city;
  char *county;
  char *state;
  char *zip;
  long int phone;
  long int fax;
  char *email;
  char *web;
} customer;

typedef struct DLList {
  struct DLList *prev;
  struct DLList *next;
  customer *data;
} DLList;

typedef struct TNode {
  struct TNode *right;
  struct TNode *left;
  union {
    char *lname;
    long int phone;
  };
  DLList *data;

} TNode;

#endif
