#include "Stack.h"
#include <stdlib.h>
#include <stdbool.h>


TREE pop ()
{
    if (size == 0)
    {
        printf("---Stack is empty as f-----");
    }
    else 
    {
        size--;
        return stack[size];
    }
}

void push(TREE curr)
{
    if (size < MAX)
    {
        size++;
        stack[size] = curr;
    }
    else
    {
        printf("TOO BIGGGGGGGGGG--that's what she said ;)");
        return;
    }
}
