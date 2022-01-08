#include<bits/stdc++.h>
using namespace std;

long long n,k;
long long A[105],C[105];
long long dp[105][1005];

long long calc(long long i, long long amount){
    if(amount==0)return 1;
    if(i>=n || amount<0)return 0;
    if(dp[i][amount]!=-1)return dp[i][amount];
    dp[i][amount]=0;
    for(long long j=0; j<=C[i]; j++)
        dp[i][amount] += calc(i+1, amount-(j*A[i]))%100000007;
    return dp[i][amount]%100000007;
}

int main(){
    int t;
    cin>>t;
    for(long long cas=1; cas<=t; cas++){
        memset(dp, -1, sizeof(dp));
        cin>>n>>k;
        for(int i=0; i<n; i++)cin>>A[i];
        for(int i=0; i<n; i++)cin>>C[i];
        printf("Case %lld: %lld\n", cas, calc(0,k));
    }
return 0;
}
