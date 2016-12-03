My Solution:

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> ans;
        if(intervals.empty()){
            ans.push_back(newInterval);
            return ans;
        }
        
        int len=intervals.size();
        bool pushed=false;
        Interval tmp(INT_MAX, INT_MIN);
        int j=0;
        for(int i=0; i<len; ++i){
            if(intervals[i].end<newInterval.start){//push all intervals before newInterval to ans
                ans.push_back(intervals[i]);
                j=i;
            }
            else if(intervals[i].start>newInterval.end){//push tmp and all intervals after newInterval to ans
                if(tmp.start!=INT_MAX and pushed==false){
                    ans.push_back(tmp);
                    pushed=true;
                }
                ans.push_back(intervals[i]);
            }
            else{//expand tmp dynamically
                tmp.start=min(tmp.start, min(newInterval.start, intervals[i].start));
                tmp.end=max(tmp.end, max(newInterval.end, intervals[i].end));
            }
        }
        if(tmp.start==INT_MAX){ //tmp not calculate
            if(newInterval.end<intervals[0].start){ // newInterval should insert at the begin of ans
                ans.insert(ans.begin(), newInterval);
            }
            else if(newInterval.start>intervals[len-1].end){//push it to ans's back
                ans.push_back(newInterval);
            }
            else{
                ans.insert(ans.begin()+j+1, newInterval); //insert it in somewhere middle of ans
            }
        }
        else if(!pushed){//tmp has been calculated but not be pushed into ans
            ans.push_back(tmp);
        }
        return ans;
    
        
    }
};

Thoughts: we could use newInterval iteratively instead of setting a new interval, and the new line as below:
newInterval.start = min(newInterval.start, intervals[i].start);
newInterval.end = max(newInterval.end, intervals[i].end);
