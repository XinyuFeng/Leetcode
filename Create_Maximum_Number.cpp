//Here is the top-voted based C++ implementation by myself.

//The key idea is how to divide the original problem into 2 easy problem.

//first, It is that how we can get max-number in one array of length k

//second, It is that how to merge all the number of 2 array to form max number

//third, it is that by loop all the N possible combination, we get the final solution.

//Here is the code:

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int len1=nums1.size(), len2=nums2.size();
        vector<int> result(k, 0);
        string result_str;
        for(int i=max(0,k-len2); i<=k && i<=len1; i++){
            vector<int> sub_1=help(nums1, i);
            vector<int> sub_2=help(nums2, k-i);
            vector<int> candidate=merge(sub_1, sub_2, k);
            ostringstream str_c;
            for(auto number:candidate) str_c<<number;
            if(result_str=="" || str_c.str().compare(result_str)>0){
                result_str=str_c.str();
                result=candidate;
            }
        }
        return result;
    }
    
    vector<int> help(vector<int>& nums, int k){
        int len=nums.size();
        int count=0;
        vector<int> result(k, 0);
        for(int i=0; i<len; i++){
            /** pop out the smaller number than nums[i] **/
            while(count>0 && len-i+count>k && nums[i]>result[count-1]) count--;
            if(count<k)  result[count++]=nums[i];
        }
        return result;
    }
    
    /** k=len1+len2 **/
    vector<int> merge(vector<int>& nums1, vector<int>& nums2, int k){
        vector<int> result(k, 0);
        ostringstream num_str1, num_str2;
        string str1, str2;
        for(auto num:nums1)  num_str1<<num;
        for(auto num:nums2)  num_str2<<num;
        str1=num_str1.str();
        str2=num_str2.str();
        for(int i=0, j=0, r=0; r<k; r++){
            result[r]=str1.substr(i).compare(str2.substr(j))>0 ? nums1[i++] : nums2[j++];
        }
        return result;
    }
};
