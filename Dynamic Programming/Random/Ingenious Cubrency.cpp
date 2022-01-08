#include<bits/stdc++.h>
using namespace std;

int coins[25],coinCount=0;
long long dp[25][10005];

long long solve(int i, int amount){
    if(amount==0)return 1;
    if(i>=coinCount || amount<0)return 0;
    if(dp[i][amount]!=-1)return dp[i][amount];
    return dp[i][amount] = solve(i, amount-coins[i]) + solve(i+1, amount);
}

int main(){
    for(int i=1; i*i*i<=9261; i++)coins[coinCount++]=i*i*i;
    memset(dp, -1, sizeof(dp));
    int n;
    while(scanf("%d",&n)==1){
        printf("%lld\n",solve(0,n));
    }
return 0;
}
