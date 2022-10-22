#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[50][4];
ll n;
ll f(int i, int prev){
    if(i==n)return 1;
    ll &ret = dp[i][prev];
    if(ret!=-1)return ret;
    ret=0;
    if(prev!=0)ret+=f(i+1,0);
    if(prev!=1)ret+=f(i+1,1);
    if(prev!=2 && i>0 && i<n-1){
        if(prev==0)ret+=f(i+2,1);
        else ret+=f(i+2,0);
    }
    return ret;
}

int main(){
    memset(dp,-1,sizeof(dp));
    cin>>n;
    cout<<f(0,3);
return 0;
}
