#ifndef TYPES_
#define TYPES_

typedef enum types{
    CHAR,
    INT,
    STRING,
    DOUBLE,
    FUNCTION,
    LIST
} Type;

typedef union contents{
    char c;
    int i;
    char *s;
    double d;
    char *f;
    Stack l; 
} Content;


typedef struct elements{
    Type type;
    Content content;
}Element;

typedef struct stacks {
    Element element;
    struct stacks *next;
} *Stack;


#endif