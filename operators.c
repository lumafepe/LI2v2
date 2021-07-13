#include "types.h"
#include "opperations_in_stack.h"
#include <math.h>
#include <string.h>

#define SimpleMath(stack,first,second, op){\
    if (areBothInt(first.type,second.type)) push(stack,INT,second.content.i op first.content.i);\
    else push(stack,DOUBLE,toD(second) op toD(first));\
}
#define increaseDecrease(stack,a, op){\
    switch(a.type){\
            case CHAR:\
                push(stack,a.type,a.content.c op 1);\
                break;\
            case INT:\
                push(stack,a.type,a.content.i op 1);\
                break;\
            case DOUBLE:\
                push(stack,a.type,a.content.d op 1);\
                break;\
            default:\
                printf("ERROR in increase decrease");\
        }\
}\


//math
void plus(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (isAnyString(first.type,second.type)) joinString(stack,first,second);
    else if (isAnyList(first.type,second.type)) joinArray(stack,first,second);
    else SimpleMath(stack,first,second,+);
}
void minus(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    SimpleMath(stack,first,second,-);   
}
void mult(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (second.type==LIST) multArray(stack,&(second.content.l),first.content.i);
    else if (second.type==STRING) multArray(stack,&second.content.s,first.content.i);
    else SimpleMath(stack,first,second,*);   
}
void div(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    SimpleMath(stack,first,second,/);   
}
void divisionRest(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    SimpleMath(stack,first,second,%); 
}

void increase(Stack *stack){
    Element first = pop(stack);
    if (first.type==LIST) separeteFirstElemL(stack,first.content.l);
    else if (first.type==STRING) separeteFirstElemS(stack,first.content.s);
    else increaseDecrease(stack,first,+);
}
void decrease(Stack *stack){
    Element first = pop(stack);
    if (first.type==LIST) separeteLastElemL(stack,first.content.l);
    else if (first.type==STRING) separeteLastElemS(stack,first.content.s);
    else increaseDecrease(stack,first,+);
}

void power(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (areBothInt(first.type,second.type)) push(stack,INT,(int) pow(toD(second),toD(first)));
    else push(stack,DOUBLE,pow(toD(second),toD(first)));
}

void and(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    SimpleMath(stack,first,second,&); 
}
void or(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    SimpleMath(stack,first,second,|); 
}
void xor(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    SimpleMath(stack,first,second,^); 
}
void notbitwise(Stack *stack){
    Element a = pop(stack);
    if (a.type==LIST) pushAllElementsFromArrayToStack(stack,a.content.l);//operation in arrays
    else push(stack,INT,~(a.content.i));
}




//operations in the stack
void replicateTop(Stack *stack){
    Element a = pop(stack);
    pushElement(stack,a);
    pushElement(stack,a);
}
void removeLast(Stack *stack){
    Stack a=*stack;
    *stack=(*stack)->next;
    free(a);
}
void switchLastTwo(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    pushElement(stack,first);
    pushElement(stack,second);
}
void rotateLastThree(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    Element third = pop(stack);
    pushElement(stack,first);
    pushElement(stack,third);
    pushElement(stack,second);
}
void copy(Stack *stack){
    Element first = pop(stack);
    pushElement(stack,getNElement(*stack,first.content.i));
}




//logic
void equal(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (second.type==LIST) getElemByPositionL(stack,second.content.l,first.content.i);
    else if (second.type==STRING) getElemByPositionS(stack,second.content.s,first.content.i);
    else push(stack,INT,toD(second)==toD(first));
}
void less(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (second.type==LIST) getFirstElemsByPositionL(stack,second.content.l,first.content.i);
    else if (second.type==STRING) getFirstElemsByPositionS(stack,second.content.s,first.content.i);
    else push(stack,INT,toD(second) < toD(first));
}
void more(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (second.type==LIST) getLastElemsByPositionL(stack,second.content.l,first.content.i);
    else if (second.type==STRING) getLastElemsByPositionS(stack,second.content.s,first.content.i);
    else push(stack,INT,toD(second) > toD(first));
}
void not(Stack *stack){
    Element first = pop(stack);
    push(stack,INT,!(first.content.i));
}
void andWithShortcut(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    pushElement(stack,(toD(second)&& toD(first))?first:generateElement(INT,0));
}

