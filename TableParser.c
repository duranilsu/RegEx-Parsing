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
    push(ct);
    push(s);
    return;
}
/* <CT> -> .<C> | eps.. we have B for <CT> and 0 for eps*/
void makeProduction4()
{
    if (*nextTerminal == '.')
    {
        TREE c = makeNode0('C');
        TREE concat = makeNode0('.');
        push(c);
        push(concat);
        return;
    }
    else
    {
        TREE eps = makeNode0('0');
        push(eps);
        return;
    }
    
}
/* <S> -> <A><ST>..we have P for <ST> */
void makeProduction5()
{
    TREE a = makeNode0('A');
    TREE st = makeNode0('P');
    push(st);
    push(a);
    return;
}
/* <ST> -> *<ST> | eps ..we have P for <ST>*/
void makeProduction6()
{
    if (*nextTerminal == '*')
    {
        TREE st = makeNode0('P');
        TREE star = makeNode0('*');
        push(st);
        push(star);
        return;
    }
    else
    {
        TREE eps = makeNode0('0');
        push(eps);
        return;
    }
}
/*A -> (<E>) | <X> */
void makeProduction7()
{
    if (*nextTerminal == '(')
    {
        TREE e = makeNode0('E');
        TREE open = makeNode0('(');
        TREE closing = makeNode0(')');
        push(closing);
        push(e);
        push(open);
    }
    else 
    {
        TREE x = makeNode0('X');
        push(x);
        return;
    }
}
/* <X> -> a|b|c|d|....|z ..x is a letter */
void makeProduction8()
{
    char curr = *nextTerminal;
    if (is_terminal(curr))
    {
        TREE letter = makeNode0('curr');
        push(letter);
        return;
    }
}
//in case we have no production, we assign it as FAILED
void makeProductionNeg()
{
    push(FAILED);
    return;
}

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

int getRow(char c)
{
    switch(c)
    {
        //s->E$
        //case 's': return 0;//this should be the string with the ENDM, think if this should be there or not
        case 'E': return 1;
        case 'C': return 2;
        case 'F': return 3; //this is ET
        case 'B': return 4;//this is CT
        case 'S': return 5; 
        case 'A': return 6;
        case 'P': return 7; //this is ST
        case 'X': return 8;
        default: return 0;
    }
}
//we map these characters to the column
int getColumn(char c)
{
    if (is_terminal(c)) return 0;

    switch (c)
    {
        case '.': return 1;
        break;
        case '*': return 2;
        break;
        case '|': return 3;
        break;
        case '\0': return 4;
        break;
        case '(': return 5;
        break;
        case ')': return 6;
        break;
        default: return -1;
    }
}

//we can match current input symbol with terminal---if yes, we return true, else false
bool matchTerminal (char c)
{
    if (*nextTerminal == c)
    {
        nextTerminal++;
        return true;
    }
    return false;
}
int getProduction(int row, int column)
{
    return parseTable[row][column];
}

//this is the parser for the table-driven algorithm
bool ParsFunction()
{
    //maybe we could set nextterminal to point to input??--->think of this
    //we follow the algorithm as mentioned in the book (FOCS 11)
    TREE root = makeNode0('E'); //we make the node for the first expression
    push(root);
    while (size != 0)
    {
        //we pop the current node from the stack
        TREE current = pop();

        if (current == FAILED) return false;
        //otherwise,we can check for valid input and get the column
        int column = getColumn(*nextTerminal);
        if (column == -1)
        {
            
        }
    }
}







