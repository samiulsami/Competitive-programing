#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool notPrime[46]={0};
vector<int>numL,numR;
ll dp[11][46][46];

ll f(int i, int sumODD, int sumEVEN, int r, int l){
    if(i==-1){
        if(sumEVEN-sumODD<0)return 0;
        return !notPrime[sumEVEN-sumODD];
    }
    ll &ret = dp[i][sumODD][sumEVEN];
    if(ret!=-1 && !r && !l)return ret;
    int upper_lim = r?numR[i]:9;
    int lower_lim = l?numL[i]:0;
    ll ans=0;
    for(int j=lower_lim; j<=upper_lim; j++){
        if(i%2)ans+=f(i-1, sumODD, sumEVEN+j, j==numR[i]?r:0, j==numL[i]?l:0);
        else   ans+=f(i-1, sumODD+j, sumEVEN, j==numR[i]?r:0, j==numL[i]?l:0);
    }
    if(!r && !l)ret=ans;
    return ans;
}

ll solve(int a,int b){
    numL.clear();
    numR.clear();
    while(a>0){
        numL.push_back(a%10);
        a/=10;
    }
    while(b>0){
        numR.push_back(b%10);
        b/=10;
    }
    while(numL.size()<numR.size())numL.push_back(0);
    return f(numL.size()-1, 0, 0, 1, 1);
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
        cout<<solve(a,b)<<endl;
    }
return 0;
}
