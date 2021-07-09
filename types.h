#ifndef TYPES_
#define TYPES_

typedef enum tipos{
    CHAR,
    INT,
    STRING,
    DOUBLE,
    FUNCTION,
    LIST
} Tipo;

typedef union contents{
    char c;
    int i;
    char *s;
    double d;
    char *f;
} Content;


typedef struct conteudo{
    Tipo tipo;
    Content content;
}Element;

typedef struct stack {
    Element element;
    struct llist *stack;
} *Stack;


#endif