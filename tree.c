/**
 * tree.c
 * Alex Weininger
 * 11/14/2018
 */

#include "tree.h"

// search tree by phone number
TNode *searchTreeByPhone(TNode *tree, long int phoneNum) {
  if (tree == NULL)
    return NULL;
  if (tree->phone == phoneNum) // check if found customer
    return tree;
  if (tree->phone < phoneNum)
    return searchTreeByPhone(tree->left, phoneNum); // go left
  return searchTreeByPhone(tree->right, phoneNum);  // go right
}

// searches the given tree for the given name
TNode *searchTreeByName(TNode *tree, char *name) {
  if (tree == NULL)
    return NULL;
  if (strcmp(tree->lname, name) == 0)
    return tree;                     // if found
  if (strcmp(tree->lname, name) < 0) // look left
    return searchTreeByName(tree->left, name);
  return searchTreeByName(tree->right, name); // look right
}

// deletes a node in the tree by name
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
    TNode *temp = getSmallestNode(treePtr->right);
    treePtr->data = temp->data;
    treePtr->lname = temp->lname;
    treePtr->right = deleteTreeByName(treePtr->right, temp->data->data->lname);
  }
  return treePtr;
}

// delete a node from the tree by phone
TNode *deleteTreeByPhone(TNode *treePtr, long int phone) {
  if (treePtr == NULL)
    return treePtr;

  if (treePtr->data->data->phone < phone) {
    treePtr->left = deleteTreeByPhone(treePtr->left, phone);

  } else if (treePtr->data->data->phone > phone) {
    treePtr->right = deleteTreeByPhone(treePtr->right, phone);

  } else { // found the node to delete check if node is a leaf or only

    if (treePtr->left == NULL) { // if it does not have a left child
      TNode *temp = treePtr->right;
      free(treePtr);
      return temp;
    } else if (treePtr->right == NULL) { // if it does not have a right child
      TNode *temp = treePtr->left;
      free(treePtr);
      return temp;
    }
    TNode *temp = getSmallestNode(treePtr->right);
    treePtr->data = temp->data;
    treePtr->phone = temp->phone;
    treePtr->right = deleteTreeByPhone(treePtr->right, temp->data->data->phone);
  }
  return treePtr;
}

// creates a new tree based on specified tree type (phone or name)
TNode *createTree(DLList *clist, int phoneTree) {
  TNode *toReturn = NULL;
  while (clist != NULL) {
    if (phoneTree)
      insertTreePhone(newTNode(clist, 1), &toReturn);
    else
      insertTreeName(newTNode(clist, 0), &toReturn);
    clist = clist->next;
  }
  return toReturn;
}

// creates a new tree node with value d returns the address of the new node
TNode *newTNode(DLList *d, int isPhone) {
  TNode *toReturn = (TNode *)malloc(sizeof(TNode));
  toReturn->data = d;
  if (isPhone)
    toReturn->phone = d->data->phone;
  else
    toReturn->lname = d->data->lname;
  toReturn->right = toReturn->left = NULL;
  return toReturn;
}

// insert by phone in order to the bst
void insertTreePhone(TNode *toInsert, TNode **tptr) {
  TNode *curr = *tptr;
  if (curr == NULL) {
    *tptr = toInsert;
    return;
  }
  while (curr != NULL) {
    if (toInsert->phone > curr->phone) {
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

// inserts name into bst
void insertTreeName(TNode *toInsert, TNode **tptr) {
  TNode *curr = *tptr;
  if (curr == NULL) {
    *tptr = toInsert;
    return;
  }
  while (curr != NULL) {
    if (strcmp(toInsert->lname, curr->lname) > 0) {
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

// returns the smallest node in the given tree
TNode *getSmallestNode(TNode *node) {
  TNode *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
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

void freeTree(TNode **tptr) {
  if (*tptr == NULL) {
    return;
  }
  freeTree(&(*tptr)->left);
  freeTree(&(*tptr)->right);
  *tptr = NULL;
  free(*tptr);
}
