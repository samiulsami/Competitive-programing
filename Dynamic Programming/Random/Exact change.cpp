#include<bits/stdc++.h>
using namespace std;

int arr[105];
int n;
typedef pair<int,int> pii;
pii dp[105][10005];

pii solve(int i,int amount){
    if(amount<=0)return make_pair(-amount,0);
    if(i==n)return make_pair(100000,200);
    pii &ret = dp[i][amount];
    if(~ret.first)return ret;
    ret=solve(i+1,amount-arr[i]);
    ret.second++;
    return ret=min(ret,solve(i+1,amount));
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int amount;
        scanf("%d%d",&amount,&n);
        for(int i=0; i<n; i++)scanf("%d",&arr[i]);
        for(int i=0; i<=100; i++)
            for(int j=0; j<=10000; j++)dp[i][j].first=-1;
        printf("%d %d\n",amount+solve(0,amount).first,solve(0,amount).second);
    }
return 0;
}