void orWithShortcut(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    pushElement(stack,second.content.i?second:first);
}
void smallest(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (first.type==STRING && second.type==STRING) pushdata(stack,(strcmp(second.content.s,first.content.s)<0)?second:first);
    else pushdata(stack,(toD(second)< toD(first))?second:first);
}
void biggest(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    if (first.type==STRING && second.type==STRING) pushdata(stack,(strcmp(second.content.s,first.content.s)>0)?second:first);
    else pushdata(stack,(toD(second) > toD(first))?second:first);
}
void ifThenElse(Stack *stack){
    Element first = pop(stack);
    Element second = pop(stack);
    Element third = pop(stack);
    pushdata(stack,toD(first)?second:third);
}
//variable


void setVariable(Stack *stack,Element *variables,char c){
    Element a = pop(stack);
    variables[c-65]=a;
}

//io

void printTop(Stack *stack){
    printElement((*stack)->element);
    printf('\n');
}

//conversion

void toInt(Stack *stack){
    Element a = pop(stack);
    switch(a.type){
        case CHAR:
            push(stack,INT,a.content.c);
            break;
        case INT:
            push(stack,INT,a.content.i);
            break;
        case DOUBLE:
            push(stack,INT,(int) a.content.d);
            break;
        case STRING:
            push(stack,INT,atoi(a.content.s));
            break;
        default:
            printf("ERROR in toInt");
        }
}

double toDouble2(Element a){
    switch(a.type){
            case CHAR:
                return (double) a.content.c;
            case INT:
                return (double) a.content.i;
            case STRING:
                return (double) strtod(a.content.s,NULL);
            case DOUBLE:
                return a.content.d;
            default:
                printf("ERROR in toDouble2");
    }
}

void toDouble(Stack *stack){
    Element a = pop(stack);
    push(stack,DOUBLE,toDouble2(a));
}

void toChar(Stack *stack){
    Element a = pop(stack);
    switch(a.type){
        case CHAR:
            push(stack,CHAR,a.content.c);
            break;
        case INT:
            push(stack,CHAR,a.content.i);
            break;
        case DOUBLE:
            push(stack,CHAR,(int) a.content.d);
            break;
        default:
            printf("ERROR in toChar");
        }
}

Stack toList2(Element a){
    Stack s=NULL;
    if (a.type == LIST) s= a.content.l;
    else pushElement(&s,a);
    return s;
}
void toList(Stack *stack){
    Element a = pop(stack);
    push(stack,LIST,toList2(a));
}

char * toString2(Element a){
    char *s;
    switch(a.type){
        case CHAR:
            s=malloc(sizeof(char));
            s[0]=a.content.c;s[2]='\0';
            break;
        case INT:
            s=malloc(1+numberOfDigits(a.content.i));
            itoa(a.content.i,s,10);
            break;
        case LIST:
            s=a.content.l;
            break;
        case STRING:
            s=a.content.s;
            break;
        default:
            printf("ERROR in toString2");
    }
    return s;
}
void toString(Stack *stack){
    Element a = pop(stack);
    push(stack,STRING,toString2(a));
}






//arrays and strings
void pushAllElementsFromArrayToStack(Stack *stack,Stack stk){
    if(stk){
        Stack next=*stack;
        *stack=stk;
        while(stk->next) stk=stk->next;
        stk->next=next;
    }
}

void joinArray(Stack *stack,Element first,Element second){
    Stack arr1 = toList2(first);
    Stack arr2 = toList2(second);
    Stack final;
    if (arr2){
        final = arr2;
        while(arr2->next) arr2=arr2->next;
        arr2->next=arr1;
    }
    else final=arr1;
    push(stack,LIST,final);
}
void joinString(Stack *stack,Element first,Element second){
    char * str1=toString2(first);
    char * str2=toString2(second);
    char *final=malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(final,str1);
    strcat(final,str2);
    free(str1);
    free(str2);
    push(stack,STRING,final);
}

