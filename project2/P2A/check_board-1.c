///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      none
// Semester:         CS 354 Spring 2023
// Instructor:       Prof Deb Deppeler
//
// Author:           vardaan kapoor
// Email:            vkapoor5@wisc.edu
// CS Login:         vardaan
// GG#:              8
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friencs, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          none
//
// Online sources:   none
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
/* this method gives us the board size
 *
 * Pre-conditions:get file pointer and a pointer to the variable which should store the size
 * param1 file pointer
 * param2 size variable's pointer
 * no return value
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line1 = NULL;//making the input line null before it gets the first line
	size_t len = 0;//making the length pointer to be 0

	if ( getline(&line1, &len, fptr) == -1 ) {
		//getline method-first argument is the pointer to the first character of the line,second is the pointer to the variable
		//which stores the length of the incoming line
		//third argument is the  standard input stream
		printf("Error reading the input file.\n");
		free(fptr);free(size);free(line1);//free the memory allocated to the 2 variables-exit with code 1
		exit(1);
	}
//else do this thing-
//	printf("now reading the file");
	char *size_chars = NULL;
	size_chars = strtok(line1, DELIM);//tokenizing the string based on the delimiter given
	*size = atoi(size_chars);//increasing the size pointer back to the size variable whose address was passed during function call

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
//printf("exiting the get_board_size() method");
}



/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {
//at this stage,board gets the pointer to the first row of the 2d heap allocated array and the fulll array has been dynamically allocated
//board is the pointer to the pointer of int-2d array on heap allocated
//size is the integer argument passed
//run the for loop but don't use indexing via i and j
//the first row of 2d array contains the address of the array embedded in it-so we only dereference it once
	//declare a int * array to store the values which we have found till yet in the array
if(size<1 || size>9)
{
printf("exiting invalid size");
exit(1);
}
//printf("size is %i",size);
for(int i=0;i<size;i++)
{
	//get first row-board pointer points to the first row only
	//declare a pointer to an array of integers
	//method 1 of dexlaring
	//int *store[size];//only declaring
	//method 2 of declaring using malloc
	int *store=malloc(size*sizeof(int));//allocate size # elements containing int
if(store==NULL)
{
printf("memory of store variable pointer is not allocated");
exit(1);
}
	//method for allocating integer pointers' space- malloc(size*sizeof(int *))
	//sizeof(int) stores 4 bytes in memory-if we want space for 28 integers,we need to do 28*sizeof(int)
//TODO:
//FOR VARDAAN KAPOOR ONLY-INITIALIZING ELEMENT TO 0 BY DEFAULT
int element=0;	int k=0;
	for(int j=0;j<size;j++)
	{
		//int element=*(oneDarray+j);
		if((*(board+i)+j)!=NULL)
{
element=*(*(board+i)+j);
//printf("location address at m[%d][%d] is %p\n",i,j,*(board+i)+j);
//printf("contents are %d\n",element);
}
		//dereference the elements of the row
		for(int l=0;l<size;l++)
		{
			if((store+l)!=NULL && *(store+l)==element && element!=0)//getting the element at index l of the store array and then checking it wrt element
			//we have gotten from the above lines-we won't check 0 as 0 is not taken as the value which is worng to input
			{
				free(store);store=NULL;return 0;//we have found duplicate value in one row
			}
		}
		*(store+(k++))=element;//if duplicate not found-then add to the element list
		//TODO:check the validity of k++ in the above expression
		//this is wrong-change  it as we can't use indexing
		
	}
/*
for(int ss=0;ss<size;ss++)
{
if(store+ss!=NULL)
{
printf("%d element is %d",i,*(store+ss));
}}
*/

	//now empty/free the store list for next row checking
	for(int l=0;l<size;l++)
		{
			*(store+l)=0;//changing the values of every element to 0 by default
		}
free(store);
store=NULL;
}

