#include<bits/stdc++.h>
using namespace std;

long long dp[51][17][17][17];
const int MOD = 1000000007;

long long solve(int i, int t, int s, int n, int x, string &a){
    if(t>16 || s>16 || n>16)return 0;
    if(i==-1)return (t==s && s==n && t>0);
    long long &ret = dp[i][t][s][n];
    if(ret!=-1 && !x)return ret;
    int upper_lim = x?a[i]-48:9;
    long long ans=0;
    for(int j=0; j<=upper_lim; j++){
        ans+=solve(i-1,t+(j==3),s+(j==6),n+(j==9),j==a[i]-48?x:0,a);
        if(ans>=MOD)ans-=MOD;
    }
    if(!x)return ret=ans;
    return ans;
}

int main(){
    int t;
    string a,b;
    memset(dp,-1,sizeof(dp));
    long long ans;
    cin>>t;
    while(t--){
        cin>>a>>b;
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
        ans=solve(b.length()-1,0,0,0,1,b)-solve(a.length()-1,0,0,0,1,a);
        int x=0,y=0,z=0;
        for(int i=0; i<a.length(); i++){
            x+=(a[i]=='3');
            y+=(a[i]=='6');
            z+=(a[i]=='9');
        }
        if(x==y && y==z && x>0)ans++;
        cout<<(ans+MOD)%MOD<<endl;//solve(b) can be less than solve(a) due to MOD
    }
return 0;
}
