class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if(matrix.empty() or matrix[0].empty()) return 0;
        auto comp=[](pair<int, pair<int, int>>& p1, pair<int, pair<int, int>>& p2) {
            return p1.first>p2.first;
        };
        
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(comp)> T(comp);//the use of function pointer
        int r=matrix.size();
        int c=matrix[0].size();
        for(int i=0; i<r; ++i){
            T.push(make_pair(matrix[i][0], make_pair(i, 0)));
        }
        int ans=0;
        while(k--){
            auto tmp=T.top();
            T.pop();
            int val=tmp.first;
            int i=tmp.second.first;
            int j=tmp.second.second;
            ans=val;
            if(j<c-1)
                T.push(make_pair(matrix[i][j+1], make_pair(i, j+1)));
        }
        return ans;
    }
};
