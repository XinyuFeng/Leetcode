class Solution {
public:
vector<vector<int>> dirs{{0,1}, {0,-1}, {1,0}, {-1,0}};

    string findShortestWay(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
        auto t=make_pair(0, "");
         vector<vector<pair<int, string>>> cache(maze.size(), vector<pair<int, string>>(maze[0].size(), t));
        cache[start[0]][start[1]].first=1;
        cache[start[0]][start[1]].second="X";
        //dfs(start[0], start[1], destination, maze, cache);
        int m=maze.size(), n=maze[0].size();
        queue<int> T;
        T.push(start[0]*n+start[1]);
        while(T.size()){
            int node=T.front();
            T.pop();
            int row= node/n, col=node%n;
            for(auto p : dirs){
                int i=row, j=col;
                string cur=cache[row][col].second;
                int len=cache[row][col].first;
                char c;
                
                if(p[0]==0 and p[1]==1) c='r';
                if(p[0]==0 and p[1]==-1) c='l';
                if(p[0]==1 and p[1]==0) c='d';
                if(p[0]==-1 and p[1]==0) c='u';
                cur+=c;
                while(i+p[0]>=0 and i+p[0]<m and j+p[1]>=0 and j+p[1]<n and maze[i+p[0]][j+p[1]]==0){
                i+=p[0];
                j+=p[1];
                len++;
                if(i==dest[0] and j==dest[1] and (cache[i][j].first==0 or cache[i][j].first>len or (cache[i][j].first==len and cache[i][j].second>cur))){
                    cache[i][j].second=cur;
                    cache[i][j].first=len;
                }
                }
                
                if(cache[i][j].first and len>cache[i][j].first) continue;
                if(len==cache[i][j].first and cur>=cache[i][j].second) continue;
                cache[i][j].second=cur;
                cache[i][j].first=len;
                T.push(i*n+j);
            }
            
        }
        return cache[dest[0]][dest[1]].first==0? "impossible" : cache[dest[0]][dest[1]].second.substr(1);
    }
};
