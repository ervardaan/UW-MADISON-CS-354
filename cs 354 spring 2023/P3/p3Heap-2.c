///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission SPRING 2023, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main File:        p3Heap.c
// This File:        p3Heap.c
// Other Files:      NONE
// Semester:         CS 354 Lecture 02? Spring 2023
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
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.--------NONE
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.-----NONE USED
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "p3Heap.h"

/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader {           

	int size_status;

	/*
	 * Size of the block is always a multiple of 8.
	 * Size is stored in all block headers and in free block footers.
	 *
	 * Status is stored only in headers using the two least significant bits.
	 *   Bit0 => least significant bit, last bit
	 *   Bit0 == 0 => free block
	 *   Bit0 == 1 => allocated block
	 *
	 *   Bit1 => second last bit 
	 *   Bit1 == 0 => previous block is free
	 *   Bit1 == 1 => previous block is allocated
	 * 
	 * Start Heap: 
	 *  The blockHeader for the first block of the heap is after skip 4 bytes.
	 *  This ensures alignment requirements can be met.
	 * 
	 * End Mark: 
	 *  The end of the available memory is indicated using a size_status of 1.
	 * 
	 * Examples:
	 * 
	 * 1. Allocated block of size 24 bytes:
	 *    Allocated Block Header:
	 *      If the previous block is free      p-bit=0 size_status would be 25
	 *      If the previous block is allocated p-bit=1 size_status would be 27
	 * 
	 * 2. Free block of size 24 bytes:
	 *    Free Block Header:
	 *      If the previous block is free      p-bit=0 size_status would be 24
	 *      If the previous block is allocated p-bit=1 size_status would be 26
	 *    Free Block Footer:
	 *      size_status should be 24
	 */
} blockHeader;         

/* Global variable - DO NOT CHANGE NAME or TYPE. 
 * It must point to the first block in the heap and is set by init_heap()
 * i.e., the block at the lowest address.
 */
blockHeader *heap_start = NULL;     

/* Size of heap allocation padded to round to nearest page size.
 */
int alloc_size;

/*
 * Additional global variables may be added as needed below
 * TODO: add global variables needed by your function
//making array of structs of blockHeader

 */
//struct blockHeader heap[alloc_size/8];//maximum no of blocks we can have


/* 
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if size < 1 
 * - Determine block size rounding up to a multiple of 8 
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split 
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements 
 *       - Update all heap block header(s) and footer(s) 
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 *   Return if NULL unable to find and allocate block for required size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the 
 *       available memory for the requesterr.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* balloc(int size) {     

	//TODO: Your code goes in here.
	//try to check if the previous block is allocated or not-accordingly make the size_status of the header of this incoming block
	if(size<1)
	{
		return NULL;
	}
	//size+=((size+size_of(blockheader))%8=c)==0?0:8-c;
	int c;  int real_size;
	size=(c=(size+sizeof(blockHeader))%(2*sizeof(blockHeader)))==0?0+size+sizeof(blockHeader):(2*sizeof(blockHeader))-c+sizeof(blockHeader)+size;//size=pl+pd only
																									 //if size is more than what is allocated
																									 //if(size>heap_start->size_status){
																									 //printf("allocation size is more than what can be supported by the heap");
																									 //return NULL;
																									 //exit(0);
																									 //}
																									 //size+=4;//adding space for header to pl+pd
																									 //printf("size of this block is %i",size);  
	/* checking some padding if possible by adding and checking both the types of sizes*/
	blockHeader *current=heap_start;
	//printf("current=%pandheap_start=%p",current,heap_start);
	blockHeader *stored_best=NULL;

	while(current->size_status!=1)
	{
		int current_size=current->size_status;
		//check only size and not size_status included--we can mask the last 2 bits-make them 0 and then find size
		//we have some current bloackheader for some block
		if(!(current_size & 1))
		{
			if(current_size & 2)
			{
				current_size-=2;

				//previous block is allocated-substract 2 
			}
			//the block is free
			//setting the storing header for best fit
			//if(!(stored_best->size_status) &1){
			//if(stored_best->size_status & 2){
			//stored_best->size_status-=2;}
			//stored_best->size_status-=1;}
			/*
			   if(stored_best==NULL && current_size>=size){
			   stored_best=current;stored_best->size_status=current_size;real_size=current->size_status;
			//stored_best has a false size-only size of payload is stored rather than status of both bits included
			}
			else{
			if(stored_best->size_status>current_size)
			{
			stored_best=current;}
			}
			 */
			if(current_size>=size)
			{

				if(stored_best==NULL){
					real_size=current->size_status;
					stored_best=current;stored_best->size_status=current_size;

				}
				else{
					if(stored_best->size_status>current_size)
					{
						real_size=current->size_status;
						stored_best=current;stored_best->size_status=current_size;
					}
				}
			}
		}
		//now getting the next block
		else{
			if(current_size & 1){ current_size-=1;}
			if(current_size & 2){ current_size-=2;}
		}
		if(current_size & 2){
			current=(blockHeader*)((void*)current+current_size/*+2*sizeof(blockHeader)*/);
		}

		else{
			current=(blockHeader*)((void*)current+current_size/*+sizeof(blockHeader)*/);
		}

	}

	if(stored_best!=NULL)
	{

		if(stored_best->size_status-(size)>=(2*sizeof(blockHeader)))//16 or 8-if 8 then no space for payload-only header and footer in the free block
		{
			//stored_best->size_status=real_size;
			//block with only header and footer with no payload or padding is also valid block
			//we can make a free block
			//we have to make 2 blocks now and the original one will be made null-garbage collected
			stored_best->size_status=size+1;
			//stored_best->size_status-=4;
			//remove header only(no footer as it is allocated)
			//making new block-free(with footer as well)

			//if(real_size%2!=0){real_size-=1;}
			if(real_size & 2){real_size-=2;
				stored_best->size_status+=2;
			}
			blockHeader *hd2=(blockHeader*)((void*)stored_best+size);hd2->size_status=real_size-size;//4 for hd2,ft's space
																									 //set p to 1 and s to 0

			blockHeader *ft=(blockHeader*)((void*)hd2+real_size-size-(sizeof(blockHeader)));
			ft->size_status=hd2->size_status;//only size for the footer-but for header we added 2(this block is free so it has a footer-its predecessor which we made has no footer and so we added only 1 as it was allocated-since it was allocated we added 2 for this block(p bit)
			hd2->size_status+=2;
		}
		else{
			//stored_best->size_status=real_size;
			//block with only header and footer with no payload or padding is also valid block
			//we can make a free block
			//we have to make 2 blocks now and the original one will be made null-garbage collected
			//get the next block after this stored_best block and make its p bit as 1
			blockHeader *next1=(blockHeader*)((void*)stored_best+stored_best->size_status);
			if(next1->size_status!=1){
				next1->size_status+=2;}
			stored_best->size_status=size+1;
			//stored_best->size_status-=4;
			//remove header only(no footer as it is allocated)
			//making new block-free(with footer as well)

			//if(real_size%2!=0){real_size-=1;}
			if(real_size & 2){real_size-=2;
				stored_best->size_status+=2;
			}
			//no splitting 
		}
		//stored_best->size_status+=1;//now allocated


		return (void*)stored_best+sizeof(blockHeader);//return the address of payload rather than that of header
	}
	else{
		return NULL;}
} 

