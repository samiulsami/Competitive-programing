#include<bits/stdc++.h>
using namespace std;

int n;
long long dp[505][505];

long long solve(int i, int rem){/// i = current column, rem = remaining blocks
    if(rem<0)return 0;
    if(rem==0)return 1;
    long long &ret = dp[i][rem];
    if(ret!=-1)return ret;
    return ret = solve(i+1, rem-i-1) + solve(i, rem-1);
}

int main(){
    memset(dp, -1, sizeof(dp));
    cin>>n;
    cout<<solve(1, n-1)-1<<endl;
return 0;
}
