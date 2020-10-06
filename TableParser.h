#define ENDM $

//make_table returns true or false if the expression can
//be evaluated by a table
extern int make_table(char input);
//checks if the character we are currently looking at is a terminal
extern int is_terminal(char c);
//checks if it is an operator
extern int is_operator(char c);

/*
essentially, these ones help us index to the table in terms of rows and columnns
rows being the syntactic categories and columns being the character (terminals)
*/
extern int equi_prod(char c);
extern int equi_char(char c);