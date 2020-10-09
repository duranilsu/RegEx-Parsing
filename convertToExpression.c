#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "convertToExpression.h"
#include "RecursiveParser.h"

char* concat(char* a, char* b);

void runConvert() {
    bool flag = true;
    printf("-------------------------\n");
    printf("Converting from parse TREE to expression TREE...\n");
    while (flag){
        printf("\tEnter expression here (\"quit\" to quit and no more than 255 characters):");
        char input[MAX];
        scanf("%999s",input);
        if (strcmp(input,"quit") == 0){
            flag = false;
        }
        else {
            TREE parseTree = buildRecursiveParser(input);
            if (parseTree == NULL) continue;
            printf("Parse Tree for input %s:\n \n", input);
            print(parseTree,-1);
            printf("\n \n");

            printf("Result for \"%s\":\n \n", input);
            TREE expressionTree = convertToExpressionTree(parseTree);
            printExpressionTree(expressionTree);
            printf("\n");

            freeTREE(parseTree);
            freeTREE(expressionTree);
        }
        printf("\n");
    }
} 

TREE convertToExpressionTree(TREE root) {
    return nodeE(root);
}

TREE nodeE(TREE node) {
    // printf("Visit E\n");
    TREE c = node->leftmostChild;
    TREE et = c->rightSibling;

    if (strcmp(et->leftmostChild->label, "eps") == 0)
        return nodeC(c);

    TREE uni = et->leftmostChild;
    TREE e = uni->rightSibling;

    TREE left = nodeC(c);
    TREE right = nodeE(e);
    TREE expression = make2Node("UNION", left, right, 0);

    return expression; 
}

TREE nodeC(TREE node) {
    // printf("Visit C\n");
    TREE s = node->leftmostChild;
    TREE ct = s->rightSibling;

    if (strcmp(ct->leftmostChild->label, "eps") == 0)
        return nodeS(s);

    TREE dot = ct->leftmostChild;
    TREE c = dot->rightSibling;

    TREE left = nodeS(s);
    TREE right = nodeC(c);
    TREE expression = make2Node("CONCAT", left, right, 0);

    return expression;
}

TREE nodeS(TREE node) {
    // printf("Visit S\n");
    TREE a = node->leftmostChild;
    TREE st = a->rightSibling;

    if (strcmp(st->leftmostChild->label, "eps") == 0)
        return nodeA(a);

    TREE expression = nodeST(st);
    for (TREE temp = expression; ; temp = temp->leftmostChild)
        if (temp->leftmostChild == NULL) {
            temp->leftmostChild = nodeA(a);
            break;
        }

    return expression;
}

TREE nodeST(TREE node) {
    // printf("Visit ST\n");
    TREE star = node->leftmostChild;
    TREE st = star->rightSibling;

    if (strcmp(st->leftmostChild->label, "eps") == 0)
        return makeNode("CLOSURE", 0);

    TREE expression = make1Node("CLOSURE", nodeST(st), 0); 

    return expression;
}

TREE nodeA(TREE node) {
    // printf("Visit A\n");
    if (strcmp(node->leftmostChild->label, "(") == 0)
        return nodeE(node->leftmostChild->rightSibling);
    else {
        return nodeX(node->leftmostChild);
    }
}

TREE nodeX(TREE node) {
    // printf("Visit X\n");
    
    TREE letter = node->leftmostChild;
    //char *atomic = "ATOMIC ";
    char* trueLabel = concat("ATOMIC ",letter->label);
    TREE expression = makeNode(trueLabel, 0);
    //expression->freeable = true;
    return expression;
}

void printExpressionTree(TREE root) {
    printf("(%s", root->label);

    for (TREE node = root->leftmostChild; node != NULL; node = node->rightSibling) {
        printf(" ");
        printExpressionTree(node);
    }

    printf(")");
}

char* concat(char* a, char* b){
    char* result;
    int size1 = 0;
    int size2 = 0;
    while (a[size1] != '\0'){
        size1++;
    }
    while (b[size2] != '\0'){
        size2++;
    }
    int totalsize = size1+size2+1;
    result = (char*) malloc(totalsize*sizeof(char));
    int index = 0;
    while (index < totalsize-1){
        if (index < size1){
            result[index] = a[index];
        }
        else {
            result[index] = b[index-size1];
        }
        index++;
    }
    result[totalsize-1] = '\0';
    return result;
}

