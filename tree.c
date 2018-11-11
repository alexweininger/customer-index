#include "tree.h"

TNode *deleteTreeByName(TNode *nameTreePtr, char *name) {

  if (nameTreePtr == NULL) {
    return nameTreePtr;
  }

  if (strcmp(nameTreePtr->data->data->lname, name) < 0) {

    nameTreePtr->left = deleteTreeByName(nameTreePtr->left, name);

  } else if (strcmp(nameTreePtr->data->data->lname, name) > 0) {

    nameTreePtr->right = deleteTreeByName(nameTreePtr->right, name);

  } else { // found the node to delete
    // check if node is a leaf or only
    if (nameTreePtr->left == NULL) {
      TNode *temp = nameTreePtr->right;
      free(nameTreePtr);
      return temp;
    } else if (nameTreePtr->right == NULL) {
      TNode *temp = nameTreePtr->left;
      free(nameTreePtr);
      return temp;
    }

    TNode *temp = getSmallestNode(nameTreePtr->right);
    nameTreePtr->data = temp->data;
    nameTreePtr->right = deleteTreeByName(nameTreePtr->right, temp->data->data->lname);
  }
  return nameTreePtr;
}

TNode *getSmallestNode(TNode *node) {
  TNode *current = node;

  /* loop down to find the leftmost leaf */
  while (current->left != NULL)
    current = current->left;

  return current;
}

customer *searchTreeByPhone(TNode *tree, long int phoneNum) {
  // printf("searching name tree for %s...\n", name);
  if (tree == NULL) {
    printf("Customer with phone number %ld not found.\n", phoneNum);
    return NULL;
  }
  // check if found customer
  if (tree->data->data->phone == phoneNum) {
    printf("Customer with phone number %ld found.\n", phoneNum);
    return tree->data->data;
  }
  // if name we're searching for is after the root name go right
  if (tree->data->data->phone < phoneNum) {
    return searchTreeByPhone(tree->left, phoneNum);
  } else {
    return searchTreeByPhone(tree->right, phoneNum);
  }
}

TNode *searchTreeByName(TNode *tree, char *name) {
  if (tree == NULL) {
    return NULL;
  }

  if (!strcmp(tree->lname, name)) {
    return tree;
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
/* insert
 * inserts data item d into tree; note that this is a BST so it is ordered
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

/* insert
 * inserts data item d into tree; note that this is a BST so it is ordered
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
  if (t == NULL) {
    return;
  }

  printR(n + 1, t->right);
  printf("lname: %s\n", t->data->data->lname);
  printf("%ld\n", t->data->data->phone);
  printR(n + 1, t->left);
}

void freeTree(TNode *t) {
  if (t == NULL) {
    return;
  }

  freeTree(t->left);
  freeTree(t->right);
  free(t);
}