//run the same loop for checking the columns' values-same j and different i values
for(int i=0;i<size;i++)
{
	int k=0;//using k again to keep track of internal indexing of the store array
	//get the column i all rows' values
	int *store1=malloc(size*sizeof(int));//again collect all the values to check
if(store1==NULL)
{
printf("store1 variable pointer wasn't allocated properly");
exit(1);
}
	int element2=0;
for(int j=0;j<size;j++)
	{
if((*(board+j)+i)!=NULL)
{
		element2=*(*(board+j)+i);//getting consecutive rows' values of one column
}
for(int  l1=0;l1<size;l1++)
		{
			if(store1+l1!=NULL && *(store1+l1)==element2 && element2!=0)
			{
				free(store1);store1=NULL;return 0;//we have found duplicate value in one row
			}
		}

		*(store1+(k++))=element2;//if duplicate not found-then add to the element list
/*
printf("element is %d\n",element2);
for(int ll=0;ll<size;ll++)
{
if(store1+ll!=NULL){
printf("%d",*(store1+ll));
}}
printf("\n");

*/
}
		//TODO:check the k++ expression
		for(int l1=0;l1<size;l1++)
		
		{
			*(store1+l1)=0;//changing the values of every element to 0 by default
		}
	
free(store1);
store1=NULL;
}

	return 1;   
}    



/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              
//getting the length of *argv array(string array of characters)
//int len1=strlen(*(argv+1));//get the length of the string array-get #characters in the array)
	// TODO: Check if number of command-line arguments is correct.
if(argc!=2)
{
printf("exit");
	exit(1);
}
	// Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");//argv contains in this case 2 values-1st one is the name of the program itself and the 
	//second one is the argument given to it
	if (fp == NULL) {
		printf("Can't open file for reading.\n");
		exit(1);//exiting with error code 1
	}

	// Declare local variables.
	int size;
	int **m;
	// TODO: Call get_board_size to read first line of file as the board size.
//pass pointers to both the arguments
get_board_size(fp,&size);//&variable gives us the address of the variable
//fp is already a pointer-so we directly give or pass its value
	// TODO: Dynamically allocate a 2D array for given board size.
//we just have to allocate memory-use malloc function
m=malloc(sizeof(int*) *size);//m is a pointer to an array of integer pointers
if(m==NULL)
{
printf("memory not allocated");
exit(1);
}
	// Read the rest of the file line by line.
	// Tokenize each line wrt the delimiter character 
	// and store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading line %i of the file.\n", i+2);
			free(line);free(token);exit(1);
		}
//adding one more line to dynamically allocate memory for the 1d array pointers for type int
*(m+i)=malloc(sizeof(int)*size);//dereference the row and then allocate memory for it
		token = strtok(line, DELIM);
		
		for (int j = 0; j < size; j++){
		// TODO: Complete the line of code below
			// to initialize your 2D array.
			/* ADD ARRAY ACCESS CODE HERE */
   *(*(m+i)+j)=atoi(token);//go to column j of row i of the 2d array
//printf("m[%d][%d] is",i,j);printf("%i",*(*(m+i)+j));
//printf("\n");
token=strtok(NULL,DELIM);
}}
	// TODO: Call the function valid_board and print the appropriate

	//       output depending on the function's return value.

if(valid_board(m,size)==0)
{
printf("invalid\n");
}
else{
printf("valid\n");
}
//printf(valid_board(m,size)==0?"invalid":"valid");//m contains a poitner to the first row-so directly pass the value of m
	// TODO: Free all dynamically allocated memory.
//list of all dynamically typed allocated memory-1d ray,2d array m,argv,fp,line,token
//always make them null-no dangling pointers and no memory leaks
//always go from the lowest to the highest level when freeing the memory
for(int i=size-1;i>=0;i--)
{
	
	//now free the whole rows as well-make them null as well
free(*(m+i));//can't free the first reference first-then we won't be able to access and free the others after it-seg fault
	//so go in reverse order
//	*(m+i)=NULL;
}
free(m);m=NULL;
/*for(int j=1;j>=0;j--)
{
for(int i=len-1;i>=0;i--)
{
free(*(argv+j)+i);
/
*(*(argv+j)+i)=NULL;
}
free(argv+j);
*(argv+j)=NULL;
}
free(argv);argv=NULL;
//TODO:aks how to free the fp argument
//my guess
//free(fp);
//fp=NULL;
//free(fp);fp=NULL;
for(int i=strlen(line)-1;i>=0;i--)
{
	free(line+i);
	//line+i=NULL;
}
free(line);
line=NULL;
for(int i=strlen(token)-1;i>=0;i--)
{
	free(token+i);
	//token+i=NULL;
}
free(token);
token=NULL;
*/

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file.\n");
		exit(1);
	} 

	return 0;       
       

}
