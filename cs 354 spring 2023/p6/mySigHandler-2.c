////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      sendsig.c,division.c
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
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <time.h>
int number_sec=4;
int c=0;
/* 
 * this method is used to define our customized method/way to handle the ALARM signal if we get any
 */
void handler_SIGALRM()
{
	//printf("hi");
	int pid=getpid();
	//method 1:using struct and getting all the elements seperately
	time_t result1=time(NULL);//getting the time
							  //note that the time result 1 of the form time_t is called the "calendar time"
							  //note that the functions ctime() and localtime() both take a pointer to  the variable storing time_t as their argument
if(result1==-1){printf("time() method didn't work properly");exit(1);}
//	struct tm store_local1=*localtime(&result1);
//	int hour=store_local1.tm_hour;
//	int sec=store_local1.tm_sec;
//	int min=store_local1.tm_min;
//	int mday=store_local1.tm_mday;
//	int mon=store_local1.tm_mon;
//	int wday=store_local1.tm_wday;
//	int year=store_local1.tm_year;


//	printf("PID: %d CURRENT TIME: %d %d %d %d:%d:%d %d\n",pid,wday,mon+1,mday,hour,min,sec,year+1900);


	//method 2:using ctime over the time method to get the string representation of the time in seconds


	//ctime() takes in a pointer to the calendar time and gives a pointer to a character string(so a c string)--which we can directly print
char *store_time=ctime(&result1);
if(store_time==NULL){printf("the ctime() method crashed");exit(1);}
	printf("PID: %d CURRENT TIME: %s\n",pid,store_time);


	//method 3:using asctime over localtime over time method to get the same string as method 2 above
	//2 steps-
	//step 1:localtime is used to convert the time given by the calendar time into the local time of the computer running this current process
	//so alll the values inside the struct returned by the method are relative to the user computer's time zone
	//step 2:asctime method converts the values inside the struct of localtime we give it into a c string just of  the same format as the ctime method
	//difference b/w ctime and asctime is that asctime takes in a pointer to a struct with all its data members containing individual info which we can extract directly from the time object using localtime() method
	//but ctime does this intermediate step of using localtime method by itself and thus tkes in a time object and directly returns us the c string

//	printf("PID: %d CURRENT TIME: %s\n",pid,asctime(&store_local1));


	alarm(number_sec);//again setting up the alarm
}
/*
 *this method defines customized way to handle the usr1 signal/exception
 */
void handler_SIGUSR1()
{
	c++;
	printf("SIGUSR1 handled and counted!\n");
}
/*
   this method is used to define customized way to handle the signal interrupt
 */
void handler_SIGINT()
{
	printf("SIGINT handled.\nSIGUSR1 was handled %d times.Exiting now.\n",c);
	exit(0);
}
/* 
   this method is used to call and run the methods and the whole program
 */
int main()
{


	printf("PID and time print every 4 seconds\nType Ctrl-C to end the program.\n");
	alarm(number_sec);
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	//note that the struct we defined has 5 members-sa_handler(pointer to the function which can take in the signal and handle it as defined by the programmeer), sa_sigaction(either use this or sa_handler), sa_mask(which defines the set of signals to be blocked during execution of the sa_handler function whose pointer we are passing)
	//now assigning each member its values
	sa.sa_handler=handler_SIGALRM;
	//nothing elss to set for the struct
	//check the condition of the working of yhe exception handler for it to be not equal to null
	if(sigaction(SIGALRM,&sa,NULL)!=0)
	{
		//we called the sigaction() function[[note this is not hte sigaction struct]] and gave it the argument of the type of exception which if found will activate this exception handler code, then we gave it the sigaction struct which contains the location where to find the code to handle this exception type ,and then the 3rd argument specifies sth etra we don't care about
		printf("error found and we tried to handle it but we couldn't");
		exit(1);
	}


	//making another sigaction hndler code-again we will call another handler through this sigaction struct and sigaction() combination-just this time give different pointer to a different function
	struct sigaction sa2;
	memset(&sa2,0,sizeof(sa2));
	sa2.sa_handler=handler_SIGUSR1;
	//now check the return value of the 2nd exception handler
	if(sigaction(SIGUSR1,&sa2,NULL)!=0)
	{
		printf("we couldn't handle the exeption");
		exit(1);
	}


	//making the 3rd exception handler caller to handle the interrupt signal(either do ctrl+c or use kill -SIGINT <pid>) to give this signal from the linux command shell
	struct sigaction sa3;
	//making the sa_handler of this struct point to the new handler we made fopr interrup exception handling
	memset(&sa3,0,sizeof(sa3));//setting the bits of the sa3 struct to 0 for some safety purposes
	sa3.sa_handler=handler_SIGINT;
	if(sigaction(SIGINT,&sa3,NULL)!=0)
	{
		printf("not able to handle interupt exception");
		exit(0);
	}


	//ANOTHER CONCPEPT WE CAN APPLY IS TO USE THE STRUCT SA 3 TIMES INSTEAD OF MAKING 3 DIFFERENT STRUCTS AND USING MEMSET ON ALL THE 3 STRUCTS-IF WE ARE NEVER REUTILIZING THE SAME STRUCT FOR HANDLING AN EXCEPTION CPDE WE HAVE ALREADY WRITTEN IN OUR PROGRAM, THEN WE CAN ALWAYS KEEP ON CHANGING THE SA_HANDLER MEMBER IOF THE SAME STRUCT TO JUST POINT IT TO THE NEW HANDLERS WE ARE MAKING
	//THE CONCEPT OF SAACTION AND CORRESPONDING HANDLER IS SIMILAR TO THE CEONCEPT OF USING TRY CATCH IN JAVA-WE CAN HAVE MANY EXCEPTION BLOCKS BUT ALL OF THEM CAN BE ASOCIATED WITH ONE TRY BUT NOT MORE THAN 1 TRY CAN BE ASSOCIATED WITH ONE EXCEPTION HANDLER BLOCK
	//IN THE SAME WAY, WE CAN HVE ONLY ONE SAACTION BUT FOR THAT WE HAVE TO SPECIFY THE TYPE OF EXCEPTION WE ARE HANDLING-SO ONE SAACTION CAN HAVE MULTIPLE HANDLERS BUT NOT THE OTHER WAY ROUND
	//SAACTION IS EQUIVALEND TO TRY BLOCK AND HANDLER(EACH) IS LIKE DIFFERENT EXCEPTION BLOCKS
	while(1)
	{
	}
	return 0;
}
