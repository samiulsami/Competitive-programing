#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string a,b;
ll dp[16][9*16+1][2][2][2];

ll solve(int i=0, int sum=0, int l=1, int r=1, int nz=1){
    if(i==a.length())return sum;
    ll &ret = dp[i][sum][l][r][nz];
    if(ret!=-1)return ret;
    int numL=a[i]-'0',numR=b[i]-'0';
    int lower_lim = l?numL:0;
    int upper_lim = r?numR:9;
    ret=0;
    for(int j=lower_lim; j<=upper_lim; j++){
        nz|=(j>0);
        ret+=solve(i+1, nz*(sum+j), j==numL?l:0, j==numR?r:0, nz);
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>a>>b;
        memset(dp,-1,sizeof(dp));
        while(a.size()<b.size())a="0"+a;
        cout<<solve()<<endl;
    }
return 0;
}
