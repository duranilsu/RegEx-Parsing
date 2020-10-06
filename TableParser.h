#include "RecursiveParser.h"


//choose production from the table--what does it take in though?
extern chooseProduction();
//function to get the row based on the given label
extern getRow(char label);
//function to get the column based on the given column
extern getColumn(char label);
//function to get the production
extern int getProduction(int row, int column);
//checks if the character we are currently looking at is a terminal
extern int is_terminal(char c);
//checks if it is an operator
extern int is_operator(char c);
//function to free the allocated memory
void freeTable(int** parseTable);
//we need to have functions for each production
void makeProduction1();
void makeProduction2();
void makeProduction3();
void makeProduction4();
void makeProduction5();
void makeProduction6();
void makeProduction7();
void makeProduction8();

void makeProductionNeg();
//function to match the terminals
bool marchterminal(char c);
//function to parse the given input
bool parsing()
{

}



/*
essentially, these ones help us index to the table in terms of rows and columnns
rows being the syntactic categories and columns being the character (terminals)
*/

//extern int equi_prod(char c);
//extern int equi_char(char c);