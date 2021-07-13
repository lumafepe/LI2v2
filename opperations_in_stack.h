#ifndef ois_
#define ois_
#include "types.h"
#include "opperations_in_stack.c"

void pushElement(Stack *next,Element element);
void push(Stack *stack,Type type,...);

Element pop(Stack *stack);
void printStack(Stack stack);

#endif