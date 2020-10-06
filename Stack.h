#include <stdio.h>
#include <string.h>
#define MAX 100
struct Stack 
{
    char arr[MAX];
    int size;
};

typedef struct Stack Stack;

size = 0;

extern char peek(Stack* pStack);
extern void push(Stack* pStack, char element);
extern char pop(Stack* pStack);
extern int isEmpty(Stack* pStack);
