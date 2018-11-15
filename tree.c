#include "tree.h"

TNode *deleteTreeByName(TNode *treePtr, char *name) {
  if (treePtr == NULL)
    return treePtr;

  if (strcmp(treePtr->data->data->lname, name) < 0) {
    treePtr->left = deleteTreeByName(treePtr->left, name);
  } else if (strcmp(treePtr->data->data->lname, name) > 0) {
    treePtr->right = deleteTreeByName(treePtr->right, name);
  } else { // found the node to delete check if node is a leaf or only
    if (treePtr->left == NULL) {
      TNode *temp = treePtr->right;
      free(treePtr);
      return temp;
    } else if (treePtr->right == NULL) {
      TNode *temp = treePtr->left;
      free(treePtr);
      return temp;
    }
    TNode *temp = getSmallestNode(treePtr->right->right);
    treePtr->data = temp->data;
    treePtr->lname = temp->lname;
    treePtr->right = deleteTreeByName(treePtr->right, temp->data->data->lname);
  }
  return treePtr;
}

/**
 * returns the smallest node in the given tree
 */
TNode *getSmallestNode(TNode *node) {
  TNode *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

/*
 * search tree by phone number
 */
customer *searchTreeByPhone(TNode *tree, long int phoneNum) {
  if (tree == NULL) {
    printf("Customer with phone number %ld not found.\n", phoneNum);
    return NULL;
  }
  if (tree->data->data->phone == phoneNum) { // check if found customer
    printf("Customer with phone number %ld found.\n", phoneNum);
    return tree->data->data;
  }
  if (tree->data->data->phone < phoneNum)
    return searchTreeByPhone(tree->left, phoneNum); // go left
  else
    return searchTreeByPhone(tree->right, phoneNum); // go right
}

/*
 * searches the given tree for the given name
 */
TNode *searchTreeByName(TNode *tree, char *name) {
  if (tree == NULL)
    return NULL;

  if (strcmp(tree->lname, name) == 0)
    return tree; // if found

  if (strcmp(tree->lname, name) < 0) // look left
    return searchTreeByName(tree->left, name);

  return searchTreeByName(tree->right, name); // look right
}

/*
 * creates a new tree node with value d returns the address of the new node
 */
TNode *newTNode(DLList *d, int isPhone) {
  TNode *toReturn = (TNode *)malloc(sizeof(TNode));
  toReturn->data = (DLList *)malloc(sizeof(DLList));
  toReturn->data = d;

  if (isPhone)
    toReturn->phone = d->data->phone;
  else
    toReturn->lname = d->data->lname;

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
    insertTreeName(list, &toReturn);
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
/*
 * inserts linked list node into tree
 */
void insertTreePhone(DLList *d, TNode **tptr) {
  TNode *toInsert = newTNode(d, 0);

  TNode *curr = *tptr;

  if (curr == NULL) {
    *tptr = toInsert;
    printR(0, *tptr);
    return;
  }

  while (curr != NULL) {
    if (d->data->phone > curr->data->data->phone) {
      if (curr->left == NULL) {
        curr->left = toInsert;
        return;
      }
      curr = curr->left;
    } else {
      if (curr->right == NULL) {
        curr->right = toInsert;
        return;
      }
      curr = curr->right;
    }
  }
}

/*
 * inserts linked list item d into tree
 */
void insertTreeName(DLList *d, TNode **tptr) {
  TNode *toInsert = newTNode(d, 0);

  TNode *curr = *tptr;
  if (curr == NULL) {
    *tptr = toInsert;
    printR(0, *tptr);
    return;
  }

  while (curr != NULL) {
    if (strcmp(d->data->lname, curr->data->data->lname) > 0) {
      if (curr->left == NULL) {
        curr->left = toInsert;
        return;
      }
      curr = curr->left;
    } else {
      if (curr->right == NULL) {
        curr->right = toInsert;
        return;
      }
      curr = curr->right;
    }
  }
}

void print(TNode *t) {
  printf("\nTREE:\n");
  printR(0, t);
}

void printR(int n, TNode *t) {
  if (t == NULL)
    return;

  printR(n + 1, t->right);
  printf("lname: %s\n", t->data->data->lname);
  printf("%ld\n", t->data->data->phone);
  printR(n + 1, t->left);
}

void freeTree(TNode *t) {
  if (t == NULL)
    return;
  freeTree(t->left);
  freeTree(t->right);
  free(t);
}
