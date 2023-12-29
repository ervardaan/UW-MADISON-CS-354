////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      NONE
// Semester:         CS 354 Lecture 00? Spring 2023
// Instructor:       deppeler
// 
// Author:           VARDAAN KAPOOR
// Email:            VKAPOOR5@WISC.EDU
// CS Login:         VARDAAN
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NONE
// Online sources:   NONE
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
// Structure that represents a magic square
typedef struct {
	int size;           // dimension of the square
	int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {

	/*
	   char * c;
	   if((c=gets())==0)
	   {
	   printf("invalid hoice");
	   exit(1); 
	   }
	//ANOTHER METHOD USING SCANF
	char * ch;
	if(scanf("%c",ch)!=1)
	{
	printf("exiting because getting the size failed");

	exit(1);
	}
	int size=atoi(ch);
	printf("the size is %i",size);
	if(size%2!=1 || size<3)
	{
	printf("invalid choice");
	exit(1);
	}
	 */
	//    char * ch;
	//     printf("Enter a character : ");
	//     //read input from user to "ch"
	//     if((scanf("%s", &ch))!=1)
	//     {
	//         exit(1);
	//     }
	//     //print to console
	//     printf("You entered %s\n", *ch);
	//     //int size=atoi()
	//     return 0;
	// printf("give us the size of the magic square");
	int size;
	printf("Enter magic square's size(odd integer>=3\n");
	scanf("%i",&size);
	if(size%2==0)
	{
		printf("Magic Square size must be odd\n");
		exit(1);
	}
if(size<3){
printf("Magic Square size must be >=3\n");
exit(1);}
//	printf("you entered %i",size);
	//return 0;
	return size;

} 

/* TODO:
 * Makes a magic square of size n using the 
 * Siamese magic square algorithm or alternate from assignment 
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {
	// int **magicsquare=(malloc(sizeof(MagicSquare));
	//for(int i=0;i<n;i++)
	//{
	//  *(magicsquare+i)=malloc(sizeof(int)*n);

	//}
	MagicSquare *square1=(MagicSquare *)(malloc(sizeof(MagicSquare)));
	//   struct MagicSquare getSquare={n,magicsquare};
	//     struct MagicSquare square1=&getSquare;
	// struct MagicSquare *square1=&getSquare;
	//now access the square member
	//getting the array of pointers to integers 
	square1->size=n;
	square1->magic_square=(int**)(malloc(sizeof(int*)*n));
	for(int i=0;i<n;i++)
	{
		*((square1->magic_square)+i)=(int*)calloc(n,sizeof(int));//giving another nested array of integers to the 1d array we are traversing right now
																 //by using calloc we autoomatically made the default values as 0
																 // for(int j=0;j<n;j++)
																 // {
																 //    *(*(square+i)+j)=0;//explicitly making every columns' value as 0

																 // }
	}
	//now we have an empty 2d array and now we acn start filling it up
	//make a do while loop until we get all the n^2 elements into the square 
/*
	for(int k=0;k<n;k++){
		for(int l=0;l<n;l++){
			printf("%d",*(*(square1->magic_square+k)+l));
		}
		printf("\n");
	}
*/	
	int r=0;int c=(n)/2;int i=1;//we start at index 0,middle of the columns
								//we use 0 indexing and so we don't do n+1-because we already want one index less than what we use in maths
	do{
		int current=*(*((square1->magic_square)+r)+c);
		if(current==0)
		{
			*(*((square1->magic_square)+r)+c)=i++;
		}
		int next_r=r-1;int next_c=c+1;
		//    if(next_r>=0 && next_r<n && next_c>=0 && c<n )
		//    {

		//    }
		//wrapping up the indexes
		next_r=next_r==-1?n-1:next_r;
		next_c=next_c==n?0:next_c;
		if( *(*((square1->magic_square)+next_r)+next_c)!=0)
		{
		//	next_r=next_r+1;//moving  one row down if the target is filled
//extra
r=r+1;
		}
//changing-
else{
		r=next_r;c=next_c;}
		//putting the element to some other location

	}
	while(i!=(n*n)+1);

//	printf("printttt\n");
/*
	for(int k=0;k<n;k++){
		for(int l=0;l<n;l++){
			printf("%i",*(*(square1->magic_square+k)+l));printf(" ");
		}
		printf("\n");
	}
*/
	return square1;   
	//   int N=n*n;
	//   int r=0;int c=1;
	//   int rr;int cc;
	//   *(*(MagicSquare+r)+c)=1;
	//   for(int i=2;i<N;i++)
	//   {
	//     rr=(r==n-1)?0:r-1;
	//     cc=(c==n-1)?0:c+1;
	//     if(*(*(MagicSquare+rr)+cc)==0)
	//     {
	//         r=rr;c=cc;
	//     }
	//     else{
	//         c=c==0?
	//     }
	//   }
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	//opening a new file using fopen method
	//TODo : we have to write on the file or we can even use output redirection
	FILE *fp=fopen(filename,"w");//open in write mode
	if(fp==NULL)
	{
		printf("the file could not be opened\n");
		exit(1);
	}
fprintf(fp,"%i\n",magic_square->size);
	for(int i=0;i<magic_square->size;i++)
	{
		for(int j=0;j<magic_square->size;j++)
		{

			fprintf(fp,"%i",*(*(magic_square->magic_square+i)+j));
		if(j!=magic_square->size-1){
fprintf(fp,",");}							
		}
		fprintf(fp,"\n");
	}
	printf("successfully loaded the file with the magic square\n");
fclose(fp);

}


/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
	// TODO: Check input arguments to get output filename
//	printf("%i",argc);
//	printf("%s\n",*(argv+1));
	if(argc!=2){
		
		printf("Usage: ./myMagicSquare.c <output_filename>\n");
		exit(1);
	}
	//argc contains only reference to one of the command line arguments
		
	// TODO: Get magic square's size from user
	int size=getSize();
//	printf("%i",size);
	MagicSquare *ms=generateMagicSquare(size);
	//getting the dereferenced value of argv
	// TODO: Generate the magic square by correctly interpreting 
	//       the algorithm(s) in the write-up or by writing or your own.  
	//       You must confirm that your program produces a 
	//       Magic Sqare as described in the linked Wikipedia page.

	// TODO: Output the magic square
	//opening and getting the file to output the data
	fileOutputMagicSquare(ms,*(argv+1));//ms already ocntains an address to the struct it points to
	
for(int i=0;i<size;i++)
  {
	int **p = ms->magic_square; 
  free(*(p+i));
  *(ms->magic_square+i)=NULL;
  }
free(ms->magic_square);
ms->magic_square=NULL;
free(ms);(ms)=NULL;

//getSize();
//	return 0;

return 0;
}
// S23

