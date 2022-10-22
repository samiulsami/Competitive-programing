#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int>num[2];
ll dp[10][91][2][2][2]; //index, sum, less than limit?, greater than limit?, non-zero digit found yet?

ll solve(int i=0, int sum=0, int l=1, int r=1, int nz=0){
    if(i==num[1].size())return sum;
    ll &ret = dp[i][sum][l][r][nz];
    if(ret!=-1)return ret;
    int lower_limit = l?num[0][i]:0;
    int upper_limit = r?num[1][i]:9;
    ret=0;
    for(int j=lower_limit; j<=upper_limit; j++){
        nz|=(j>0);
        ret+=solve(i+1, nz*(sum+j), num[0][i]==j?l:0, num[1][i]==j?r:0, nz);
    }
    return ret;
}


void init(int n, bool k){
    num[k].clear();
    while(n){
        num[k].push_back(n%10);
        n/=10;
    }
}

int main(){
    int l,r;
    while(cin>>l>>r){
        if(l==-1 && r==-1)break;
        if(r<l)swap(l,r);
        init(l,0);
        init(r,1);
        while(num[1].size()>num[0].size())num[0].push_back(0);
        reverse(num[1].begin(),num[1].end());
        reverse(num[0].begin(),num[0].end());
        memset(dp,-1,sizeof(dp));
        cout<<solve()<<endl;
    }
return 0;
}
