#include <stdio.h>
#include <string.h>
#include "RecursiveParser.h"
#define MAX 1000
int size = 0;

TREE stack[MAX];

typedef struct Stack Stack;

size = 0;


extern void push(TREE curr);
extern TREE pop();

