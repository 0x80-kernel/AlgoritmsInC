// list.c
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int value;
  struct Node *next;
};

struct List
{
  size_t size;
  struct Node *node;
};

// index starts at 1
struct Node* getNodeAtIndex(struct List *head,
                            const int index)
{
  if (head == NULL || index > head->size || index < 1) {
    return NULL;
  }
  struct Node *aux = head->node;
  for (int i = 1; i < index; i++) {
    aux = aux->next;
  }
  return aux;
}

struct List* initializeList()
{
  struct List *head = malloc(sizeof(struct List));
  if (head != NULL) {
    head->size = 0;
    head->node = NULL;
  }
  return head;
}

void incrementSize(struct List *head)
{
  if (head == NULL) {
    return;
  }
  head->size++;
}

void decrementSize(struct List *head)
{
  if (head == NULL || head->size <= 0) {
    return;
  }
  head->size--;
}

int pushAtBeginning(struct List *head, const int val)
{
  if (head == NULL) {
    return -1;
  }
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    return -1;
  }
  newNode->value = val;
  newNode->next = head->node;
  head->node = newNode;
  incrementSize(head);
  return 0;
}

int pushAtEnd(struct List *head, const int val)
{
  if (head == NULL) {
    return -1;
  }
  if (head->size == 0) {
    return pushAtBeginning(head, val);
  }
  struct Node *aux = getNodeAtIndex(head, head->size);
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    return -1;
  }
  newNode->value = val;
  newNode->next = NULL;
  aux->next = newNode;
  incrementSize(head);
  return 0;
}

// pos starts at 1
int pushAtPos(struct List *head, const int val,
              const int pos)
{
  if (head == NULL) {
    return -1;
  }
  if (pos < 1 || pos > head->size + 1) { // Out of range
    return -1;
  }
  if (pos == 1) {
    if (pushAtBeginning(head, val) == 0)
      return 0;
    else
      return -1;
  }
  struct Node *aux = getNodeAtIndex(head, pos - 1);
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    return -1;
  }
  newNode->value = val;
  newNode->next = pos < head->size ? aux->next : NULL;
  aux->next = newNode;
  incrementSize(head);
  return 0;
}

bool contains(const struct List *head, const int val)
{
  if (head == NULL) {
    return false;
  }
  struct Node *aux = head->node;
  while (aux != NULL) {
    if (aux->value == val) {
      return true;
    }
    aux = aux->next;
  }
  return false;
}

// pos starts at 1
int deleteValueFromPos(struct List *head, const int pos)
{
  if (head == NULL || pos < 1 || pos > head->size) {
    return -1;
  }
  if (pos == 1) {
    struct Node *temp = head->node;
    head->node = temp->next;
    free(temp);
    decrementSize(head);
    return 0;
  }
  struct Node *prev = getNodeAtIndex(head, pos - 1);
  if (prev == NULL || prev->next == NULL) {
    return -1;
  }
  struct Node *temp = prev->next->next;
  free(prev->next);
  prev->next = temp;
  decrementSize(head);
  return 0;
}

int modifyValue(struct List *head, const int val, const int pos)
{
  if (head == NULL || pos < 1 || pos > head->size) {
    return -1;
  }
  struct Node *aux = getNodeAtIndex(
      head, pos); // Since pos is already verified, i dont check it again
  aux->value = val;
  return 0;
}

void printList(const struct List *head)
{
  if (head == NULL) return;
  printf("List : [ ");
  struct Node *aux = head->node;
  while (aux != NULL) {
    printf("%d", aux->value);
    if (aux->next != NULL)
      printf(" -> ");
    aux = aux->next;
  }
  printf(" ]\n");
}

// outVal works as return
int getValueFromPos(struct List *head, const int pos,
                    int *outVal)
{
  if (head == NULL || pos < 1 || pos > head->size) {
    return -1;
  }
  struct Node *current = getNodeAtIndex(head, pos);
  if (current == NULL) {
    return -1;
  }
  *outVal = current->value;
  return 0;
}

void freeList(struct List **headPtr)
{
  if (headPtr == NULL || *headPtr == NULL) {
    return;
  }
  struct Node *aux = (*headPtr)->node;
  while (aux != NULL) {
    struct Node *temp = aux->next;
    free(aux);
    aux = temp;
  }
  free(*headPtr);
  *headPtr = NULL;
}
