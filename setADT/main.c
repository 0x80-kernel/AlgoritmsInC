// main.c
#include "set.h"
#include <stdio.h>

int main()
{
  struct Set *s = initializeSet();
  add(s, 10);
  add(s, 20);
  add(s, 30);
  printSet(s);                                                  // 10 -> 20 -> 30
  removeFromSet(s, 20);
  printSet(s);                                                  // 10 -> 30
  printf("Contains 10: %s\n", contains(s, 10) ? "yes" : "no");  // yes
  printf("First value: %d\n", choose(s));                       // 10
  freeSet(&s);
  return 0;
}
