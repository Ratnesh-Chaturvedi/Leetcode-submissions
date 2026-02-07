class Solution {
public:
    int minimumDeletions(string s) {
        int n=s.size();
        if(n==1)return 0;
        int cntb=0,cnta=0;
        int ans=n;
        bool lastb=false,lasta=false;
        int ca=0,cb=0;
        for(int i=0;i<n;i++){
            if(s[i]=='a')ca++;
            else cb++;
        }
        for(int i=0;i<n;i++){
            ans=min(ans,(ca-cnta)+cntb);
            if(s[i]=='a')cnta++;
            else cntb++;
           
        }
         ans=min(ans,(ca-cnta)+cntb);
        return ans;
        

    }
};

// Approach 2->
   int minimumDeletions(string s) {
        int b=0,del=0;
        for(char c:s){
            if(c=='b')b++;
            else {
                if(b>0){
                    del++;
                    b--;
                }
            }
        }
        return del;
    }

    //Approach-> we can also do this using stack 