////////////////////////////////////////////////////////////////////////////////
// Main File:        csim.c
// This File:        csim.c
//
// Semester:         CS 354 Spring 2023
// Instructor:       Debbra Deppeler
//
// Author:           vardaan kapoor
// Email:            vkapoor5
// CS Login:         vardaan
//
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friencs, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          None
//
//
// Online sources:   None
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Spring 2023
//
////////////////////////////////////////////////////////////////////////////////

/*
 * csim.c:
 * A cache simulator that can replay traces (from Valgrind) and output
 * statistics for the number of hits, misses, and evictions.
 * The replacement policy is LRU.
 *
 * Implementation and assumptions:
 *  1. Each load/store can cause at most one cache miss plus a possible eviction.
 *  2. Instruction loads (I) are ignored.
 *  3. Data modify (M) is treated as a load followed by a store to the same
 *  address. Hence, an M operation can result in two cache hits, or a miss and a
 *  hit plus a possible eviction.
 */

#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

/******************************************************************************/
/* DO NOT MODIFY THESE VARIABLES **********************************************/

// Globals set by command line args.
int b = 0; // number of block (b) bits
int s = 0; // number of set (s) bits
int E = 0; // number of lines per set

// Globals derived from command line args.
int B; // block size in bytes: B = 2^b
int S; // number of sets: S = 2^s

// Global counts to track cache statistics in access_data().
int hit_cnt = 0;
int miss_cnt = 0;
int evict_cnt = 0;

// Global to control trace output
int verbosity = 0; // print trace if set
/******************************************************************************/

// Type mem_addr_t: Use when dealing with addresses or address masks.
typedef unsigned long long int mem_addr_t;

// Type cache_line_t: Use when dealing with cache lines.
// TODO - COMPLETE THIS TYPE
typedef struct cache_line
{
    long counting;
    char valid;
    mem_addr_t tag;
   
} cache_line_t;

// Type cache_set_t: Use when dealing with cache sets
// Note: Each set is a pointer to a heap array of one or more cache lines.
typedef cache_line_t *cache_set_t;

// Type cache_t: Use when dealing with the cache.
// Note: A cache is a pointer to a heap array of one or more sets.
typedef cache_set_t *cache_t;

// Create the cache we're simulating.
// Note: A cache is a pointer to a heap array of one or more cache sets.
cache_t cache;
long count = 1;
mem_addr_t sb = 0;

/* TODO - COMPLETE THIS FUNCTION
 * init_cache:
 * Allocates the data structure for a cache with S sets and E lines per set.
 * Initializes all valid bits and tags with 0s.
 */
void init_cache()
{
    S = pow(2, s); // S= 2^s
    B = pow(2, b); // B=2^b
    int t = B;
    for (int i = 0; i < s; i++)
    {
        sb += t;
        t *= 2;
    }
    // allocate cache with S sets
    cache = malloc(sizeof(cache_set_t) * S);
    if (cache == NULL)
    {
        printf("malloc wrong");
        exit(1);
    }

    // allocate E lines per set
    for (int i = 0; i < S; i++)
    {
        cache[i] = malloc(sizeof(cache_line_t) * E);
        if (cache[i] == NULL)
        {
            printf("malloc fail");
            exit(1);
        }
        // allocate cache blocks per line
        for (int j = 0; j < E; j++)
        {
            (*(cache + i) + j)->valid = '0'; // char not an int
            (*(cache + i) + j)->tag = 0;
            (*(cache + i) + j)->counting = 0;
        }
    }
}
//extra methods used to create binary to decimal conversions an print verbose mode if asked
/*
mem_addr_t getDecimal(mem_addr_t number)
{
	int c=0;mem_addr_t total_dec=0;
	while(number!=0){
		int d=number%10;
		if(d==1){
			total_dec+=pow(2,c);
		}
		else{
			total_dec=total_dec;
		}
		number/=10;
		c++;
	}
	return total_dec;
}
mem_addr_t getBinary(unsigned long long int number){



	mem_addr_t new_num=0;mem_addr_t c=0;//changed from int
	while(number!=0){
		int d=number%2;
		//new_num=(d==1)?pow(10.0,((double)c))*(d)+new_num:new_num;
		if(d==1){
			new_num=new_num+pow(10.0,(double)c)*d;//removed casting of double around c
		}
		else{
			new_num=new_num;

		}
		number/=2;
		c++;
		//add the extra 0s at the end of the method by checking the number of digits with the counter c

	}
	//checking to add extra number of 0s at the beginning 
	return new_num;
}  

void printdata()
{
	for(int i=0;i<S;i++)
	{
		for(int j=0;j<E;j++)
		{
			cache_line_t line=*(*(cache+i)+j);
			printf("(s,E): %i,%i, v bit %i and tag %llu and counter %lli",i,j,line.valid,line.tag,line.counter);
			printf("\n");
		}
	}
}
*/
/* TODO - COMPLETE THIS FUNCTION
 * free_cache:
 * Frees all heap allocated memory used by the cache.
 */
