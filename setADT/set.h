// set.h
#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct Set Set;

Set *initializeSet();
bool contains(const Set *set, int x);
int add(Set *set, int x);
int removeFromSet(Set *set, int x);
int choose(const Set *set);
void printSet(const Set *set);
void freeSet(Set **set);
