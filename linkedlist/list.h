// list.h
#pragma once

#include <stdbool.h>

typedef struct List List;

List* initializeList();
void freeList(List **listPtr);
int pushAtBeginning(List *list, int val);
int pushAtEnd(List *list, int val);
int pushAtPos(List *list, int val, int pos);
int deleteValueFromPos(List *list, int pos);
bool contains(const List *list, int val);
int getValueFromPos(List *list, int pos, int *outVal);
int modifyValue(List *list, int val, int pos);
void printList(const List *list);