void free_cache()
{

    for (int i = 0; i < S; i++)
    {
        free(cache[i]);
        cache[i] = NULL;
    }

    free(cache);
    cache = NULL;
}

/* TODO - COMPLETE THIS FUNCTION
 * access_data:
 * Simulates data access at given "addr" memory address in the cache.
 *
 * If already in cache, increment hit_cnt
 * If not in cache, cache it (set tag), increment miss_cnt
 * If a line is evicted, increment evict_cnt
 */
void access_data(mem_addr_t addr)
{
//byte shifting and manipulation without >> or <<
/*
long long int convert=(long long int)addr;
printf("%llx in address integer",addr);
printf("%llu is the address\n",addr);//if 32-unsigned notation(magnitude)
printf("%llx is the conversion\n",convert); //then 20(actually in hex)    
printf("binary conversion of addr %llx\n",getBinary(addr));
printf("%llu is the value",(mem_addr_t)16294176);
//printf("%llu after change\n",addr>>2);//then 8
mem_addr_t addr1;
//printf("seperating s bits %llu\n",(addr1=addr>>b));//magnitude of s and t left
//printf("in hex value %llx\n",(long long int)addr1);//hex of s and t left

	//int B=pow(2,b);int S=pow(2,s);
	///mask bits to get b bitsexit
	//printf("value is %llx",addr);
	//printf("value again is %llu",addr);
//printf("%llu is hex value of addr",(long long int)addr &((long long int)(pow(2,b))));
	
mem_addr_t s_bits=0;mem_addr_t b_bits=0;mem_addr_t t_bits=0;
mem_addr_t binary=getBinary(addr);
	//mem_addr_t binary=getBinary(addr);//only s and t left in binary
//mem_addr_t collects=(mem_addr_t)(((int)binary)%((int)(pow(10,b))));
//printf("s bits are %llu\n",collects);
//printf("%llx is binary",binary);
printf("%llu is binary",binary);
	if(b!=0){
		b_bits=(mem_addr_t)(((int)binary)%((int)(pow(10,b))));

		//printdata();
		//extra testing-
		//binary=10101;
		
		   //printf("bbb %llu",binary);
		   //printf("binary val is %i",(int)binary);
		   //printf("remainder %i",((int)binary)%(int)(pow(10,b)));
		   //printf("simple rem %llu",binary%(int)(pow(10,b)));
		   //printf("check val %i",(int)(pow(10,b)));


		 //  printf("the val of b_bits %llu",b_bits);
		 
		binary=getDecimal(binary);//first convert and then modify vi >>/<< and then change back to binary
		binary=binary>>b;//remove the leftmost b bits so that the s bits now come to the leftmost index
		binary=getBinary(binary);//getting the binary back
	}
	if(s!=0){


		s_bits=(mem_addr_t)(((int)binary)%((int)(pow(10,s))));
		binary=getDecimal(binary);
		binary=binary>>s;//shift by s bits to the right
		binary=getBinary(binary);
	}
	t_bits=binary;
	new_int t_num=getDecimal(t_bits);
	new_int s_num=getDecimal(s_bits);new_int b_num=getDecimal(b_bits);
	if(verbosity){printf("set is %lli and t tag is %lli\n",s_num,t_num);}
*/
    int total=s+b;
    mem_addr_t tt = addr >> (total);
    mem_addr_t set = (addr & sb) / pow(2, b);

    // check cache for a hit
    for (int i = 0; i < E; i++)
    {
        if ((*(cache + set) + i)->tag == tt)
        {
            if ((*(cache + set) + i)->valid == '1')
            {
                hit_cnt++;
                (*(cache + set) + i)->counting = count;
                count++;
                return;//no value but just break
            }
        }
    }
/*
//printf("new val %llx",a);
	   //printf("newwww %llu",a);
	 //  printf("bin%llu\n ",getBinary(addr));
	 
	//mem_addr_t b_block=addr & (B-1);
	//printf("binb%llu\n",getBinary((unsigned long long int)b_block));
	//mem_addr_t s_block=addr & (int)((pow(2,(s+b)))-B);
	//printf("bins%llu\n",getBinary((unsigned long long int)s_block));
	//mem_addr_t t_block=addr & (int)(addr-S*B);
	
	   //printf("bint%llu\n",getBinary((unsigned long long int)t_block));
	   //printf("b=%llu\n",b_block);printf("s=%llu\n",s_block);printf("t=%llu\n",t_block);
	 //  printf("b in integerr is %llx",b_block);
	 	//now running the actual search after masking and extracting the data bits
	//cache_line_t target=*(*(cache+s_num)+t_num);
	cache_set_t set_target=*(cache+s_num);//getting the particular set
	new_int checkline=0;new_int max_of_counter=0;//stores the maximum of counters
	cache_line_t* line_target=(set_target);cache_line_t* collect_line;
	new_int count=line_target->counter;
	//getting the first line
	new_int index=0;
	for(new_int k=0;k<E;k++)
	{
		//traversing the set
		line_target=(set_target+k);//TODO
		if(max_of_counter<line_target->counter)
		{
			max_of_counter=line_target->counter;
		}
		//checking the tag bit
		if(line_target->counter<count){
			index=k;
		}
		if((line_target->tag==t_num) &( line_target->valid=='1'))
		{
			//got the correct cache
			checkline=1;
			collect_line=line_target;
			hit_cnt++;
			printf("hit");
			break;
		}
		if((line_target->tag==t_num) & (line_target->valid=='0')){
			miss_cnt++;line_target->valid='1';checkline=1;
			collect_line=line_target;
			printf("miss");
			break;
		}
	}
	cache_line_t* empty_line;
	//printdata();

	if(!checkline)
	{
		//we git a miss
		miss_cnt++;
		printf("miss and no match");
		empty_line=(set_target);
		new_int count_empty=0;
		for(new_int j=0;j<E;j++)
		{
			if((set_target+j)->valid=='0')
			{
				empty_line=(set_target+j);
				count_empty++;
				break;
			}
		}
		if(!count_empty)//if this is the case then we didn't find any open cache block in the previous for loop
		{
			printf("eviction");
			//find the eviction victim and evict it
			empty_line=(set_target+index);
			evict_cnt++;
		}
		empty_line->tag=t_num;empty_line->valid='1';
		empty_line->counter=max_of_counter+1;
	}
	else{
		collect_line->counter=max_of_counter+1;
	}
printf("\n");
*/
    // cache miss
    miss_cnt++;
    int min = INT_MAX;//constant defined with max value as a sentinel for comparing
    int eviction = 0;
    for (int i = 0; i < E; i++)
    {
        if ((*(cache + set) + i)->valid == '0') // found an unused line
        {
            (*(cache + set) + i)->tag = tt;
            (*(cache + set) + i)->counting = count;
            count++;
            (*(cache + set) + i)->valid = '1';
            return;
        }
        else if ((*(cache + set) + i)->counting < min)
        {
            min = (*(cache + set) + i)->counting;
            eviction = i;
        }
    }
    // did not find a unused line //need to evict
    evict_cnt++;
    (*(cache + set) + eviction)->tag = tt;
    (*(cache + set) + eviction)->counting = count;
    count++;
    (*(cache + set) + eviction)->valid = '1';
    return;
}

