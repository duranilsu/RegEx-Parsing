#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"
#include "TableParser.h"

//now we need to create an array of productions
//subsequently, we need a 2d array which is table

//here is our table...<Anisha will do>
/*
    The base expression is <S>-> <E>$
    <E>
*/

char* nextTerminal;

//this is our table for the parser
    int parseTable[9][7] =
    {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0},
        {3, 0, 0, 0, 0, 3, 0},
        {2, 2, 2, 2, 2, 2, 2},
        {4, 4, 4, 4, 4, 4, 4},
        {5, 0, 0, 0, 0, 5, 0},
        {7, 0, 0, 0, 0, 7, 0},
        {6, 6, 6, 6, 6, 6, 6},
        {8, 0, 0, 0, 0, 0, 0}
    }

/* <E> -> <C><F> we have <ET> as <F> */
void makeProduction1()
{
    TREE C = makeNode0('C');
    TREE et = makeNode0('F');
    push(et);
    push(C);
    return;
}

/* <ET> -> | <E> | epsilon, we have F as <ET> and 0 as epsilon */
void makeProduction2()
{
    if (*nextTerminal == '|')
    {
        TREE e = makeNode0('E');
        TREE pipe = makeNode0('|');
        push(e);
        push(pipe);
    }
    else
    {
        TREE eps = makeNode0('0');
        push(eps);
    }
    
}
/* <C> -> <S><CT> we have B as <CT>*/
void makeProduction3()
{
    TREE s = makeNode0('S');
    TREE ct = makeNode0('B');
    
}
void makeProduction4();
void makeProduction5();
void makeProduction6();
void makeProduction7();
void makeProductionNeg();
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
        //s->E$
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

