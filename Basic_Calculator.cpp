class Solution {
public:
    int calculate(string s) {
        int result=0; 
        int num=0, sign=1; 
        stack<int> nums, ops; 
        
        for(int i=0; i<s.size(); ++i){
            char c=s[i];
            if(c>='0' && c<='9'){
                num=10*num + c-'0'; /// For case: "23" 
            }else if(c=='+'){
                result+=num*sign; /// everytime meets an operator, sum up previous number
                num=0;
                sign=1;    /// sign is the sign of next number
            }else if(c=='-'){
                result+=num*sign; /// everytime meets an operator, sum up previous number
                num=0; 
                sign=-1; 
            }else if(c=='('){
                nums.push(result); /// ...(1+3+(..xx..)+...)... before go into cur (..xx..), record the forefront result (in this case it is 1+3 ) into nums array    
                ops.push(sign);  // record cur (..xx..) sign
                result=0;  // result is to record the total value in the cur (..xx..)
                sign=1;
            }else if(c==')' && ops.size()){ 
                result+=num*sign; /// For case: 1-(5)
                num=0;
                
                result = result*ops.top() + nums.top();  // ...(1+3+(..xx..)+...)... sum up cur (..xx..)  and the forefront result (in this case it is 1+3 )
                nums.pop();
                ops.pop();
            }
        }
        result+=num*sign; /// For the last one operation. consider the case:  1+2+3 
        return result; 
    }
};

//Second Way
/*remaining   sign stack(T)    total
3-(2+(9-4))   [1, 1]            0
 -(2+(9-4))   [1]               3
  (2+(9-4))   [1, -1]           3
   2+(9-4))   [1, -1, -1]       3
    +(9-4))   [1, -1]           1
     (9-4))   [1, -1, -1]       1
      9-4))   [1, -1, -1, -1]   1
       -4))   [1, -1, -1]      -8
        4))   [1, -1, -1, 1]   -8
         ))   [1, -1, -1]      -4
          )   [1, -1]          -4
              [1]              -4
              */
class Solution {
public:
    int calculate(string s) {
        
        if(s.empty())return 0;
        int total=0;
        int len=s.size();
        stack<int> T;
        T.push(1);
        T.push(1);
        for(int i=0; i<len; ++i){
            if(s[i]>='0' and s[i]<='9'){
                int tmp=0;
                while(s[i]>='0' and s[i]<='9'){
                    tmp=tmp*10+s[i]-'0';
                    i++;
                }
                total+=(tmp*T.top());
                i--;
                T.pop();
            }
            else if(s[i]==')')
                T.pop();
            else if(s[i]!=' '){
                T.push(T.top()*(s[i]=='-'? -1 : 1));
            }
        }
        return total;
        
    }
};