/* TODO - FILL IN THE MISSING CODE
 * replay_trace:
 * Replays the given trace file against the cache.
 *
 * Reads the input trace file line by line.
 * Extracts the type of each memory access : L/S/M
 * TRANSLATE each "L" as a load i.e. 1 memory access
 * TRANSLATE each "S" as a store i.e. 1 memory access
 * TRANSLATE each "M" as a load followed by a store i.e. 2 memory accesses
 */
void replay_trace(char *trace_fn)
{
    char buf[1000];
    mem_addr_t addr = 0;
    unsigned int len = 0;
    FILE *trace_fp = fopen(trace_fn, "r");

    if (!trace_fp)
    {
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while (fgets(buf, 1000, trace_fp) != NULL)
    {
        if (buf[1] == 'S' || buf[1] == 'L' || buf[1] == 'M')
        {
            sscanf(buf + 3, "%llx,%u", &addr, &len);

            if (verbosity)
                printf("%c %llx,%u ", buf[1], addr, len);
            // S OR L access_data is called once but if M called twice
            access_data(addr);
            if (buf[1] == 'M') // modify means load and then store so need an extra access
            {
                access_data(addr);
            }
            // TODO - MISSING CODE
            // GIVEN: 1. addr has the address to be accessed
            //        2. buf[1] has type of acccess(S/L/M)
            // call access_data function here depending on type of access

            if (verbosity)
                printf("\n");
        }
    }

    fclose(trace_fp);
}

/*
 * print_usage:
 * Print information on how to use csim to standard output.
 */
void print_usage(char *argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of s bits for set index.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of b bits for block offsets.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * print_summary:
 * Prints a summary of the cache simulation statistics to a file.
 */
void print_summary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
    FILE *output_fp = fopen(".csim_results", "w");
    assert(output_fp);
    fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
    fclose(output_fp);
}

/*
 * main:
 * Main parses command line args, makes the cache, replays the memory accesses
 * free the cache and print the summary statistics.
 */
int main(int argc, char *argv[])
{
    char *trace_file = NULL;
    char c;

    // Parse the command line arguments: -h, -v, -s, -E, -b, -t
    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch (c)
        {
        case 'b':
            b = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'h':
            print_usage(argv);
            exit(0);
        case 's':
            s = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        default:
            print_usage(argv);
            exit(1);
        }
    }

    // Make sure that all required command line args were specified.
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL)
    {
        printf("%s: Missing required command line argument\n", argv[0]);
        print_usage(argv);
        exit(1);
    }

    // Initialize cache.
    init_cache();

    // Replay the memory access trace.
    replay_trace(trace_file);

    // Free memory allocated for cache.
    free_cache();

    // Print the statistics to a file.
    // DO NOT REMOVE: This function must be called for test_csim to work.
    print_summary(hit_cnt, miss_cnt, evict_cnt);
    return 0;
}

// Spring 202301
