class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>>coords;
        for(auto building : buildings){ //put all"critic point" into coords;
            coords.push_back(make_pair(building[0], -building[2])); 
            coords.push_back(make_pair(building[1], building[2]));
        }
        sort(coords.begin(), coords.end());//sort it based on x, if x is the same, then sort it based on y(this is the reason why it <0
        multiset<int> heights={0};
        vector<pair<int, int>>corners;
        int x=-1;
        int y=0;
        for(auto p : coords){
            if(p.second<0){
                heights.insert(-p.second);
            }
            else{
                heights.erase(heights.find(p.second));
            }
            
            if(y!=*heights.rbegin()){
                corners.emplace_back(p.first, y=*heights.rbegin());
            }
            
        }
        
        return corners;
    }
};
