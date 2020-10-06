/* Collaborators: Anisha Bhattacharya,
                    Godbless Chille,
                    Nilsu Duran
*/
#include <stdlib.h>
#include <stdio.h>
#define FAILED NULL

//we defined tree as pointer to a struct called node
typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

TREE parseTree;

char* lookahead;
//a tree with no children
extern TREE makeNode0(char x);
//tree with one child
extern TREE makeNode1(char x, TREE t);
//tree with four children
extern TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);

//Functions for the syntactic categories
extern TREE sync_catE();
extern TREE sync_catC();
extern TREE sync_catET();
extern TREE sync_catS();
extern TREE sync_catCT();
extern TREE sync_catA();
extern TREE sync_catST();
extern TREE sync_catX();
extern void print(TREE parseTree, int j);
