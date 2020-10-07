/* Collaborators: Anisha Bhattacharya,
                    Godbless Chille,
                    Nilsu Duran
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RecursiveParser.h"
#include "TableParser.h"


int numFree = 0;
int numNodes = 0;
int main()
{

    //the expression's storage
    
    char input[MAX];
    printf("-------------Recursive Decent Parser-------------");
    while (true)
    {
        printf("Enter an Arithmetic expression or type quit to exit \n");
        scanf("%s", input);
        if (strcmp(input, "quit") == 0)
        {
            break;
        }
        lookahead = input;

        parseTree = sync_catE();

        printf("Parsing on: %s \n", input);

        if(parseTree == NULL) 
        {
            printf("Invalid input\n");
        } 
        else 
        {
            printf("----------------------|Tree|----------------------\n");
            print(parseTree, -1);
            freeTREE(parseTree);
            printf("\n");
            //printf("Nodes: %d \nFreedNodes: %d\n",numNodes, numFree);
        }
    }

//table-driven parser

}