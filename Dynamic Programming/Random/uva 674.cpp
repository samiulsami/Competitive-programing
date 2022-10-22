#include<bits/stdc++.h>
using namespace std;

int changes[]={50,25,10,5,1};
//              0, 1, 2,3,4;
int n;
int dp[10005][10005];

int calc(int i, int amount){
    if(i>4 || amount<0)return 0;
    if(amount==0)return 1;
    if(dp[i][amount]!=-1)return dp[i][amount];
    return dp[i][amount] = (calc(i,amount-changes[i]) + calc(i+1, amount));
}

int main(){
    memset(dp, -1, sizeof(dp));
    while(scanf("%d",&n)==1){
        printf("%d\n",calc(0,n));
    }
return 0;
}
