#include<bits/stdc++.h>
using namespace std;

map<long long, long long>dp;

long long solve(long long x){
    if(x==0)return 0;
    if(dp[x]!=0)return dp[x];
    return dp[x] = max(x, solve(x/2)+solve(x/3)+solve(x/4));
}

int main(){
    long long x;
    while(cin>>x)cout<<solve(x)<<endl;
return 0;
}
