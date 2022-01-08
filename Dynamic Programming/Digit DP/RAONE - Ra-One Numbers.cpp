#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[9][82][82][2][2];
int vis[9][82][82][2][2]={0};
int color=1;
string a,b;

ll solve(int i=0, int sumODD=0, int sumEVEN=0, int x=1, int y=1){
    if(i==a.length())return (sumEVEN-sumODD)==1;
    ll &ret=dp[i][sumODD][sumEVEN][x][y];
    if(vis[i][sumODD][sumEVEN][x][y]==color)return ret;
    vis[i][sumODD][sumEVEN][x][y]=color;
    int numL = a[i]-48;
    int numR = b[i]-48;
    int lower_lim = x?numL:0;
    int upper_lim = y?numR:9;
    ret=0;
    for(int j=lower_lim; j<=upper_lim; j++){
        if((a.length()-i-1)%2==0)ret+=solve(i+1, sumODD+j, sumEVEN, numL==j?x:0, numR==j?y:0);
        else ret+=solve(i+1, sumODD, sumEVEN+j, numL==j?x:0, numR==j?y:0);
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>a>>b;
        while(a.size()<b.size())a="0"+a;
        cout<<solve()<<endl;
        color++;
    }
return 0;
}
