//Way 1
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        unordered_map<string, int> mp;
        string corners[4];
        for(auto v: rectangles){
            for(int i=0; i<4; ++i){
                corners[i]=to_string(v[i/2*2]) + " " + to_string(v[(i%2)*2+1]);
                if(mp[corners[i]] & (1<<i)) return false;
                else
                    mp[corners[i]] |= (1<<i);
            }
        }
        
        int corner=0;
        for(auto i=mp.begin(); i!=mp.end(); ++i){
            int val=i->second;
            if(!(val&(val-1)) and (++corner>4)) return false;
            if((val&(val-1)) and !(val==3 or val==12 or val==10 or val==5 or val==15)) return false;
        }
        
        return true;
    }
};

//way 2
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        
        if(rectangles.empty() or rectangles[0].empty()) return false;
        int x1=INT_MAX;
        int y1=INT_MAX;
        int x2=INT_MIN;
        int y2=INT_MIN;
        
        set<string> T;
        int area=0;
        for(auto rect : rectangles){
            x1=min(x1, rect[0]);
            y1=min(y1, rect[1]);
            x2=max(x2, rect[2]);
            y2=max(y2, rect[3]);
            
            area+=(rect[2]-rect[0])*(rect[3]-rect[1]);
            
            string s1=to_string(rect[0])+" "+to_string(rect[1]);
            string s2=to_string(rect[0])+" "+to_string(rect[3]);
            string s3=to_string(rect[2])+" "+to_string(rect[1]);
            string s4=to_string(rect[2])+" "+to_string(rect[3]);
            
            if(!T.emplace(s1).second) T.erase(s1);
            if(!T.emplace(s2).second) T.erase(s2);
            if(!T.emplace(s3).second) T.erase(s3);
            if(!T.emplace(s4).second) T.erase(s4);
        }
        string s1=to_string(x1)+" "+to_string(y1);
        string s2=to_string(x1)+" "+to_string(y2);
        string s3=to_string(x2)+" "+to_string(y1);
        string s4=to_string(x2)+" "+to_string(y2);
        if(!T.count(s1) or !T.count(s2) or !T.count(s3) or !T.count(s4) or T.size()!=4) return false;
        
        return area==(x2-x1)*(y2-y1);
    }
};
