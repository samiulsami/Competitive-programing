#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2002;
short dp1[N][N];
ll dp[N][N];
string s;

short isPal(int l, int r){
    if(l>=r)return 1;
    short &ret = dp1[l][r];
    if(~ret)return ret;
    if(s[l]==s[r])return ret=isPal(l+1,r-1);
    return ret=0;
}

ll f(int l, int r){
    if(l>r)return 0;
    if(l==r)return 1;
    ll &ret = dp[l][r];
    if(~ret)return ret;
    ret = (ll)isPal(l,r) + f(l+1,r) + f(l,r-1) - f(l+1,r-1);
    return ret;
}

int main(){
    memset(dp,-1,sizeof(dp));
    memset(dp1,-1,sizeof(dp1));

    cin>>s;
    ll ans=0;
    int n=s.length();
    for(int i=1; i<=n; i++){
        for(int j=0; j+i-1<n; j++){
            if(isPal(j,j+i-1))ans+=f(j+i,n-1);
        }
    }
    cout<<ans<<endl;

return 0;
}
