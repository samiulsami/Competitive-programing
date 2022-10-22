#include<bits/stdc++.h>
using namespace std;
///The 16th Heilongjiang Provincial Collegiate Programming Contest - D - 'Doin Time
typedef long long ll;
typedef pair<ll, ll> pll;
pll dp[302][302];
bool vis[302][302]={0};
ll arr[302];

const int MOD = 1000003;
int n;

pll f(int l, int r){
    if(l>r)return pll(0,0);
    if(l==r)return pll(arr[l],0);
    if(vis[l][r])return dp[l][r];
    vis[l][r]=1;
    pll &ret = dp[l][r];
    ret = pll(0,0);
	
    for(int i=l; i<r; i++){
        pll lft = f(l,i);
        pll rgt = f(i+1,r);
        ll val = (lft.first*rgt.first)%MOD;
        ll add = (lft.first-rgt.first);
        add = add*add;
        add += lft.second + rgt.second;
        if(add>ret.second)ret=pll(val,add);
    }
    return ret;
}

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++)scanf("%lld",&arr[i]);

    printf("%lld",f(0,n-1).second);

return 0;
}
