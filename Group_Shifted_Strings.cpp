/*Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"], 
A solution is:

[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
*/
///////////////////////////////////////////////////////////
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> T;
        for(auto s : strings){
            T[helper(s)].emplace_back(s);
        }
        vector<vector<string>> ans;
        for(auto m : T){
            auto tmp=m.second;
            sort(tmp.begin(), tmp.end());
            ans.emplace_back(tmp);
        }
        return ans;
    }
private:
    string helper(string& s){
        string t;
        int l=s.size();
        for(int i=1; i<l; ++i){
            int diff=s[i]-s[i-1];
            if(diff<0) diff+=26;
            t+='a'+diff;
        }
        return t;
    }
};
