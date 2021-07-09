#include "types.h"
#include "opperations_in_stack.h"
#include <stdarg.h>


void addElem(Stack *next,Element element){
    Stack a = malloc(sizeof(struct stacks));
    a->next = *next;
    a->element=element;
    *next=a;
}


void push(Stack *stack,Type type,...){
    va_list ap;
    va_start(ap, type);
    Element element;
    element.type=type;
    switch(type){
        case CHAR:
            element.content.c = va_arg(ap,char);
            break;
        case INT:
            element.content.i = va_arg(ap,int);
            break;
        case STRING:
            element.content.s = va_arg(ap,char *);
            break;
        case DOUBLE:
            element.content.d = va_arg(ap,double);
            break;
        case LIST:
            element.content.l = va_arg(ap,Stack);
            break;
        case FUNCTION:
            element.content.f = va_arg(ap,char *);
            break;
        default:
            fprintf("ERROR in push");
    }
    addElem(stack,element);
    va_end(ap);
}

Element pop(Stack *stack){
    Element element = (*stack)->element;
    Stack aLib=*stack;
    *stack=(*stack)->next;
    free(aLib);
    return element;
}

void printStack(Stack *stack){
    switch((*stack)->element.type){
        case CHAR:
            printf("%c",(*stack)->element.content.c);
            break;
        case INT:
            printf("%d",(*stack)->element.content.i);
            break;
        case STRING:
            printf("%s",(*stack)->element.content.s);
            break;
        case DOUBLE:
            printf("%g",(*stack)->element.content.d);
            break;
        case LIST:
            printStack((*stack)->element.content.l);
            break;
        case FUNCTION:
            printf("{%s}",(*stack)->element.content.f);
            break;
        default:
            fprintf("ERROR in printStack");
    }
}