/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 */                    
int bfree(void *ptr) {    
	//TODO: Your code goes in here.
	//we get the allocated address of the payload but we want to get the address of its header   
	if(ptr==NULL)
	{
		return -1;
	}
	ptr=(blockHeader*)((void*)ptr-(sizeof(blockHeader)));//ptr=(blockHeader*)ptr;
	int value=(int)((int*)ptr);
	int hs_value=(int)((int*)heap_start);
	if( (value+(sizeof(blockHeader)))%(2*sizeof(blockHeader))!=0)
	{
		return -1;
	}
	if( ( value)<hs_value)
	{
		return -1;
	}
	if(value>hs_value+alloc_size)
	{
		return -1;
	}
	if( (((blockHeader*)ptr)->size_status & 1)==0)
	{
		return -1;}
	blockHeader *block=(blockHeader*)ptr;
	blockHeader *next=NULL;  blockHeader *footer=NULL; 
	block->size_status=block->size_status-1;//change the s bit form 1 to 0
	if(block->size_status & 2){
		next=(blockHeader*)((void*)block+block->size_status-2);
		footer=(blockHeader*)((void*)block+block->size_status-2-sizeof(blockHeader));
	}
	else{
		next=(blockHeader*)((void*)block+block->size_status);
		footer=(blockHeader*)((void*)block+block->size_status-(sizeof(blockHeader)));
	}

	//giving additional footer as it wasn't there before wheen the block was allocated

	footer->size_status=block->size_status;
	//removing the p bit if the previous block was allocated or not
	if(footer->size_status & 2){ footer->size_status-=2;}
	if(next->size_status!=1)//next block is not the end mark
	{
		next->size_status-=2;//setting the p bit int he next header as the previous one is now free
	} 
	return 0;
} 

/*
 * Function for traversing heap block list and coalescing all adjacent 
 * free blocks.
 *
 * This function is used for user-called coalescing.
 * Updated header size_status and footer size_status as needed.
 */
