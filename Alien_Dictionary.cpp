class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;
        
        for(auto word:words){
            for(auto ch : word)
                indegree[ch]=0;
        }
        for(int i=1; i<words.size(); ++i){
            int idx=0;
            int len=min(words[i-1].size(), words[i].size());
            while(idx<len and words[i-1][idx]==words[i][idx]){
                idx++;
            } 
            if(idx==len and words[i-1].size()>len) return "";
            if(idx==len) continue;
            if(graph[words[i-1][idx]].count(words[i][idx])==0)
                indegree[words[i][idx]]++;
            graph[words[i-1][idx]].insert(words[i][idx]);
            
        }
        
        string ans="";
        queue<char> T;
        for(auto q : indegree){
            if(!q.second) T.push(q.first);
        }
        while(T.size()){
            char node=T.front(); T.pop();
            ans+=node;
            for(auto t : graph[node]){
                indegree[t]--;
                if(!indegree[t]) T.push(t);
            }
        }
        return ans.size()==indegree.size()? ans : "";
        
    }
};
