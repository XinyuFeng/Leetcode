/*
Define S = [s,n] as the string S which consists of n connected strings s. For example, ["abc", 3] ="abcabcabc".

On the other hand, we define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1. For example, “abc” can be obtained from “abdbec” based on our definition, but it can not be obtained from “acbbe”.

You are given two non-empty strings s1 and s2 (each at most 100 characters long) and two integers 0 ≤ n1 ≤ 106 and 1 ≤ n2 ≤ 106. Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2]. Find the maximum integer M such that [S2,M] can be obtained from S1.

Example:

Input:
s1="acb", n1=4
s2="ab", n2=2

Return:
2
*/
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        vector<int> rapport(102, -1);
        vector<int> rest(102, -1);
        int b=-1; int posrest=0; int rap=0;
        int last=-1;
        rapport[0]=rest[0]=0;
        for(int i=1; i<=s2.size()+1; ++i){
            int j;
            for(j=0; j<s1.size(); ++j){
                if(s2[posrest]==s1[j]){
                    posrest++;
                    if(posrest==s2.size()){
                        rap++;
                        posrest=0;
                    }
                }
            }
            for(int k=0; k<i; ++k){
                if(posrest==rest[k]){b=k; last=i; break;}
            }
            rapport[i]=rap;
            rest[i]=posrest;
            if(b>=0) break;
        }
        int interval=last-b;
        if(b>=n1) return rapport[n1]/n2;
        return ((n1-b)/interval*(rapport[last]-rapport[b])+rapport[(n1-b)%interval+b])/n2;
    }
};
