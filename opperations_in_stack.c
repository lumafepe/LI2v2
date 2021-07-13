#include "types.h"
#include "opperations_in_stack.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void pushElement(Stack *next,Element element){
    Stack a = malloc(sizeof(struct stacks));
    a->next = *next;
    a->element=element;
    *next=a;
}


Element generateElement(Type type,...){
    va_list ap;
    va_start(ap, type);
    Element element;
    element.type=type;
    switch(type){
        case CHAR:
            element.content.c = (char) va_arg(ap,int);
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
            printf("ERROR in generateElement");
    }
    va_end(ap);
    return element;
}

void push(Stack *stack,Type type,...){
    va_list ap;
    va_start(ap, type);
    Element element = generateElement(type,ap);
    pushElement(stack,element);
    va_end(ap);
}


Element pop(Stack *stack){
    Element element = (*stack)->element;
    Stack aLib=*stack;
    *stack=(*stack)->next;
    free(aLib);
    return element;
}



void printElement(Element element){
    switch(element.type){
            case CHAR:
                printf("%c",element.content.c);
                break;
            case INT:
                printf("%d",element.content.i);
                break;
            case STRING:
                printf("%s",element.content.s);
                break;
            case DOUBLE:
                printf("%g",element.content.d);
                break;
            case LIST:
                printStack(element.content.l);
                break;
            case FUNCTION:
                printf("{%s}",element.content.f);
                break;
            default:
                printf("ERROR in printElement");
        }
}

void printStack(Stack stack){
    if(stack){
        printStack(stack->next);
        printElement(stack->element);
    }
}
Element * generateVariables(){
    Element *variables = malloc(26*sizeof(struct elements));
    variables['A'-65]=generateElement(INT,10);
    variables['B'-65]=generateElement(INT,11);
    variables['C'-65]=generateElement(INT,12);
    variables['D'-65]=generateElement(INT,13);
    variables['E'-65]=generateElement(INT,14);
    variables['F'-65]=generateElement(INT,15);
    variables['N'-65]=generateElement(CHAR,'\n');
    variables['S'-65]=generateElement(CHAR,' ');
    variables['X'-65]=generateElement(INT,0);
    variables['Y'-65]=generateElement(INT,1);
    variables['Z'-65]=generateElement(INT,2);
    return variables;
}

void destroy(Stack *stack){
    if(*stack){
        destroy((*stack)->next);
        free(*stack);
    }
}