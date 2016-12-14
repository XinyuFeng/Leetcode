//Given an unsorted integer array, find the first missing positive integer.

//For example,
//Given [1,2,0] return 3,
//and [3,4,-1,1] return 2.

//Your algorithm should run in O(n) time and uses constant space.


class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        
        if(nums.empty()) return 1;
        int len=nums.size();
        for(int i=0; i<len; ++i){
            while(nums[i]>0 and nums[i]<=len and nums[i]!=nums[nums[i]-1]) //swap iteratively
               swap(nums[i], nums[nums[i]-1]); //nums[i] equals to i+1;
        }
        
        for(int i=0; i<len; ++i){  //find first i that nums[i]!=i+1;
            if(nums[i]!=i+1)
                return i+1;
        }
        return len+1;
    }
};
