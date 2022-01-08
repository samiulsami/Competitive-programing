#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[20][(1<<10)+1][(1<<10)+1];
vector<int>num;

ll f(int i, int taken, int oddEven, int k){
    if(i==-1){
        for(int it=0; it<=9; it++){
            if(!bool(taken&(1<<it)))continue;
            if(bool(it%2) == bool(oddEven&(1<<it)))return 0;
        }
        return 1;
    }
    ll &ret = dp[i][taken][oddEven];
    if(ret!=-1 && !k)return ret;
    int lim = k?num[i]:9;
    ll ans=0;
    for(int j=0; j<=lim; j++){
        int newTaken=taken;
        int newOddEven=oddEven;
        if(taken>0 || j>0){
            newTaken|=(1<<j);
            newOddEven^=(1<<j);
        }
        ans+=f(i-1, newTaken, newOddEven, j==num[i]?k:0);
    }
    if(!k)ret=ans;
    return ans;
}

ll solve(ll x){
    num.clear();
    while(x>0){
        num.push_back(x%10);
        x/=10;
    }
    return f(num.size()-1, 0, 0, 1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    ll t,a,b;
    cin>>t;
    while(t--){
        cin>>a>>b;
        cout<<solve(b)-solve(a-1)<<endl;
    }
return 0;
}
