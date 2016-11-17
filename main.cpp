//
//  main.cpp
//  sudoku
//
//  Created by Xinyu Feng on 11/16/16.
//  Copyright (c) 2016 Xinyu Feng. All rights reserved.
//

#include <iostream>
#include <array>
#include <vector>
using namespace std;

class Solution{
    struct cell{
        uint8_t value;
        uint8_t numPossibilities;//the number of possible value for this cell
        bitset<10> constraints;//if contraints[v] is 1 then value can't be v
        cell():value(0), numPossibilities(9), constraints(){}
    };
    array<array<cell,9>,9> cells;
    
    bool updateConstraints(int i, int j, int excludedValue){
        cell &c=cells[i][j];
        if(c.constraints[excludedValue])
            return true;
        if(c.value == excludedValue)
            return false;
        c.constraints.set(excludedValue);
        if(--c.numPossibilities>1)
            return true;
        for(int v=1; v<=9; ++v){// only one possibility
            if(!c.constraints[v])
                return set(i, j, v);
        }
        return false;
    }
    
    bool set(int i, int j, int v){//set the value of cell[i][j], and spread constraint to i row, j col, and 3x3 squares
        cell& c=cells[i][j];
        if(c.value==v)
            return true;
        if(c.constraints[v])
            return false;
        c.constraints=bitset<10>(0x3FE);
        c.constraints.reset(v);//it can't have constraints on its own value
        c.numPossibilities=1;// since it has a value, it has only one possibility
        c.value=v;
        
        for(int k=0; k<9; ++k){
            if( i!=k and !updateConstraints(k, j, v))//spread the whole j col
                return false;
            if(j!=k and !updateConstraints(i, k, v))//spread the whole i row
                return false;
            int ix=(i/3)*3+k/3;
            int jx=(j/3)*3+k%3;
            if(ix!=i and jx != j and !updateConstraints(ix, jx, v))// spread 3x3 square
                return false;
            
        }
        return true;
    }
    
    vector<pair<int, int>> bt;//empty cells
    
    bool findValuesForEmptyCells(){
        bt.clear();
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if (!cells[i][j].value) {
                    bt.push_back(make_pair(i, j));//get all empty cells
                }
            }
        }
        //sort according the number of possibilities
        sort(bt.begin(), bt.end(), [this](const pair<int, int>&a, const pair<int, int>&b){
            return cells[a.first][a.second].numPossibilities < cells[b.first][b.second].numPossibilities;
        });
        return backtrack(0);//backtrack from the first empty cell
    }
    bool backtrack(int k){
        if(k>=bt.size())//finished
            return true;
        int i=bt[k].first;
        int j=bt[k].second;
        
        if(cells[i][j].value)
            return backtrack(k+1);
        auto constraints = cells[i][j].constraints;
        
        array<array<cell, 9>, 9> snapshot(cells);//make a copy of the original board
        for(int v=1; v<=9; ++v){
            if(!constraints[v]){ //try all possible values for cells[i][j]
                if(set(i, j, v)){
                    if(backtrack(k+1))
                        return true;
                }
                cells=snapshot;
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<string> &board){
        cells = array<array<cell, 9>, 9>();
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(board[i][j] !='.' and !set(i, j, board[i][j]-'0'))
                    return;
            }
        }
        if(!findValuesForEmptyCells())
            return;
        
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(cells[i][j].value)
                    board[i][j] = cells[i][j].value+'0';
            }
        }
    }
};



int main(int argc, const char * argv[]) {
    // insert code here...
    vector<string> test(9, "");
    test[0]="..9748...";
    test[1]="7........";
    test[2]=".2.1.9...";
    test[3]="..7...24.";
    test[4]=".64.1.59.";
    test[5]=".98...3..";
    test[6]="...8.3.2.";
    test[7]="........6";
    test[8]="...2759..";
    Solution S;
    S.solveSudoku(test);
    for(int i=0; i<9; ++i){
        cout<<test[i]<<endl;
    }
    std::cout << "Hello, World!\n";
    
    return 0;
}
