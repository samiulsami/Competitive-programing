#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int dp[1005];
int solve(int i=0){
    if(i==n)return 0;
    int &ret=dp[i];
    if(~ret)return ret;
    ret=1005;
    for(int j=i; j<n; j++){
        bool isPal=1;
        for(int x=i,y=j; isPal && x<=y; x++,y--)if(s[x]!=s[y])isPal=0;
        if(isPal)ret=min(ret,solve(j+1)+1);
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>s;
        memset(dp,-1,sizeof(dp));
        n=s.length();
        cout<<"Case "<<cas<<": "<<solve(0)<<endl;
    }
return 0;
}
