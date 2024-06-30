#include<iostream>
#include<vector>
#include<algorithm>

using namespace std ;

// insert sort 

void insert_sort(vector<float>& nums)
{
	for(int i = 1 ; i < nums.size() ; ++i)
	{ 
	        float  insert_val = nums[i] ; 
		int last_pos = i -1 ; 

		while(last_pos >= 0 &&  insert_val < nums[last_pos])
		{ 
			nums[last_pos + 1] = nums[last_pos] ; 	
			last_pos-- ; 	
		}
		nums[last_pos+1] = insert_val ;
	}

}

int main()
{
	vector<float> nums = {1.2,3.5,2.1,0.5,0.8,1.2,1.3,1.5,4.5,8.9} ; 
	cout<< "the orginal  nums: "; 
	for(const auto& num : nums)
	{
		cout<< num <<" " ; 
	}
	cout << endl ;

        insert_sort(nums) ; 	
	cout<< "the insert sort nums: ";
        for(const auto& num : nums) 
        {
                cout<< num <<" " ;
        }
        cout << endl ;
	return 0 ; 
}

