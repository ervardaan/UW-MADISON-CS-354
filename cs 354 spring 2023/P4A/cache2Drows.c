#include <stdio.h>
#include <string.h>
#define NUM_ROWS 3000
#define NUM_COLS 500
int a[NUM_ROWS][NUM_COLS];
int main()
{
  for(int i=0;i<NUM_ROWS;i++)
    {
      for(int j=0;j<NUM_COLS;j++)
	{
	  a[i][j]=i+j;
	}
    }
  return 1;
}
