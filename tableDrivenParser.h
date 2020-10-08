#ifndef _Table_h
#define _Table_h

#include "RecursiveParser.h"
extern void createParseTable();
extern bool parsing();
extern int switchChar(char c);
extern int getRow(char* c);
extern int getProduction(int row, int col);
extern void chooseProduction(TREE curr, int production);
extern void freeTable(int **parseTable);
extern void productionNegative(TREE curr);
extern void production1(TREE curr);
extern void production2(TREE curr);
extern void production3(TREE curr);
extern void production4(TREE curr);
extern void production5(TREE curr);
extern void production6(TREE curr);
extern void production7(TREE curr);
extern void production8(TREE curr);
extern void getLabel(char *x, int indent);
extern void printParseTree();
extern void printError();

extern bool parsing();

extern TREE pop();
extern void push(TREE curr);

extern void tryTableDrivenParser();

#endif