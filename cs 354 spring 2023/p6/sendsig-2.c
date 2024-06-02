////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        sendsig.c
// Other Files:      division.c
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
# include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
/*
   this method is used to run the main program
 */
int main(int argc,char *argv[])
{
	//printf("%s",argv[2]);
	//printf("%d",atoi(argv[2]));

	if(argc!=3 || (strcmp(argv[1],"-i")!=0 && strcmp(argv[1],"-u")!=0))
	{
		printf("Usage: sendsig <signal type> <pid>");
		exit(1);
	}
	int check=0;
	if(strcmp(argv[1],"-i")==0)
	{
		check=kill(atoi(argv[2]),2);//2 IS FOR NTERRUPT SIGNAL
	}
	else{
		check= kill(atoi(argv[2]),10);//10 is for usr1
	}
	if(!check)
	{
		//we got 0 as the return value-so we are good
	}
	else{
		printf("we are not able to send a signall to the desired process");
	}

}

