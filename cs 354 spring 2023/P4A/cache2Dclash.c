#include <stdio.h>
#include <string.h>
#define NUM_ROWS 128
#define NUM_COLS 8
#define ITERATION 100
int a[NUM_ROWS][NUM_COLS];
int main()
{
for(int k=0;k<ITERATION;k++)
{
for(int i=0;i<NUM_ROWS;i+=64)
{
for(int j=0;j<NUM_COLS;j++)
{
a[NUM_ROWS][NUM_COLS]=k+i+j;
}
}
}
return 1;
}

