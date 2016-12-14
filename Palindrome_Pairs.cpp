//First way, using trie
//https://discuss.leetcode.com/topic/39585/o-n-k-2-java-solution-with-trie-structure-n-total-number-of-words-k-average-length-of-each-word

class Solution {
public:
    struct TrieNode{
        TrieNode* next[26];
        int index;
        vector<int> l;
        
        TrieNode(){
            memset(next, NULL, sizeof(next));
            index=-1;
        }
    };
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> ans;
        if(words.empty()) return ans;
        
        TrieNode* root = new TrieNode();
        for(int i=0; i<words.size(); ++i) addWord(root, words[i], i);
        for(int i=0; i<words.size(); ++i) search(words, i, root, ans);
        return ans;
    }
    
    void addWord(TrieNode* root, string word, int idx){
        for(int i=word.length()-1; i>=0; --i){
            int j=word[i]-'a';
            if(root->next[j]==NULL) root->next[j]=new TrieNode();
            if(isP(word, 0, i)) root->l.push_back(idx);
            root=root->next[j];
        }
        root->l.push_back(idx);
        root->index=idx;
    }
    
    void search(vector<string>& words, int i, TrieNode* root, vector<vector<int>>& ans){
        for(int j=0; j<words[i].length(); ++j){
            if(root->index>=0 and root->index!=i and isP(words[i], j, words[i].length()-1)){
                ans.push_back({i, root->index});
            }
            root=root->next[words[i][j]-'a'];
            if(root==NULL) return;
        }
        
        for(int j : root->l){
            if(i==j) continue;
            ans.push_back({i, j});
        }
    }
    
    bool isP(string word, int i, int j){
        while(i<j){
            if(word[i++]!=word[j--]) return false;
        }
        return true;
    }
};

//Second Way, hashmap
class Solution {
public:

    bool isP(string t){
        if(t.empty()) return true;
        int len=t.size();
        for(int i=0; i<len/2; ++i){
            if(t[i]!=t[len-i-1])
                return false;
        }
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        
        vector<vector<int>> ans;
        if(words.empty()) return ans;
        int len=words.size();
        unordered_map<string, int> T;
        for(int i=0; i<len; ++i){
            string tmp=words[i];
            reverse(tmp.begin(), tmp.end());
            T[tmp]=i;
        }
        
        if(T.find("")!=T.end()){
            for(int i=0; i<len; ++i){
                if(words[i]=="") continue;
                if(isP(words[i]))
                    ans.push_back({T[""], i});
            }
        }
        
        for(int i=0; i<len; ++i){
            for(int j=0; j<words[i].size(); ++j){
                string left=words[i].substr(0,j);
                string right=words[i].substr(j);
                
                if(T.find(left)!=T.end() and isP(right) and T[left]!=i){
                    ans.push_back({i, T[left]});
                }
                
                if(T.find(right)!=T.end() and isP(left) and T[right]!=i){
                    ans.push_back({T[right], i});
                }
            }
        }
        return ans;
    }
}
