#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll m,d;
ll dp[2005][2005][2][2];
string a,b;
int len;
const ll mod = 1e9+7;

ll f(int i, int rem, int x, int y){
    if(i==len)return (rem==0);
    ll &ret=dp[i][rem][x][y];
    if(~ret)return ret;
    int lower_lim = x?a[i]-48:0;
    int upper_lim = y?b[i]-48:9;
    ret=0;
    if((lower_lim>d || upper_lim<d) && i%2)return 0;
    if(i%2)return ret=f(i+1, ((rem*10)+d)%m, (a[i]-48)==d?x:0, (b[i]-48)==d?y:0)%mod;
    for(int j=lower_lim; j<=upper_lim; j++){
        if(j==d)continue;
        ret+=f(i+1, ((rem*10)+j)%m, (a[i]-48==j)?x:0, (b[i]-48)==j?y:0)%mod;
        ret%=mod;
    }
    return ret%mod;
}

int main(){
    cin>>m>>d>>a>>b;
    len=a.length();
    memset(dp,-1,sizeof(dp));
    cout<<f(0,0,1,1)%mod;
return 0;
}
