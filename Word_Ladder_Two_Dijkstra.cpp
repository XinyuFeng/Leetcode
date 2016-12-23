class Solution {
    unordered_map<string, vector<string>> Map;
    vector<vector<string>> results;
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &dict) {
       if(dict.empty()) return results;
       
       int m=INT_MAX;
       queue<string> T;
       T.push(beginWord);
       unordered_map<string, int> ladder;
       for(string s : dict){
           ladder[s]=INT_MAX;
       }
       ladder[beginWord]=0;
       
       dict.insert(endWord);
       //BFS: Dijisktra
       while(T.size()){
           string word=T.front();
           T.pop();
           int step=ladder[word]+1;//'step' indicates how many steps are needed to travel to one word. 
           if(step>m) break;
           for(int i=0; i<word.size(); ++i){
               for(char ch='a'; ch<='z'; ++ch){
                   string tmp=word;
                   tmp[i]=ch;
                   if(tmp==word) continue;
                   if(ladder.find(tmp)!=ladder.end()){
                       if(step>ladder[tmp]) continue;//Check if it is the shortest path to one word.
                       else if(step<ladder[tmp]){
                           T.push(tmp);
                           ladder[tmp]=step;
                       }
                       else;
                       Map[tmp].emplace_back(word);//Build adjacent Graph
                       if(tmp==endWord) m=step;
                   }
               }
           }
       }
       
       vector<string>result;
       dfs(endWord, beginWord, result);
       return results;
    }
    
    void dfs(string word, string start, vector<string>& result){
        if(word==start){
            result.insert(result.begin(), start);
            results.emplace_back(result);
            result.erase(result.begin());
            return;
        }
        
        result.insert(result.begin(), word);
        if(Map.find(word)!=Map.end()){
            for(auto s : Map[word]){
                dfs(s, start, result);
            }
        }
        result.erase(result.begin());
        
    }
};