void multArray(Stack *stack,Stack *stk,int times){
    Stack new;
    new=copyList(stk);
    Stack start=new;
    for(int i=1;i<times;i++){
        while(new->next) new=new->next;
        new->next=copyList(stk);
    }
    push(stack,LIST,start);
    destroy(stk);
}

void multString(Stack *stack,char **s,int times){
    char *new=malloc(strlen(*s)*times+1);
    strcpy(new,*s);
    for(int i=1;i<times;i++) strcat(new,*s);
    push(stack,STRING,new);
    free(*s);
}

void range(Stack *stack){
    Element a = pop(stack);
    if (a.type==LIST) push(stack,INT,numberOfElementsInList(a.content.l));
    else if (a.type==STRING) push(stack,INT,strlen(a.content.s));
    else push(stack,INT,1);
}
void getElemByPositionL(Stack *stack,Stack stk,int Invertedpos){
    int pos=numberOfElementsInList(stk)-1-Invertedpos;
    Stack start=stk;
    while (pos--) stk=stk->next;
    pushElement(stack,stk->element);
    destroy(start);
}
void getElemByPositionS(Stack *stack,char *s,int pos){
    push(stack,CHAR,s[pos]);
    free(s);
}

void getFirstElemsByPositionL(Stack *stack,Stack stk,int Invertedpos){
    int pos=numberOfElementsInList(stk)-1-Invertedpos;
    Stack start=stk;
    while (pos--){
        start=stk;
        stk=stk->next;
        free(start);
    }
    push(stack,LIST,stk);
}
void getFirstElemsByPositionS(Stack *stack,char *s,int pos){
    s[pos+1]=0;
    push(stack,STRING,s);
}
void getLastElemsByPositionS(Stack *stack,char *s,int pos){
    char *s2=strdup(s+pos+1);
    free(s);
    push(stack,STRING,s2);
}


getLastElemsByPositionL(Stack *stack,Stack stk,int pos){
    Stack start=stk;
    while (pos--){
        stk=stk->next;
    }
    destroy(stk);
    push(stack,LIST,stk);
}

void separeteLastElemL(Stack *stack,Stack stk){
    push(stack,LIST,stk->next);
    Element a = stk->element;
    free(stk);
    pushElement(stack,a);
}



void separeteLastElemS(Stack *stack,char *s){
    char last=s[strlen(s)-1];
    s[strlen(s)-1]='\0';
    char *s2=strdup(s);
    free(s);
    push(stack,STRING,s2);
    push(stack,CHAR,last);
}

void separeteFirstElemL(Stack *stack,Stack stk){
    Stack aux;
    Element a;
    while (stk && stk->next && stk->next->next) stk=stk->next;
    if (stk->next){
        a = stk->next->element;
        free(stk->next);
        stk->next=NULL;
        }
    else{
        a = stk->element;
        free(stk);
        stk=NULL;
    }
    push(stack,LIST,stk);
    pushElement(stack,a);
}

void separeteFirstElemS(Stack *stack,char *s){
    char first=s[0];
    char *s2=strdup(s+1);
    free(s);
    push(stack,STRING,s2);
    push(stack,CHAR,first);
}























//auxiliary


int areBothInt(Type a,Type b){
    return a==INT && b==INT;
}

int isAnyString(Type a,Type b){
    return a==STRING||b==STRING;
}
int isAnyList(Type a,Type b){
   return a==LIST||b==LIST; 
}

Element getNElement(Stack stack,int n){
    while(n--) stack=stack->next;
    return stack->element;
}
int numberOfDigits(int i){
    int c=1;
    if(i<0){
        c++;
        i=abs(i);    
    }
    while(i>9){
        i=i/10;
        c++;
    }
    return c;
}

Stack copyList(Stack a){
    Stack b;
    if (a){
        b=malloc(sizeof(struct stacks));
        b->element=a->element;
        b->next=copyList(a->next);
    }
    else b=NULL;
    return b;
}
int numberOfElementsInList(Stack a){
    int c=0;
    while (a) {
        a=a->next;
        c++;
    }
    return c;
}