#include <stdio.h>
#include <string.h>
#define NUM_ROWS 3000
#define NUM_COLS 500
int a[NUM_ROWS][NUM_COLS];
int main()
{
for(int i=0;i<NUM_COLS;i++)
{
for(int j=0;j<NUM_ROWS;j++)
{
a[j][i]=i+j;
}
}
return 1;
}
