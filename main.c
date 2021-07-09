#include "types.h"
#include "opperations_in_stack.h"

int main(){

    Stack stack;
    push(&stack,INT,15);
    push(&stack,INT,10);
    printStack(stack);
    return 0;
}