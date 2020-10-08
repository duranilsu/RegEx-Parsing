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

//lookahead? where is it intialized here
int numFree = 0;
int numNodes = 0;
int main()
{

    //the expression's storage
    
    char input[MAX];
    // printf("-------------Recursive Decent Parser-------------");
    // while (true)
    // {
    //     printf("Enter an Arithmetic expression or type quit to exit \n");
    //     scanf("%s", input);
    //     if (strcmp(input, "quit") == 0)
    //     {
    //         break;
    //     }
    //     lookahead = input;

    //     parseTree = sync_catE();

    //     printf("Parsing on: %s \n", input);

    //     if(parseTree == NULL) 
    //     {
    //         printf("Invalid input\n");
    //     } 
    //     else 
    //     {
    //         printf("----------------------|Tree|----------------------\n");
    //         print(parseTree, -1);
    //         freeTREE(parseTree);
    //         printf("\n");
    //         printf("Nodes: %d \nFreedNodes: %d\n",numNodes, numFree);
    //     }
    // }

//table-driven parser

// printf("-------------Table-Driven Parser-------------\n");
//     while (true)
//     {
//         printf("Enter an Arithmetic expression or type quit to exit \n");
//         scanf("%s", input);
//         if (strcmp(input, "quit") == 0)
//         {
//             break;
//         }
//         lookahead = input;
//         //printf("%c here is the pointer\n", *lookahead);
//         printf("Trying to parse noww......");
//         TREE parse = ParsFunction();
//         printf("%c here is the pointer\n", *lookahead);
//         printf("Parsing on: %s \n", input);
//         //ParsFunction()
//         if(parse == FAILED) 
//         {
//             // if (parseTree != FAILED)
//             // {
//             //     freeTREE(parseTree);
//             // }
//             printf("Invalid input\n");
//         } 
//         else 
//         {
//             printf("----------------------|Tree|----------------------\n");
//             print(parse, -1);
//             //freeTREE(parse);
//             printf("\n");
//             //printf("Nodes: %d \nFreedNodes: %d\n",numNodes, numFree);
//         }
//         while (getSize() != 0){
//             TREE curr = pop();
//             freeTREE(curr);
//         }
//     }


//this one works! BUt have to revert back to the original stuff that GB was doing 
    // printf("-------------Table-Driven Parser-------------\n");
    // while (true)
    // {
    //     printf("Enter an Arithmetic expression or type quit to exit \n");
    //     scanf("%s", input);
    //     if (strcmp(input, "quit") == 0)
    //     {
    //         break;
    //     }
    //     nextTerminal = input;
    //     //printf("%c here is the pointer\n", *lookahead);
    //     printf("Trying to parse noww......");
    //     TREE root = makeNode0('E'); //we make the node for the first expression
    //     push(root);
    //     printf("%c here is the pointer\n", *nextTerminal);
    //     printf("Parsing on: %s \n", input);
    //     bool possible=ParsFunction(root);
    //     printf("JUST CALLED IT\n");
    //     if(possible) 
    //     {
            
    //         if (parseTree != FAILED)
    //         {
    //             freeTREE(parseTree);
    //         }
    //         //printf("Invalid input\n");
    //     } 
    //     else 
    //     {
    //         printf("----------------------|Tree|----------------------\n");
    //         print(root, -1);
    //         //freeTREE(parse);
    //         printf("\n");
    //         //printf("Nodes: %d \nFreedNodes: %d\n",numNodes, numFree);
    //     }
    //     while (getSize() != 0){
    //         TREE curr = pop();
    //         freeTREE(curr);
    //     }
    // }
    

    //the final one I hope
    printf("-------------Table-Driven Parser-------------\n");
    while (true)
    {
        printf("Enter an Arithmetic expression or type quit to exit \n");
        scanf("%s", input);
        if (strcmp(input, "quit") == 0)
        {
            break;
        }
        nextTerminal = input;
        //printf("%c here is the pointer\n", *lookahead);
        printf("Trying to parse noww......");
        // TREE parse = ParsFunction();
        printf("%c here is the pointer\n", *nextTerminal);
        printf("%s \n",input);
        printf("Parsing on: %s \n", input);
        printf("Okay calling method parsefunc\n");
        // bool val=ParsFunction();
        // printf("%c",val);
        // printf("called parse function once");
        if(!ParsFunction()) 
        {
            // if (parseTree != FAILED)
            // {
            //     freeTREE(parseTree);
            // }
            printf("Invalid input- parse is null\n");
        } 
        else 
        {
            printf("----------------------|Tree|----------------------\n");
            //freeTREE(parse);
            printf("\n");
            //printf("Nodes: %d \nFreedNodes: %d\n",numNodes, numFree);
        }
        // while (getSize() != 0)
        // {
        //     TREE curr = pop();
        //     freeTREE(curr);
        // }
    }

}