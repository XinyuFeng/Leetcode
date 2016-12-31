//divide and conquer
class Solution {

protected:
    void merge_countSmaller(int* indices, int first, int last, vector<int>& results, vector<int>& nums){
        int count=last-first;
        if(count>1){
            int step=count/2;
            int mid=first+step;
            merge_countSmaller(indices, first, mid, results, nums);
            merge_countSmaller(indices, mid, last, results, nums);
            int tmp[count];
            int idx1=first, idx2=mid;
            int semicount=0, i=0;
            while(idx1<mid or idx2<last){
                if((idx2==last) or(idx1<mid and nums[indices[idx1]]<=nums[indices[idx2]])){
                    tmp[i++]=indices[idx1];
                    results[indices[idx1++]]+=semicount;
                }
                else{
                    tmp[i++]=indices[idx2++];
                    ++semicount;
                    
                }
            }
            memcpy(indices+first, tmp, 4*count);
            
        }
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int n=nums.size();
        vector<int> results(n,0);
        if(nums.empty()) return results;
        int indices[n]={0};
        for(int i=0; i<n; ++i){
            indices[i]=i;
        }
        merge_countSmaller(indices, 0, n, results, nums);
        return results;
    }
};

//BST Way
class Solution {
public:

    struct Node{
        Node* left;
        Node* right;
        int val, sum, dup;
        Node(int v, int s){
            left=NULL;
            right=NULL;
            val=v;
            sum=s;
            dup=1;
        }
    };
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);
        if(nums.empty()) return ans;
        Node* root=new Node(INT_MAX, 0);
        for(int i=nums.size()-1; i>=0; --i){
            insert(root, nums[i], ans, i, 0);
        }
        return ans;
    }
    
    void insert(Node* root, int num, vector<int>& ans, int i, int presum){
        Node* tmp=root;
        while(tmp){
            if(tmp->val==num){
                tmp->dup++;
                ans[i]=presum+tmp->sum;
                return;
            }
            else if(tmp->val>num){
                tmp->sum++;
                if(!tmp->left){
                    tmp->left=new Node(num, 0);
                    ans[i]=presum;
                    return;
                }
                tmp=tmp->left;
            }
            else{
                presum+=(tmp->sum+tmp->dup);
                if(!tmp->right){
                    tmp->right=new Node(num, 0);
                    ans[i]=presum;
                    return;
                }
                tmp=tmp->right;
            }
        }
    }
    
};
