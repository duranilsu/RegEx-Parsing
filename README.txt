CSC173 Project 2

Collaborators: Godbless Chille, Nilsu Duran, Anisha Bhattacharya
netID: gchille, vduran, abhatta9

————————————————————————————————————

Files:
	CSC173-Project-2-Final
			> main.c
			> RecursiveParser.c
			> RecursiveParser.h
			> tableDrivenParser.c
	 		> tableDrivenParser.h
			> convertToExpression.c
			> convertToExpression.h
			> Makefile
			> README.txt


Regular Expression Terminals: 
. = concatenation
* = closure
| = union

Grammar Structure
1. <E> -> <C><ET>
2. <ET> -> |<E>|eps
3. <C> -> <S><CT>
4. <CT> -> .<C>|eps
5. <S> -> <A><ST>
6. <ST> -> *<ST>|eps
7. <A> -> (<E>)|eps
8. <X> -> a|b|...|z

"eps" means empty character

————————————————————————————————————

HOW TO RUN:

After you link cd to directory, type:
$ make
$ ./rexp

After running the file once, type:
$ make clean

and type in the same commands as before.

____________________________________

What our files do:

We run the program inside main.c which includes the header files for RecursiveParser, tableDrivenParser, convertToExpression.
For the first part of the project, we used the RecursiveParser files to build a recursive parser 
where we defined the functions for creating the tree and the syntactic categories.
For the second part, we used the tableDrivenParser files to build a table driven parser which defines functions for each production 
inside the table and also implemented other functionality for the table.
For the third part, the convertToExpression files convert the parse tree to an expression tree and prints it as prefix notation.

———————————————————————————————————

Output:

When you run the project, you will be prompted to enter a regular expression. 
A parse tree will be printed using the recursive parser. Type quit to pass to the second part. 
Enter another regex to print a parse tree this time using a parse table. 
The output should be the same as the first part. Type quit for the third part where you enter another expression. 
This time the tree will be printed along with an expression tree printed in prefix notation.