/*Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W). You also have several balls in your hand.

Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place). Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

Examples:

Input: "WRRBBW", "RB"
Output: -1
Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW

Input: "WWRRBBWW", "WRBRW"
Output: 2
Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

Input:"G", "GGGGG"
Output: 2
Explanation: G -> G[G] -> GG[G] -> empty 

Input: "RBYYBBRRB", "YRBGB"
Output: 3
Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty */

class Solution {
public:
    map<pair<string, string>, int> f;
    int findMinStep(string board, string hand) {
        f.clear();
        return solve(board,hand);
    }
    int solve(string board, string hand){
        while(removeCon(board));
        if(board.empty()) return 0;
        if(hand.empty() or board.size()+hand.size()<3) return -1;
        auto it=f.find(make_pair(board, hand));
        if(it!=f.end()) return it->second;
        
        int best=-1;
        for(int i=0; i<hand.size(); ++i){
            for(int j=0; j<board.size(); ++j){
                if(board[j]==hand[i]){
                    string new_board=board;
                    string new_hand=hand;
                    
                    new_board.insert(new_board.begin()+j, hand[i]);
                    new_hand.erase(i, 1);
                    int ans=solve(new_board, new_hand);
                    if(ans>-1){
                        if(best==-1) best=ans+1;
                        else best=min(best, ans+1);
                    }
                }
            }
        }
        f[make_pair(board, hand)]=best;
        return best;
    }
    bool removeCon(string& str){
        int con=1;
        for(int i=1; i<str.size(); ++i){
            if(str[i]==str[i-1]) con++;
            else{
                if(con>=3){
                    str.erase(i-con, con);
                    return true;
                }
                con=1;
            }
        }
        if(con>=3){
            str.erase(str.size()-con, con);
            return true;
        }
        return false;
    }
};
