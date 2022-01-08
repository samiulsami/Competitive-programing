#include<bits/stdc++.h>
using namespace std;

int Set(int n, int pos){return n|(1<<pos);}
int reset(int n, int pos){return n&~(1<<pos);}
int change(int n, int pos){return n^(1<<pos);}
bool check(int n, int pos){return (bool)(n&(1<<pos));}

int dp[(1<<15)+2];

int solve(int mask){
    int &ret=dp[mask];
    if(~ret)return ret;
    int counter=0;
    for(int i=12; i>=1; i--)counter+=(int)check(mask,i);
    ret=counter;
    for(int i=12; i>2; i--){
        if((check(mask,i)+check(mask,i-1)+check(mask,i-2))==2 && check(mask,i-1)){
            int newmask=mask;
            newmask=newmask^(1<<i);
            newmask=newmask^(1<<(i-1));
            newmask=newmask^(1<<(i-2));
            ret=min(ret, min(solve(newmask),counter-1));
        }
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    memset(dp,-1,sizeof(dp));
    int t;
    char c;
    cin>>t;
    while(t--){
        int n=0;
        for(int i=12; i>0; i--){
            cin>>c;
            if(c=='o')n=Set(n,i);
        }
        cout<<solve(n)<<endl;
    }
return 0;
}
