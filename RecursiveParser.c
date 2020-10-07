/* Collaborators: Anisha Bhattacharya,
                    Godbless Chille,
                    Nilsu Duran
*/

#include "RecursiveParser.h"



TREE makeNode(char x, int indent) {
    TREE root;

    root = malloc(sizeof(struct NODE));
    numNodes++;
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

/*
    x
*/
TREE makeNode0(char x) {
    TREE root;

    root = malloc(sizeof(struct NODE));
    numNodes++;
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}
/*
    x
  /
t1
*/
TREE makeNode1(char x, TREE t) {
    TREE root;

    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode2 (char x, TREE t1, TREE t2)
{
    TREE root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}
/*
    x
  /  \       \
t1 --> t2 --> t3
*/
TREE makeNode3 (char x, TREE t1, TREE t2, TREE t3)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

/*
    x
  /  \       \      \
t1 --> t2 --> t3 --> t4
*/
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4) {
    TREE root;

    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}


//lookahead func to b implemented
//we need to implement all the individual funcs

/* <E> -> <C><ET> */
TREE sync_catE ()
{
    TREE c;
    TREE et;
    
    c = sync_catC();
    if (c != NULL)
    {
        et = sync_catET();
        if (et != NULL)
        {
            return makeNode2('E', c, et);
        }
        else {
            return FAILED;
        }
    }
    else {
        return FAILED;
    }
}

//look at this again
/* <ET> -> | <E> | e ..we have F for <ET>*/
TREE sync_catET()
{
    TREE e;

    if (*lookahead == '|')
    {
        lookahead++;
        e = sync_catE();
        if (e != NULL)
        {
            return makeNode2('F', makeNode0('|'), e);
        }
        else 
        {
            return FAILED;
        }
    }
        
    
    else 
    {
        return makeNode1('F', makeNode0('0'));
    }
}
/* <C> -> <S><CT> ..we have B for <CT>*/
TREE sync_catC ()
{
    TREE s;
    TREE ct;

    s = sync_catS();
    if (s != NULL)
    {
        ct = sync_catCT();
        if (ct != NULL)
        {
            return makeNode2('C', s, ct);
        }
        else 
        {
            return FAILED;
        }
    }
    else 
    {
        return FAILED;
    }
}

//check these functions and make sure they work
/* <CT> -> .<C> | e */
TREE sync_catCT()
{
    TREE c;
    if (*lookahead == '.')
    {
        lookahead++;
        c = sync_catC();
        if (c != FAILED)
        {
            return makeNode2('B', makeNode0('.'), c);
        }
        else
        {
            return FAILED;
        }
    }
    else
    {
        return makeNode1('B', makeNode0('0'));
    }
}

/* S -> <A><ST> ..we have P for <ST>*/
TREE sync_catS()
{
    TREE a;
    TREE st;
    a = sync_catA();
    if (a != NULL)
    {
        st = sync_catST();
        if (st != NULL)
        {
            return makeNode2('S', a, st);
        }
        else 
        {
            return FAILED;
        }
    }
    else {
        return FAILED;
    }
}

/* <ST> -> <ST>* | e */
TREE sync_catST ()
{
    TREE st;
    if (*lookahead == '*')
    {
        lookahead++;
        st = sync_catST();
        if (st != FAILED)
        {
            return makeNode2('P', makeNode0('*'), st);
        }
        else 
        {
            return FAILED;
        }
    }
    else 
    {
        return makeNode1('P', makeNode0('0'));
    }
}

/* <A> -> (<E>) | <X> */

//cheeck this one again...arent we making a tree of three?
TREE sync_catA()
{
    TREE e;
    TREE x;

    if (*lookahead == '(')
    {
        lookahead++;
        e = sync_catE();
        if (e != NULL && *lookahead == ')')
        {
            lookahead++;
            return makeNode3('A', makeNode0('('), e, makeNode0(')'));
        }
        else 
        {
            return FAILED;
        }
    }
    else 
    {
        x = sync_catX();
        if (x != NULL)
        {
            return makeNode1('A', x);
        }
        else
        {
            return FAILED;
        }
        
    }
   

    // if (e != NULL)
    // {
    //     x = sync_catX();
    //     if (x != NULL)
    //     {
    //         return makeNode2('E', )
    //     }
    // }
}

TREE sync_catX()
{
    
    if (*lookahead <= 'z' && *lookahead >= 'a')
    {
        char curr = *lookahead;
        lookahead++;
        return makeNode1('X', makeNode0(curr));
    }
 
    return FAILED;
}

/*
Prints the parse tree in the required format
*/
void print(TREE parseTree, int j)
{
    TREE curr;
    for (int i = 0; i <= j; i++)
    {
        printf(" ");
    }
    printf("%c\n", parseTree->label);
    curr = parseTree->leftmostChild;
    while (curr != NULL)
    {
        print(curr, j+1);
        curr = curr ->rightSibling;
    }
}

void freeTREE(TREE root)
{
    if(root->leftmostChild)
    {
        freeTREE(root->leftmostChild);
    }
    if (root->rightSibling)
    {
        freeTREE(root->rightSibling);
    }
    numFree++;
    free(root);
    
}







