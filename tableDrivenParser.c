#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tableDrivenParser.h"

#define MAX 1000
#define FAILED NULL

char printing[MAX];
int indexPrinting = 0;
char *start, *nextTerminal;
TREE stack[MAX];
int size = 0;
int** parseTable;


void tryTableDrivenParser()
{
    start = (char*) malloc(sizeof(char)*256);
    createParseTable();
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
        else 
        {
            printf("Result for \"%s\":\n \n", input);
            nextTerminal = start;
            strcpy(nextTerminal,input);
            if (!parsing())
            {
                printError();
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
    freeTable(parseTable);
    //freeStack();
    //free(printing);
}

//return if parsing is success
bool parsing(){
    TREE root = makeNode("E",0);
    push(root);
    while (size != 0){
        //pop curr Node
        TREE curr = pop();
        if (curr == FAILED) return false;
        //check valid input and get column
        int col = switchChar(*nextTerminal);
        if (col == -1) {
            if (curr != FAILED) freeTREE(curr);
            return false;
        }
        //get row by label
        int row = getRow(curr->label);
        int production = getProduction(row,col);
        if (row > 0){ //Capital Letter => label
            //look at position (row,col) => production number
            //follow the production
            chooseProduction(curr,production);
        }
        else { //matching (terminal node)
            if (strcmp(curr->label, "eps") != 0 && *nextTerminal != curr->label[0]){
                if (curr != FAILED) freeTREE(curr);
                return false;
            } 
            else if (*nextTerminal == curr->label[0]) nextTerminal++;
        }
        if (curr != FAILED) {
            getLabel(curr->label,curr->indent);
            //printf("I am working, label is: %s \t and %d:\n", curr->label, curr->indent);
            freeTREE(curr);
        }
        else {
            return false;
        }
    }
    if (*nextTerminal != '\0') return false;
    return true;
}

/* 
    parseTable = {
        {0,0,0,0,0,0,0},
        {1,0,0,0,0,1,0},
        {3,0,0,0,0,3,0},
        {2,2,2,2,2,2,2},
        {4,4,4,4,4,4,4},
        {5,0,0,0,0,5,0},
        {7,0,0,0,0,7,0},
        {6,6,6,6,6,6,6},
        {8,0,0,0,0,0,0}
    };
*/
void createParseTable(){
    
    int row = 9;
    int col = 7;
    parseTable = malloc(sizeof(int*)*row);
    for (int i = 0; i < row; i++){
        parseTable[i] = malloc(sizeof(int)*col);
        for (int j = 0; j < col; j++){
            parseTable[i][j] = 0;
        }
    }
    for (int i = 0; i < col; i++){
        parseTable[3][i] = 2;
        parseTable[4][i] = 4;
        parseTable[7][i] = 6;
    }
    parseTable[1][0] = 1;
    parseTable[1][5] = 1;
    parseTable[2][0] = 3;
    parseTable[2][5] = 3;
    parseTable[5][0] = 5;
    parseTable[5][5] = 5;
    parseTable[6][0] = 7;
    parseTable[6][5] = 7;
    parseTable[8][0] = 8;
    
}

//choose production to execute
void chooseProduction(TREE curr,int production){
    switch (production)
    {
    case 1:
        production1(curr);
        break;
    case 2: 
        production2(curr);
        break;
    case 3:
        production3(curr);
        break;
    case 4:
        production4(curr);
        break;
    case 5:
        production5(curr);
        break;
    case 6:
        production6(curr);
        break;
    case 7:
        production7(curr);
        break;
    case 8:
        production8(curr);
        break;
    default:
        productionNegative(curr);
        break;
    }
}

//get production from the table
int getProduction(int row, int col){
    return parseTable[row][col];
}

//get Row based on label of Node
int getRow(char* label){
    char label1 = label[0];
    switch (label1){
        case 'E':
            if (label[1] == 'T'){
                return 3;
            }
            else if (label[1] == '\0'){
                return 1;
            }
            else return 0;
        case 'C':
            if (label[1] == 'T'){
                return 4;
            }
            else if (label[1] == '\0'){
                return 2;
            }
            else return 0; 
        case 'S':
            if (label[1] == 'T'){
                return 7;
            }
            else if (label[1] == '\0'){
                return 5;
            }
            else return 0; 
        case 'A':
            if (label[1] == '\0') return 6;
            else return 0;
        case 'X': 
            if (label[1] == '\0') return 8;
            else return 0;
        default:
            return 0;
    }
}

//choose Col based on input
int switchChar(char c){
    if ((int) c > 96 && (int) c < 123) return 0;
    else if (c == '.') return 1;
    else if (c == '*') return 2;
    else if (c == '|') return 3;
    else if (c == '\0') return 4;
    else if (c == '(') return 5;
    else if (c == ')') return 6;
    else return -1;
}


//pop operation of stack
TREE pop() 
{
    TREE c;
    if (size == 0)
    {
        printf("size is empty!!");
    }
    size--;
    c = stack[size];
    return c;
}
//push operation of stack
void push(TREE c){
    if (size < MAX){
        stack[size] = c;
        size++;
    }
}

//production for failed node
void productionNegative(TREE curr) {
    push(FAILED);
    return;
}

// production 1: <E> -> <C><ET>
void production1(TREE curr){
    int num = curr->indent+1;
    TREE concat = makeNode("C",num);
    TREE et = makeNode("ET",num);
    push(et);
    push(concat);
    return;
}

// production 3: <C> -> <S><CT>
void production3(TREE curr){
    int num = curr->indent+1;
    TREE star = makeNode("S",num);
    TREE ct = makeNode("CT",num);
    push(ct);
    push(star);
}

// production 2: <ET> -> |<E>  |  eps
void production2(TREE curr){
    int num = curr->indent+1;
    if (*nextTerminal == '|'){
        TREE e = makeNode("E",num);
        TREE straight = makeNode("|",num);
        push(e);
        push(straight);
        return;
    }
    else {
        TREE eps = makeNode("eps",num);
        push(eps);
        return;
    }
}

// production 5: <S> -> <A><ST>
void production5(TREE curr){
    int num = curr->indent+1;
    TREE atomic, st;
    atomic = makeNode("A",num);
    st = makeNode("ST",num);
    push(st);
    push(atomic);
    return;
}

// production 4: <CT> -> .<C>  |  eps
void production4(TREE curr){
    int num = curr->indent+1;
    if (*nextTerminal == '.'){
        TREE c;
        TREE dot = makeNode(".",num);
        c = makeNode("C",num);
        push(c);
        push(dot);
        return;
    }
    else{
        TREE eps = makeNode("eps",num);
        push(eps);
        return;
    }
}

// production 7: <A> -> (<E>)  |  <X>
void production7(TREE curr){
    int num = curr->indent+1;
    if (*nextTerminal == '('){
        TREE e;
        TREE open, close;
        e = makeNode("E",num);
        open = makeNode("(",num);
        close = makeNode(")",num);
        push(close);
        push(e);
        push(open);
        return;
    }
    else {
        TREE e;
        e = makeNode("X",num);
        push(e);
        return;
    }
}

// production 6: <ST> -> *<ST> |  eps
void production6(TREE curr){
    int num = curr->indent+1;
    if (*nextTerminal == '*'){
        TREE st;
        TREE star;
        st = makeNode("ST",num);
        star = makeNode("*",num);
        push(st);
        push(star);
        return;
    }
    else {
        TREE eps = makeNode("eps",num);
        push(eps);
        return;
    }
}

// production 8: <X> -> a|b|c|...|z
void production8(TREE curr){
    char c = *nextTerminal;
    int num = curr->indent+1;
    if ((int) c > 96 && (int) c < 123){
        //nextTerminal++;
        char *input = malloc(2*sizeof(char));
        input[0] = c;
        input[1] = '\0';
        TREE in = makeNode(input,num);
        //in->freeable = true;
        push(in);
        return;
    }
    else {
        TREE c = FAILED;
        push(c);
        return;
    }
}

//get printing line for node
void getLabel(char *x, int indent) {
    int index = 0;
    while (index < indent){
        printing[indexPrinting] = ' ';
        indexPrinting++;
        printing[indexPrinting] = ' ';
        indexPrinting++;
        index++;
        //printf("  ");
    }
    int i = 0;
    while (x[i] != '\0'){
        printing[indexPrinting] = x[i];
        indexPrinting++;
        i++;
    }
    //printf("%s\n",x);
    printing[indexPrinting] = '\n';
    indexPrinting++;
}

//print parse TREE 
void printParseTree(){
    printing[indexPrinting] = '\0';
    int i = 0;
    while (printing[i] != '\0'){
        printf("%c",printing[i]);
        i++;
    }
    indexPrinting = 0;
}

void freeTable(int** parseTable)
{
    for (int i = 0; i < 9; i++)
    {
        free(parseTable[i]);
    }
    free(parseTable);
}

void printError()
{
    printf("Invalid input!");
}