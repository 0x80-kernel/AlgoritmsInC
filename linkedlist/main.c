#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Head
{
  size_t size;
  struct Node *Node;
};

struct Node
{
  int value;
  struct Node *next;
};

// index starts at 1
struct Node* getNodeAtIndex(const struct Head *head,
                            const int index)
{
  if (head == NULL || index > head->size || index < 1) {
    return NULL;
  }
  struct Node *aux = head->Node;
  for (int i = 1; i < index; i++) {
    aux = aux->next;
  }
  return aux;
}

struct Head* initializeList()
{
  struct Head *head = malloc(sizeof(struct Head));
  if (head != NULL) {
    head->size = 0;
    head->Node = NULL;
  }
  return head;
}

void modifySize(struct Head *head, const bool increment)
{
  if (head == NULL) {
    return;
  }
  if (increment) {
    head->size++;
  } else if (!(increment) && head->size > 0) {
    head->size--;
  }
}

int pushAtbeginning(struct Head *head, const int val)
{
  if (head == NULL) {
    return -1;
  }
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    return -1;
  }
  newNode->value = val;
  newNode->next = head->Node;
  head->Node = newNode;
  modifySize(head, true);
  return 0;
}

int pushAtEnd(struct Head *head, const int val)
{
  if (head == NULL) {
    return -1;
  }
  if (head->size == 0) {
    return pushAtbeginning(head, val);
  }
  struct Node *aux = getNodeAtIndex(head, head->size);
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    return -1;
  }
  newNode->value = val;
  newNode->next = NULL;
  aux->next = newNode;
  modifySize(head, true);
  return 0;
}

// pos starts at 1
int pushAtPos(struct Head *head, const int val,
              const int pos)
{
  if (head == NULL) {
    return -1;
  }
  if (pos < 1 || pos > head->size + 1) { // Out of range
    return -1;
  }
  if (pos == 1) {
    if (pushAtbeginning(head, val) == 0)
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
  modifySize(head, true);
  return 0;
}

bool contains(const struct Head *head, const int val)
{
  if (head == NULL) {
    return false;
  }
  struct Node *aux = head->Node;
  while (aux != NULL) {
    if (aux->value == val) {
      return true;
    }
    aux = aux->next;
  }
  return false;
}

// pos starts at 1
int deleteValueFromPos(struct Head *head, const int pos)
{
  if (head == NULL || pos < 1 || pos > head->size) {
    return -1;
  }
  if (pos == 1) {
    struct Node *temp = head->Node;
    head->Node = temp->next;
    free(temp);
    modifySize(head, false);
    return 0;
  }
  struct Node *prev = getNodeAtIndex(head, pos - 1);
  if (prev == NULL || prev->next == NULL) {
    return -1;
  }
  struct Node *temp = prev->next->next;
  free(prev->next);
  prev->next = temp;
  modifySize(head, false);
  return 0;
}

int modifyValue(struct Head *head, const int val, const int pos)
{
  if (head == NULL || pos < 1 || pos > head->size) {
    return -1;
  }
  struct Node *aux = getNodeAtIndex(
      head, pos); // Since pos is already verified, i dont check it again
  aux->value = val;
  return 0;
}

void printList(const struct Head *head)
{
  if (head == NULL || head->Node == NULL) {
    return;
  }
  struct Node *aux = head->Node;
  while (aux->next != NULL) {
    printf("%d -> ", aux->value);
    aux = aux->next;
  }
  printf("%d\n", aux->value);
}

// outVal works as return
int getValueFromPos(const struct Head *head, const int pos,
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

void freeList(struct Head *head)
{
  if (head == NULL || head->size == 0) {
    return;
  }
  struct Node *aux = head->Node;
  while (aux != NULL) {
    struct Node *temp = aux->next;
    free(aux);
    aux = temp;
  }
  head->size = 0;
  head->Node = NULL;
}

int main()
{
  struct Head *head = initializeList();
  pushAtbeginning(head, 2);                    // Add 2
  pushAtbeginning(head, 5);                    // Add 5
  pushAtbeginning(head, 3);                    // Add 3
  pushAtEnd(head, 10);                         // Add 10 and the end
  printList(head);                             // 3 5 2 10
  modifyValue(head, 100, 1);                   // 100 5 2 10
  pushAtPos(head, 99, 2);                      // 100 99 5 2 10
  printList(head);                             // 100 99 5 2 10
  if (contains(head, 10)) printf("True\n");    // True
  deleteValueFromPos(head, 4);                 // 100 99 5 10
  printList(head);                             // 100 99 5 10
  freeList(head);
  return 0;
}
