#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TableParser.h"



//now we need to create an array of productions
//subsequently, we need a 2d array which is table

//here is our table...<Anisha will do>
/*
    The base expression is <S>-> <E>$
    <E>
*/
int size = 0;
TREE stack[MAX];
char printing[MAX];
int indexForPrinting = 0;
char* start;
// char* nextTerminal;
//it should point to the same character as what lookahead is pointing to
//char* nextTerminal;
//int size = 0;

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
    };

/* <E> -> <C><F> we have <ET> as <F> */
void makeProduction1(TREE root)
{
    int num = root->indent+1;
    TREE C = makeNode("C", num);
    TREE et = makeNode("ET", num);
    push(et);
    push(C);
    return;
}

/* <ET> -> | <E> | epsilon, we have F as <ET> and 0 as epsilon */
void makeProduction2(TREE root)
{
    int num = root->indent+1;
    if (*nextTerminal == '|')
    {
        TREE e = makeNode("E", num);
        TREE pipe = makeNode("|", num);
        push(e);
        push(pipe);
        return;
    }
    else
    {
        TREE eps = makeNode("eps", num);
        push(eps);
        return;
    }
    
}
/* <C> -> <S><CT> we have B as <CT>*/
void makeProduction3(TREE root)
{
    int num = root->indent+1;
    TREE s = makeNode("S", num);
    TREE ct = makeNode("CT", num);
    push(ct);
    push(s);
    return;
}
/* <CT> -> .<C> | eps.. we have B for <CT> and 0 for eps*/
void makeProduction4(TREE root)
{
    int num = root->indent+1;
    if (*nextTerminal == '.')
    {
        TREE c = makeNode("C", num);
        TREE concat = makeNode(".", num);
        push(c);  
        push(concat);
        return;
    }
    else
    {
        TREE eps = makeNode("eps", num);
        push(eps);
        return;
    }
    
}
/* <S> -> <A><ST>..we have P for <ST> */
void makeProduction5(TREE root)
{
    int num = root->indent+1;
    TREE a = makeNode("A", num);
    TREE st = makeNode("ST", num);
    push(st);
    push(a);
    printf("in production five now----\n");
    return;
}
/* <ST> -> *<ST> | eps ..we have P for <ST>*/
void makeProduction6(TREE root)
{
    int num = root->indent+1;
    if (*nextTerminal == '*')
    {
        TREE st = makeNode("ST", num);
        TREE star = makeNode("*", num);
        push(st);
        push(star);
        return;
    }
    else
    {
        printf("in production 6 now----\n");
        TREE eps = makeNode("eps", num);
        push(eps);
        return;
    }
}
/*A -> (<E>) | <X> */
void makeProduction7(TREE root)
{
    int num = root->indent+1;
    if (*nextTerminal == '(')
    {
        TREE e = makeNode("E", num);
        TREE open = makeNode("(", num);
        TREE closing = makeNode(")", num);
        push(closing);
        push(e);
        push(open);
        return;
    }
    else 
    {
        TREE x = makeNode("X", num);
        push(x);
        return;
    }
}
/* <X> -> a|b|c|d|....|z ..x is a letter */
void makeProduction8(TREE root)
{
    int num = root->indent+1;
    char curr = *nextTerminal;
    if (is_terminal(curr))
    {
        char input[2];
        input[0] = curr;
        printf("current input letter is \t :%c \n", input[0]);
        input[1] = '\0';
        TREE letter = makeNode(input, num);
        push(letter);
        return;
    }
    else
    {
        printf("it's not a terminal, let's push\n");
        TREE c = FAILED;
        push(c);
        return;
    }
    
}
//in case we have no production, we assign it as FAILED
void makeProductionNeg(TREE root)
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