int coalesce() {
	//TODO: Your code goes in here.
	blockHeader *current=heap_start;int y=0;//kep track of atleast one coalesce instance
	while(current->size_status!=1)
	{
		//2 methods-either keep  going and collecting the free blocks until we reach an allocated one
		//or keep merging the previous and current blocks
		//method 2-check the status of current block and previous block-we always coalesce the current and previous ones and then go ahead
		//we change the size status of the first(previous) of the 2 freed blocks and then the current block-even though its header exists -is never accessed as we directly go to the next of current from 
		//previous of current as the size was updated
		//problem-we can't access the header of the previous block to change the size status of that block after coalescing
		//method 1-start fom starting and go till an allocated one is found
		if(!(current->size_status & 1)){
			int p_check=0;
			int size=current->size_status;
			if(current->size_status & 2){size-=2;p_check=1;}

			blockHeader *next=(blockHeader*)((void*)current+size);
			while(!(next->size_status & 1))
			{
				y++;
				if(next->size_status &2){ next=(blockHeader*)((void*)next+next->size_status-2);}
				else{
					next=(blockHeader*)((void*)next+next->size_status);
				}
			}
			int new_size=(int)next-(int)current;
			current->size_status=new_size;
			//ste the new status+size for the current block
			if(p_check)//the current block has an allocated previous block
			{
				current->size_status+=2;
			}
			blockHeader *new_footer=(blockHeader*)((void*)next-(sizeof(blockHeader)));
			new_footer->size_status=new_size;
			//next already has the p bit set to 0
			//make the new current as the new allocated block we found-next
			current=next;
		} 
		else{
			//current->size_status+=current->size_status &1?-1:0;
			current->size_status+=current->size_status &2?-3:-1;//already allocated-so directly substract 1 without checking
			current=(blockHeader*)((void*)current+current->size_status);
		}
	}
	return y;//any +ve value works
}


/* 
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int init_heap(int sizeOfRegion) {    

	static int allocated_once = 0; //prevent multiple myInit calls

	int   pagesize; // page size
	int   padsize;  // size of padding when heap size not a multiple of page size
	void* mmap_ptr; // pointer to memory mapped area
	int   fd;

	blockHeader* end_mark;

	if (0 != allocated_once) {
		fprintf(stderr, 
				"Error:mem.c: InitHeap has allocated space during a previous call\n");
		return -1;
	}

	if (sizeOfRegion <= 0) {
		fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
		return -1;
	}

	// Get the pagesize from O.S. 
	pagesize = getpagesize();

	// Calculate padsize as the padding required to round up sizeOfRegion 
	// to a multiple of pagesize
	padsize = sizeOfRegion % pagesize;
	padsize = (pagesize - padsize) % pagesize;

	alloc_size = sizeOfRegion + padsize;

	// Using mmap to allocate memory
	fd = open("/dev/zero", O_RDWR);
	if (-1 == fd) {
		fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
		return -1;
	}
	mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == mmap_ptr) {
		fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
		allocated_once = 0;
		return -1;
	}

	allocated_once = 1;

	// for double word alignment and end mark
	alloc_size -= 8;

	// Initially there is only one big free block in the heap.
	// Skip first 4 bytes for double word alignment requirement.
	heap_start = (blockHeader*) mmap_ptr + 1;

	// Set the end mark
	end_mark = (blockHeader*)((void*)heap_start + alloc_size);
	end_mark->size_status = 1;

	// Set size in header
	heap_start->size_status = alloc_size;

	// Set p-bit as allocated in header
	// note a-bit left at 0 for free
	heap_start->size_status += 2;

	// Set the footer
	blockHeader *footer = (blockHeader*) ((void*)heap_start + alloc_size - 4);
	footer->size_status = alloc_size;

	return 0;
} 

/* 
 * Function can be used for DEBUGGING to help you visualize your heap structure.
 * Traverses heap blocks and prints info about each block found.
 * 
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void disp_heap() {     

	int    counter;
	char   status[6];
	char   p_status[6];
	char * t_begin = NULL;
	char * t_end   = NULL;
	int    t_size;

	blockHeader *current = heap_start;
	counter = 1;

	int used_size =  0;
	int free_size =  0;
	int is_used   = -1;

	fprintf(stdout, 
			"*********************************** HEAP: Block List ****************************\n");
	fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
	fprintf(stdout, 
			"---------------------------------------------------------------------------------\n");

	while (current->size_status != 1) {
		t_begin = (char*)current;
		t_size = current->size_status;

		if (t_size & 1) {
			// LSB = 1 => used block
			strcpy(status, "alloc");
			is_used = 1;
			t_size = t_size - 1;
		} else {
			strcpy(status, "FREE ");
			is_used = 0;
		}

		if (t_size & 2) {
			strcpy(p_status, "alloc");
			t_size = t_size - 2;
		} else {
			strcpy(p_status, "FREE ");
		}

		if (is_used) 
			used_size += t_size;
		else 
			free_size += t_size;

		t_end = t_begin + t_size - 1;

		fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status, 
				p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);

		current = (blockHeader*)((char*)current + t_size);
		counter = counter + 1;
	}

	fprintf(stdout, 
			"---------------------------------------------------------------------------------\n");
	fprintf(stdout, 
			"*********************************************************************************\n");
	fprintf(stdout, "Total used size = %4d\n", used_size);
	fprintf(stdout, "Total free size = %4d\n", free_size);
	fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
	fprintf(stdout, 
			"*********************************************************************************\n");
	fflush(stdout);

	return;  
} 


// end p3Heap.c (Spring 2023)                                         


