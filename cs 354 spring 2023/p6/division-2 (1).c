////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        division.c
// Other Files:      sendsig.c
// Semester:         CS 354 Lecture 02? Spring 2023
// Instructor:       deppeler
// 
// Author:           vardaan kapoor
// Email:            vkapoor5@wisc.edu
// CS Login:         vardaan
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NONE
// Online sources:   NONE
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int c=0;
/*
   this method is used to define the customized working when we get a floating point exception
 */
void handler_SIGFPE()
{
	printf("a division by 0 was attempted.\nTotal number of operations completed successfully:%d\nThe program will be terminated.",c);
	exit(0);
}
/*
   thids method defines customized working when we get an interrup signal
 */
void handler_SIGINT()

{
	printf("number of successfully completed divisions are %d",c);
	exit(0);
}

/*
   this method is used to call all the other functions and run the whole proigram
 */
int main()
{
	struct sigaction sa4;
	memset(&sa4,0,sizeof(sa4));
	sa4.sa_handler=handler_SIGFPE;
	if(sigaction(SIGFPE,&sa4,NULL)!=0)
	{
		printf("we are not able to handle FLOATING POINT EXCEPTION");
		exit(1);
	}
	struct sigaction sa5;
	memset(&sa5,0,sizeof(sa5));
	sa5.sa_handler=handler_SIGINT;
	if(sigaction(SIGINT,&sa5,NULL)!=0)
	{
		printf("we are not able to handle the interrupt signal");
		exit(0);
	}
	while(1)
	{
		char str[100];
		int num1;int num2;
		printf("Enter first integer");
		if(fgets(str,100,stdin)!=NULL){//when we don't read from a file pointer stream,we replace file stream with the standard input stream called stdin
		
		num1=atoi(str);
}

else{
printf("wrong input type");exit(1);}
printf("\n");
		printf("Enter second integer");

		if(fgets(str,100,stdin)!=NULL){
		num2=atoi(str);
}
else{
printf("wrong input type");exit(1);}
		printf("\n");
		int div=num1/num2;
		//if the division line doesn't give an exception, then c will be incremented otherwise the control goes directly to the sigaction block


		printf("%d/%d is %d with a remainder of %d\n",num1,num2,div,num1%num2);

		c++;
	}

}

