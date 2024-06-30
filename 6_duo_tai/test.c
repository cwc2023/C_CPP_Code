#include <stdio.h>


typedef struct Base {
	int (*send) (struct Base* base) ; 

}Base,  *Base_p; 

typedef struct Test{
	Base base ; 
	int a ; 
	int b ; 

} Test, *Test_p; 


int my_send_1(Base_p base)
{
	Test_p test = (Test_p) base ; 
	printf("the pointer point the send_1\n") ; 
	return test->a + test->b ;		
} 	

int my_send_2(Base_p base) 
{
	Test_p test = (Test_p) base ; 
	printf("the pointer point the send_2\n") ;  
	return test->a + test->b ; 
}

int main() 
{
	Test test_1 ; 
        test_1.a = 1 ; 
	test_1.b = 2 ;
	test_1.base.send = my_send_1 ; 

	Base_p p = (Base_p)&test_1 ; 

	int res_1 = p->send(p) ; 
	printf("the result_1 is : %d\n" , res_1);

	
	Test test_2 ;
	test_2.a =1 ; 
	test_2.b =2;
	test_2.base.send = my_send_2 ;
       	Base_p p_1 = (Base_p)&test_2 ; 
	int res_2 = p_1->send(p_1) ; 
	printf("the res_2 is %d\n" ,res_2) ; 
		

	return 0 ; 

}
