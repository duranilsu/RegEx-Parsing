#ifndef _Convert_h
#define _Convert_h

#include "RecursiveParser.h"

#define FAILED NULL

extern TREE nodeE(TREE node);
extern TREE nodeC(TREE node);
extern TREE nodeS(TREE node);
extern TREE nodeST(TREE node);
extern TREE nodeA(TREE node);
extern TREE nodeX(TREE node);

extern void runConvert();
extern TREE convertToExpressionTree(TREE root);
extern void printExpressionTree(TREE root);

#endif


