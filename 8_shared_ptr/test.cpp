#include<iostream>
#include<memory>

using namespace std ; 

int main() 
{
    // cpp 共享指针
    shared_ptr<int> ptr_1(new int(520)) ; 
    cout << "ptr1管理的内存引用计数" << ptr_1.use_count() << endl ; 

    shared_ptr<int> ptr_2(ptr_1) ; 
    cout << "ptr1管理的内存引用计数" << ptr_1.use_count() << endl ; 
    return 0 ; 

}
