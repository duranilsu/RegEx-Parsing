#include "RecursiveParser.h"
#ifndef _Table_Parser_h
#define _Table_Parser_h
//choose production from the table--what does it take in though?
char* nextTerminal;
extern void chooseProduction();
extern void push(TREE curr);
extern TREE pop();
//function to get the row based on the given label
extern int getRow(char label);
//function to get the column based on the given column
extern int getColumn(char label);
//function to get the production
extern int getProduction(int row, int column);
//checks if the character we are currently looking at is a terminal
extern int is_terminal(char c);
//checks if it is an operator
extern int is_operator(char c);
//we need to have functions for each production
extern void makeProduction1();
extern void makeProduction2();
extern void makeProduction3();
extern void makeProduction4();
extern void makeProduction5();
extern void makeProduction6();
extern void makeProduction7();
extern void makeProduction8();
extern int getSize ();

extern void makeProductionNeg();
//function to match the terminals
extern bool marchterminal(char c);
//function to parse the given input
//extern bool ParsFunction(TREE root);
extern TREE ParsFunction();
#endif

/*
essentially, these ones help us index to the table in terms of rows and columnns
rows being the syntactic categories and columns being the character (terminals)
*/

//extern int equi_prod(char c);
//extern int equi_char(char c);