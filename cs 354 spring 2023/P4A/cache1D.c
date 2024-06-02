#include <stdio.h>
#include <string.h>
/////////////
//author-name:vardaan kapoor
//lecture:lecture2
////////////
#define GLOBAL_N 100000
int a[GLOBAL_N];
int main()
{

  int len=sizeof(a)/sizeof(a[0]);//divide the total no of byte by the no of bytes taken by one element of the array
printf("size of a is %i",sizeof(a));
printf("length is %i",len);
  for(int i=0;i<len;i++)
    {
      a[i]=i;
    }
  return 1;
}
