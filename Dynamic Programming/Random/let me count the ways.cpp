#include<bits/stdc++.h>
using namespace std;

int n;
int coins[5]={1,5,10,25,50};
long long dp[30002][5];

long long solve(int i=0, int amount=n){
    if(amount==0)return 1;
    if(amount<0 || i==5)return 0;
    long long &ret = dp[amount][i];
    if(ret!=-1)return ret;
    return ret = solve(i+1,amount)+solve(i,amount-coins[i]);
}

int main(){
    memset(dp,-1,sizeof(dp));
    //freopen("output.txt","w",stdout);
    while(scanf("%d",&n)!=EOF){
        long long ans=solve(0,n);
        if(ans==1)printf("There is only 1 way to produce %d cents change.\n",n);
        else printf("There are %lld ways to produce %d cents change.\n",ans,n);
    }


return 0;
}
