#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pll;
#define xx first
#define yy second
const ll MOD=998244353;

vector<int>num;
ll powers[20];
int k;
pll dp[20][(1<<10)+1];

pll f(int i, int used, int lim){
    if(i==-1)return {0,1};
    pll &ret = dp[i][used];
    if(ret.xx!=-1 && !lim)return ret;
    int upper_lim = lim?num[i]:9;
    pll ans={0,0},tmp={0,0};
    for(int j=0; j<=upper_lim; j++){
        if(__builtin_popcount(used)==k && !bool(used&(1<<j)))continue;
        if(used==0 && j==0)tmp=f(i-1,used,j==num[i]?lim:0);
        else tmp=f(i-1,used|(1<<j),j==num[i]?lim:0);
        ans.xx=(ans.xx+tmp.xx%MOD)%MOD;
        ans.xx=(ans.xx+((tmp.yy)*powers[i]*j)%MOD)%MOD;
        ans.yy=(ans.yy+tmp.yy%MOD)%MOD;
    }
    if(!lim)ret=ans;
    return ans;
}

ll solve(ll x){
    num.clear();
    while(x>0){
        num.push_back(x%10);
        x/=10;
    }
    return f(num.size()-1, 0, 1).xx%MOD;
}

int main(){
    ll a,b,ans;
    for(int i=0; i<20; i++)
        for(int j=0; j<=(1<<10); j++)dp[i][j].xx=-1,dp[i][j].yy=0;
    powers[0]=1;
    for(int i=1; i<=19; i++)powers[i]=((powers[i-1])*10)%MOD;

    cin>>a>>b>>k;
    ans=solve(b)-solve(a-1);
    cout<<(ans+MOD)%MOD<<endl;
return 0;
}
