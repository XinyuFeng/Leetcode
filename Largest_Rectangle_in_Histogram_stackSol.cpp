class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        if(heights.size()==1) return heights[0];
        
        stack<int> S;
        int len=heights.size();
        int ans=0;
        for(int i=0; i<=len; ++i){
            int h=i==len? 0:heights[i];//the final element should be 0 to pop out all those remaining elements in the stack
            
            if(S.empty() or h>=heights[S.top()])//push idx into stack iff its empty or h greater than the top elem of the stack
                S.push(i);
            else{
                int tp=S.top();
                S.pop();
                ans=max(ans, heights[tp]*(S.empty()? i:i-1-S.top()));//calculate the area between i-1 to the idx on top of stack
                i--;                                                 // tp should be the minimum height in this area
            }
        }
        
        return ans;
        
        
    }
};
