/* Collaborators: Anisha Bhattacharya,
                    Godbless Chille,
                    Nilsu Duran
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define FAILED NULL
#define MAX 1000
#ifndef _RecursiveParser_h
#define _RecursiveParser_h
extern int numNodes;
extern int numFree;


//we defined tree as pointer to a struct called node
typedef struct NODE *TREE;
struct NODE {
    char* label;
    int indent;
    TREE leftmostChild, rightSibling;
};

char* lookahead;
//a tree with no children
extern TREE makeNode(char* x, int j);
extern TREE make1Node(char *x, TREE t, int indent);
extern TREE make2Node (char *x, TREE t1, TREE t2, int indent);
extern TREE make3Node (char *x, TREE t1, TREE t2, TREE t3, int indent);
extern TREE make4Node(char *x, TREE t1, TREE t2, TREE t3, TREE t4, int indent);
extern TREE makeNode0(char* x);
//tree with one child
extern TREE makeNode1(char* x, TREE t);
//tree with four children
extern TREE makeNode4(char* x, TREE t1, TREE t2, TREE t3, TREE t4);
// free tree nodes
extern void freeTREE(TREE root);

//Functions for the syntactic categories
extern TREE sync_catE();
extern TREE sync_catC();
extern TREE sync_catET();
extern TREE sync_catS();
extern TREE sync_catCT();
extern TREE sync_catA();
extern TREE sync_catST();
extern TREE sync_catX();
//extern void getLabel(char *x, int indent);
extern void printParseTree();
extern void print(TREE parseTree, int j);
extern void runRecursiveParser();
extern TREE buildRecursiveParser(char *input);
#endif