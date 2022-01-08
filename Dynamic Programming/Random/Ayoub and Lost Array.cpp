#include<bits/stdc++.h>
using namespace std;

long long arr[3];
long long dp[200005][3];
long long n,l,r;

const long long MOD = 1e9 + 7;

long long solve(int i=0, int val=0){
    if(i==n){
        if(val==0)return 1;
        return 0;
    }
    long long &ret = dp[i][val];
    if(ret!=-1)return ret;
    long long tmp=0;
    for(int j=0; j<=2; j++)tmp+=(((solve(i+1,(j+val)%3))%MOD)*arr[j]),tmp%=MOD;
    return ret=tmp;
}

int main(){
    cin>>n>>l>>r;
    memset(dp,-1,sizeof(dp));
    arr[0]=r/3 - (l-1)/3;
    arr[2]=(r+1)/3 - (l)/3;
    arr[1]=(r+2)/3 - (l+1)/3;
    cout<<solve();
return 0;
}
