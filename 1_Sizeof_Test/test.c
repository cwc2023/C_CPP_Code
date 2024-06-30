#include<stdio.h>

struct test
{
    /* data */
    char a ; 
    int b ; 
    char c[2] ; 
};

int main()
{
    struct test a1 ; 
    int len  = sizeof(a1) ; 
    printf("the strcut len is : %d\n", len ) ;

}