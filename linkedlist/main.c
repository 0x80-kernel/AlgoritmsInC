// main.c
#include "list.h"
#include <stdio.h>

int main()
{
  struct List *head = initializeList();
  pushAtBeginning(head, 2);                    // Add 2
  pushAtBeginning(head, 5);                    // Add 5
  pushAtBeginning(head, 3);                    // Add 3
  pushAtEnd(head, 10);                         // Add 10 and the end
  printList(head);                             // List : [ 3 -> 5 -> 2 -> 10 ]
  modifyValue(head, 100, 1);                   // 100 5 2 10
  pushAtPos(head, 99, 2);                      // 100 99 5 2 10
  printList(head);                             // List : [ 100 -> 99 -> 5 -> 2 -> 10 ]
  if (contains(head, 10)) printf("True\n");    // True
  deleteValueFromPos(head, 4);                 // 100 99 5 10
  printList(head);                             // List : [ 100 -> 99 -> 5 -> 10 ]
  freeList(&head);
  return 0;
}