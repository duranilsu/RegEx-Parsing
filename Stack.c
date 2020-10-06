#include "Stack.h"
#include <stdlib.h>
#include <stdbool.h>

char peek(Stack* pStack)
{
    if (pStack -> size == 0)
    {
        printf("----Stack is empty----");
    }
    return pStack->arr[pStack->size-1];
}

char pop (Stack* pStack)
{
    if (pStack->size == 0)
    {
        printf("---Stack is empty as f-----");
    }
    else 
    {
        char output = pStack->arr[(pStack->size)-1];
        pStack->size--;
    }
}

void push(Stack* pStack, char element)
{
    if (pStack->size < MAX)
    {
        pStack->size++;
        pStack->arr[(pStack->size) - 1] = element;
    }
    else
    {
        printf("TOO BIGGGGGGGGGG--that's what she said ;)");
        return;
    }
}

int isEmpty(Stack* pStack)
{
    if (pStack->size == 0)
    {
        printf("I got nothing dude! ;(");
        return true;
    }
    return false;
}