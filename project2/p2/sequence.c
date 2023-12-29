int * create_sequence(int *x0,m)
{
    //we have received the pointer to the first element which we will keep on overriding
    //m and b are same parameters-so they are added and manipulated in the main method
    printf("%p and %i",x0,*x0);
    x0=&(*(x0)*m);//dereferencing the x0 pointer,multiplying m offset-calculating the new address
    //now x0 has the new address which oints to the new value
    return x0;//x0 has the address of integer-so we don't have  to use &x0 to get the address
}
int main(int argc,int *argv[])
{
    printf("%p ",argv);
    //argv is the pointer to 1d array of integers' pointers
    if(argc!=5)
    {
        exit(1);
    }
    //formula-
    //xN=x(N-1)*m +b
    int n=*(argv+1);//dereferencing the 2rd element  of the argv array
    int x0=*(argv+2);//dereferencing the 3th element of the argv array
    int b=*(argv+4);
    int m=*(argv+3);
    printf("%i ",x0);
    printf("n is %i",n);
    printf("n is %i",m);
    printf("n is %i",b);
    while(n-->=0)
    {
        printf("%i ",(x0=*(create_sequence(&x0,m)))+b);
        printf("x0 is %i",&x0);
    }
}