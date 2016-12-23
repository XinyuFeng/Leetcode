//We start with trimming.

//If we see [0-9] we reset the number flags.
//We can only see . if we didn't see e or ..
//We can only see e if we didn't see e but we did see a number. We reset numberAfterE flag.
//We can only see + and - in the beginning and after an e
//any other character break the validation.
//At the and it is only valid if there was at least 1 number and if we did see an e then a number after it as well.

//So basically the number should match this regular expression:

//[-+]?(([0-9]+(.[0-9]*)?)|.[0-9]+)(e[-+]?[0-9]+)?

class Solution {
public:
    bool isNumber(string s) {
        bool pointSeen=false;
        bool eSeen=false;
        bool numberSeen=false;
        bool numberAfterE=true;
        int i=0;
        while(s[i++]==' ');//trim " "
        i--;
        int init=i;//save initial position
        int j=s.size()-1;
        while(s[j--]==' ');//trim " "
        j++;
        for(; i<=j; ++i){
            if(s[i]>='0' and s[i]<='9'){
                numberSeen=true;
                numberAfterE=true;
            }
            else if(s[i]=='.'){
                if(eSeen or pointSeen) return false;
                pointSeen=true;
                
            }
            else if(s[i]=='e'){
                if(eSeen or !numberSeen) return false;
                numberAfterE=false;
                eSeen=true;
            }
            else if(s[i]=='-' or s[i]=='+'){
                if(i!=init and s[i-1]!='e') return false;
            }
            else return false;
        }
        
        return numberSeen and numberAfterE;
    }
};
