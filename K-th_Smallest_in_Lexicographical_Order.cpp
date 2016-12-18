class Solution {
public:
    int calSteps(long n, long n1, long n2){
        int steps=0;
        while(n1<=n){
            steps+=(min(n2, n+1)-n1);
            n1*=10;
            n2*=10;
        }
        return steps;
    }
    
    int findKthNumber(int n, int k) {
        int cur=1;
        k--;
        while(k){
            int steps=calSteps(n, cur, cur+1);
            if(steps<=k){
                cur+=1;
                k-=steps;
                
            }
            else{
                cur*=10;
                k--;
            }
        }
        return cur;
        
    }
    
};
