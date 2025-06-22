// set.c
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int value;
  struct Node *next;
};

struct Set
{
  size_t size;
  struct Node *node;
};

// Helper
static void incrementSize(Set *set)
{
  if (set != NULL)
    set->size++;
}

static void decrementSize(Set *set)
{
  if (set != NULL && set->size > 0)
    set->size--;
}

// Set
struct Set *initializeSet()
{
  Set *head = malloc(sizeof(struct Set));
  if (head != NULL) {
    head->size = 0;
    head->node = NULL;
  }
  return head;
}

bool contains(const Set *head, const int x)
{
  if (head == NULL) {
    return false;
  }
  struct Node *aux = head->node;
  while (aux != NULL) {
    if (aux->value == x) {
      return true;
    }
    aux = aux->next;
  }
  return false;
}

// Always adds at the end if value not already in set
int add(Set *head, int x)
{
  if (head == NULL || contains(head, x)) {
    return -1;
  }
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    return -1;
  }
  newNode->value = x;
  newNode->next = NULL;
  if (head->node == NULL) {
    head->node = newNode;
  } else {
    struct Node *aux = head->node;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = newNode;
  }
  incrementSize(head);
  return 0;
}

int removeFromSet(Set *head, const int x)
{
  if (head == NULL || head->node == NULL) {
    return -1;
  }
  if (head->node->value == x) {
    struct Node *temp = head->node;
    head->node = temp->next;
    free(temp);
    decrementSize(head);
    return 0;
  }
  struct Node *aux = head->node;
  struct Node *prev = head->node;
  while (aux != NULL) {
    if (aux->value == x) {
      prev->next = aux->next;
      free(aux);
      decrementSize(head);
      return 0;
    }
    prev = aux;
    aux = aux->next;
  }
  return -1;
}

int choose(const Set *head)
{
  if (head == NULL || head->node == NULL) {
    return -1;
  }
  return head->node->value;
}

void printSet(const Set *head)
{
  if (head == NULL) return;
  printf("Set : { ");
  struct Node *aux = head->node;
  while (aux != NULL) {
    printf("%d", aux->value);
    if (aux->next != NULL)
      printf(" -> ");
    aux = aux->next;
  }
  printf(" }\n");
}

void freeSet(Set **headPtr)
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