#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"
#include "TableParser.h"

//now we need to create an array of productions
//subsequently, we need a 2d array which is table

int is_terminal(char c)
{
    if (c <= 'z' && c >= 'a')
    {
        return true;
    }
    return false;
}

int is_operator(char c)
{
    switch(c)
    {
        case '|': return true;
        case '.': return true;
        case '*': return true;
        case ')': return true;
        case '(': return true;
        default: return false;
    }
}

int equi_prod(char c)
{
    switch(c)
    {
        case 's': return 0;//this should be the string with the ENDM, think if this should be there or not
        case 'E': return 1;
        case 'C': return 2;
        case 'F': return 3; //this is ET
        case 'S': return 4;
        case 'B': return 5; //this is CT
        case 'A': return 6;
        case 'P': return 7; //this is ST
        default: return 0;
    }
}

int equi_char(char c)
{
    switch (c)
    {
        case '|': return 0;
        break;
        case '.': return 1;
        break;
        case '*': return 2;
        break;
        case '(': return 3;
        break;
        case ')': return 4;
        break;
        case '$': return 5;
        break;
        default: return 10;
    }
}
int make_table (char* input)
{
    //now we need to create an array of productions
//subsequently, we need a 2d array which is table
//we will also need to make a parse tree from the working of the table
}
