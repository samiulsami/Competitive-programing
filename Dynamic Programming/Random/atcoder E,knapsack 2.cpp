#include<bits/stdc++.h>
using namespace std;

int N,maxW;
long long dp[102][100002];
struct asdfklj{
    long long val,w;
}arr[102];

long long knapsack(int i, int current){
    if(current==0)return 0;
    if(current<0 || i==N)return INT_MAX;
    long long &ret=dp[i][current];
    if(ret!=-1)return ret;
    return ret = min(arr[i].w+knapsack(i+1,current-arr[i].val), knapsack(i+1,current));
}

int main(){
    scanf("%d%d",&N,&maxW);
    memset(dp,-1,sizeof(dp));
    for(int i=0; i<N; i++)scanf("%I64d%I64d",&arr[i].w,&arr[i].val);
    for(int i=100000;;i--)
        if(knapsack(0,i)<=maxW)
            printf("%d",i),exit(0);
}
