//the reason for this sorting: if all width is equal, in order to make lower_bound() work, we need to make the height in decreasing order
class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        if(envelopes.empty()) return 0;
        
        auto comp=[](pair<int, int>& p1, pair<int, int>& p2){
            if(p1.first==p2.first) return p1.second>p2.second;
            return p1.first<p2.first;
        };
        
        sort(envelopes.begin(), envelopes.end(), comp);
        int len=envelopes.size();
        vector<int> dp;//dp[i]: the smallest tail value in a sequence with length i.
      
        for(int i=0; i<len; ++i){
            auto it =lower_bound(dp.begin(), dp.end(), envelopes[i].second);//find the first >= value in dp, and replace it
            if(it==dp.end()) dp.emplace_back(envelopes[i].second);
            else *it=envelopes[i].second;
        }
        return dp.size();
       
        
    }
};