int getRow(char* c)
{
    char first = c[0];
    switch(first)
    {
        //s->E$
        //case 's': return 0;//this should be the string with the ENDM, think if this should be there or not
        case 'E': 
            if (c[1] == 'T')
            {
                return 3;
            }
            else if (c[1] == '\0')
            {
                return 1;
            }
            else return 0;
        case 'C': 
            if (c[1] == 'T')
            {
                return 4;
            }
            else if (c[1] == '\0')
            {
                return 2;
            }
            else return 0;
        case 'S':
            if (c[1] == 'T')
            {
                return 7;
            }
            else if (c[1] == '\0')
            {
                return 5;
            }
            else return 0;
        case 'A': 
            if (c[1] == '\0')
            {
                return 6;
            }
            else return 0;
        case 'X': 
         if (c[1] == '\0')
            {
                return 8;
            }
            else return 0;
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

//we need to be able to chooe the productions
void chooseProduction(TREE root, int production)
{
    if (production == 1)
    {
        makeProduction1(root);
        return;
    }
    else if (production == 2)
    {
        makeProduction2(root);
        return;
    }
    else if (production == 3)
    {
        makeProduction3(root);
        return;
    }
    else if (production == 4)
    {
        makeProduction4(root);
        return;
    }
    else if (production == 5)
    {
        printf("choosing five here------\n");
        makeProduction5(root);
        return;
    }
    else if (production == 6)
    {
        makeProduction6(root);
        return;
    }
    else if (production == 7)
    {
        makeProduction7(root);
        return;
    }
    else if (production == 8)
    {
        makeProduction8(root);
        return;
    }
    else
    {
        makeProductionNeg(root);
        return;
    }
    
}

int getSize ()
{
    return size;
}

//this is the case where a tree is returned and printed by the main function
//the problem with this method is that I am not sure about whether there are changes being made on the root tree that is created by us. 
//we need to call makeNode everytime we get a production
//I am not entirely sure about how
// it only returns <E> 
//Q1:where are we making nodes for this parsing function??
//we do it on root 
//curr is the tree on top of the stack so we cannot use that 
bool ParsFunction()
{
    //maybe we could set nextterminal to point to input??--->think of this
    //we follow the algorithm as mentioned in the book (FOCS 11)
    printf("Just got in\n");
    TREE root = makeNode("E", 0); //we make the node for the first expression
    printf("The root is given value %s\n", root->label);
    push(root);
    printf("push successfull--- %s", root->label);
    printf("The root is pushed on the stack\n");
    while (size != 0)
    {
        //we pop the current node from the stack
        TREE current = pop();
        printf("pop successfull--- %s\n", current->label);
        //printf("Our label is currently: %s \t our terminal is: %c", current->label, *nextTerminal);
        printf("got the topmost tree in curr\n");
        

        if (current == FAILED) 
        {
            printf("Invalid input--1\n");
            return false;
        }
        //otherwise,we can check for valid input and get the column
        printf("current label is----\t %s\n: ", current->label);
        int column = getColumn(*nextTerminal);
        if (column == -1)
        {
            if (current!= FAILED) 
            {
                freeTREE(current);
            }
            printf("Invalid input--2\n");
            return false;
        } 
        //get rows by the labels
        int row = getRow(current->label);
        printf("We are in row: %i\t and column %d \t\n: ",row, column);
        int production = getProduction(row, column);
        printf("the current production is\t %d %d:\n ", production, row);
        //printf("curr-label[0] is -- %c\tand NT is -- %c", current->label[0], *nextTerminal);
        //printf("the value of row is %d: \n", row);
        if (row > 0)
        {
            chooseProduction(current, production);
        }
        else if (*nextTerminal == current->label[0])
        {
            //move on to next char at the input
            nextTerminal+=sizeof(char);
            printf("Next terminal is %s \n", nextTerminal);
        }
        else 
        {
            if (strcmp(current->label, "eps") != 0 && *nextTerminal != current->label[0])
            {
                printf("before I fail, label here is \t%s: \n", current->label);
                if (current != FAILED) 
                {
                    printf("Current label is: --- %s\n", current->label);
                    printf("Nextterminal is currently--- %c\n", *nextTerminal);
                    freeTREE(current);
                    printf("Invalid input--3\n");
                    return false;
                }
            }
        }
        if (current == FAILED)
        {
            printf("Invalid input--4\n");
            return false;
            
        }
        else
        {
            getLabel(current->label, current->indent);
            freeTREE(current);
            //return root;
            //if i returned root here-- it would just give me <E> that is why it is best to do nothing
            //return current;
            //freeTREE(current);
        }
        
    }
    if (*nextTerminal != '\0')
    {
        printf("Invalid input--5\n");
        return false;
    }
    return true;
}

void runTableParser()
{
    start = (char*) malloc(sizeof(char)*256);
    bool flag = true;
    printf("-------------------------\n");
    printf("Trying Table Driven Parser...\n");
    while (flag){
        printf("\tEnter expression here (\"quit\" to quit and no more than 255 characters):");
        char input[256];
        scanf("%255s",input);
        if (strcmp(input,"quit") == 0){
            flag = false;
        }
        else {
            printf("Result for \"%s\":\n \n", input);
            nextTerminal = start;
            strcpy(nextTerminal,input);
            if (!ParsFunction()){
                printf("Invalid input\n");
            }
            else {
                printParseTree();
            }
            while (size != 0){
                TREE curr = pop();
                freeTREE(curr);
            }
        }
        printf("\n");
    }
    free(start);
    //freeTable(parseTable);
    //freeStack();
    //free(printing);
}

//this is the parser for the table-driven algorithm
//the tree will be formed with the root as <E> which is the start expression

// bool ParsFunction(TREE root)
// {
//     //maybe we could set nextterminal to point to input??--->think of this
//     //we follow the algorithm as mentioned in the book (FOCS 11)
//     // root = makeNode('E'); //we make the node for the first expression
//     // push(root);
//     while (size != 0)
//     {
//         printf("Size of the stack is not 0 yet\n");
//         //we pop the current node from the stack
//         TREE current = pop();
//         printf("just popped the tree on the top\n");
//         if (current == FAILED) 
//         {
//             printf("current is NULL -which means it has failed");
//             return false;
//         }
//         //otherwise,we can check for valid input and get the column
//         /*
//         there is definately something wrong with our nextTerminal -it is not initialized its just a pointer pointing to nothing rn
//         */
//         printf("maybe there is a problem with next terminal? I am not sure why the coulmn is not working %s", nextTerminal);
//         int column = getColumn(*nextTerminal);
//         printf("just got the columns now!\n");

//         if (column == -1)
//         {           
//             //if (current!= FAILED) freeTREE(current);
//             return false;
//         }
//         //get rows by the labels
//         int row = getRow(current->label);
//         printf("just got the rows now!\n");
//         int production = getProduction(row, column);
//         if (row > 0)
//         {
//             chooseProduction(production);
//         }
//         else
//         {
//             if (*nextTerminal == current->label)
//             {
//                 nextTerminal++;
//             }
//             else
//             {
//                 if (!(*nextTerminal == current->label && current->label == 0))
//                 {
//                     if (current != FAILED) 
//                     {
//                         //freeTREE(current);
//                         return false;
//                     }
//                 }
//             }

//         }
//         if (current == FAILED)
//         {
//             return false;
//         }
//         else
//         {
//             //freeTREE(current);
//         }
        
//     }
//     if (!(*nextTerminal == '\0'))
//     {
//         return false;
//     }
//     return true;
// }
TREE pop ()
{
    TREE curr;
    if (size > 0)
    {
        size--;
        printf("size of stack is now: \t%d", size);
        curr =stack[size];
    }
    return FAILED;
}

void push(TREE curr)
{
    if (size < MAX)
    {
        stack[size] = curr;
        size++;
    }
    else
    {
        printf("TOO BIGGGGGGGGGG--that's what she said ;)");
        return;
    }
}

//get printing line for node
void getLabel(char* x, int indent) {
    int index = 0;
    while (index < indent){
        printing[indexForPrinting] = ' ';
        indexForPrinting++;
        printing[indexForPrinting] = ' ';
        indexForPrinting++;
        index++;
        //printf("  ");
    }
    int i = 0;
    while (x[i] != '\0'){
        printing[indexForPrinting] = x[i];
        indexForPrinting++;
        i++;
    }
    //printf("%s\n",x);
    printing[indexForPrinting] = '\n';
    indexForPrinting++;
}

//print parse tree 
void printParseTree(){
    printing[indexForPrinting] = '\0';
    int i = 0;
    while (printing[i] != '\0'){
        printf("%c",printing[i]);
        i++;
    }
    indexForPrinting = 0;
}









