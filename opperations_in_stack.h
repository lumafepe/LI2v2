#ifndef ois_
#define ois_
#include "types.h"

void addElem(Stack *next,Element element);
void push(Stack *stack,Type type,...);

Element pop(Stack *stack);
void printStack(Stack *stack);

#endif