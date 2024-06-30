#include<iostream>

using namespace std ; 


class ListNode{
public: 
      int val ; 
      ListNode * next ; 
      ListNode(int x):val(x) , next(NULL){} ; 
};


class Solution{
    public:
    ListNode  *removeDupNOde(ListNode *head)
    {
        ListNode *current = head ; 
        while(current != NULL)
        {
            ListNode *runner = current ; 
            while(runner->next != NULL)
            {
                if(runner->next->val == current->val)
                {
                    runner->next = runner->next->next ; 
                }
                else
                {
                    runner = runner->next ; 
                }
            }
            current = current->next ; 
        }
        return head ; 
    }
};

int main()
{
    ListNode * head = new ListNode(1) ;
    head->next = new ListNode(2) ;
    head->next->next = new ListNode(3) ;
    head->next->next->next = new ListNode(2) ;
    head->next->next->next->next = new ListNode(1) ;

    ListNode * temp = head ; 
    while(temp !=NULL)
    {
        cout<<temp->val<< " " ;
        temp = temp->next ; 
    }
    Solution sol ;
    ListNode * result = sol.removeDupNOde(head) ;

    cout << endl ; 

    while(result != NULL)
    {
        cout<<result->val<<" " ; 
        result = result->next ; 
    }
    return 0 ;
    
}