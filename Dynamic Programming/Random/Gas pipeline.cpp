#include<bits/stdc++.h>
using namespace std;
#define xx first
#define yy second

long long dp[200005][2],n,a,b;
string s;
long long solve(int i,int prev){
    if(i==n-1)return prev?a:0;
    long long &ret=dp[i][prev];
    if(ret!=-1)return ret;
    if(prev==0){
        if(s[i]=='1')ret=solve(i+1,1)+a+b+b;
        else ret=solve(i+1,0);
    }
    else {
        if(s[i]=='1')ret=solve(i+1,1)+b;
        else ret=min(solve(i+1,0)+a,solve(i+1,1)+b);
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>a>>b;
        cin>>s;
        for(int i=0; i<n; i++)dp[i][0]=dp[i][1]=-1;
        cout<<(b*(n+1))+(a*n)+solve(0,0)<<endl;
    }
return 0;
}

