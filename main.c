/* Collaborators: Anisha Bhattacharya,
                    Godbless Chille,
                    Nilsu Duran
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RecursiveParser.h"
#include "tableDrivenParser.h"
#include "convertToExpression.h"

//lookahead? where is it intialized here
int numFree = 0;
int numNodes = 0;

char* start;

int main()
{
    runRecursiveParser();
    tryTableDrivenParser();
    runConvert();
	return 0;

}