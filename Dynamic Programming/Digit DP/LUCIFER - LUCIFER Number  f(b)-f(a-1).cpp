#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool notPrime[46]={0};
vector<int>num;
ll dp[11][46][46];

ll f(int i, int sumODD, int sumEVEN, int k){
    if(i==-1){
        if(sumEVEN-sumODD<0)return 0;
        return !notPrime[sumEVEN-sumODD];
    }
    ll &ret = dp[i][sumODD][sumEVEN];
    if(ret!=-1 && !k)return ret;
    int upper_lim = k?num[i]:9;
    ll ans=0;
    for(int j=0; j<=upper_lim; j++){
        if(i%2)ans+=f(i-1,sumODD,sumEVEN+j,j==num[i]?k:0);
        else ans+=f(i-1,sumODD+j,sumEVEN,j==num[i]?k:0);
    }
    if(!k)ret=ans;
    return ans;
}

ll solve(int n){
    num.clear();
    while(n>0){
        num.push_back(n%10);
        n/=10;
    }
    return f(num.size()-1, 0, 0, 1);
}

int main(){
    int t,a,b;
    memset(dp,-1,sizeof(dp));
    notPrime[0]=notPrime[1]=1;
    for(int i=4; i<=45; i++)
        for(int j=2; j*j<=i; j++)
            if(i%j==0)notPrime[i]=1;
    cin>>t;
    while(t--){
        cin>>a>>b;
        cout<<solve(b)-solve(a-1)<<endl;
    }
return 0;
}
