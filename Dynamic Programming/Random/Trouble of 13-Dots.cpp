#include<bits/stdc++.h>
using namespace std;

int dp[10005][105];
pair<int,int>arr[105];
int m,n;

int solve(int i, int amount){
    if(i==n || amount>=m)return 0;
    int &ret=dp[amount][i];
    if(~ret)return ret;
    ret=0;
    int sum=amount+arr[i].first;
    if(sum<=m || (sum>2000 && sum-m<=200))ret=solve(i+1,sum)+arr[i].second;
    return ret = max(ret,solve(i+1,amount));
}

int main(){
    //freopen("output.txt","w",stdout);
    while(cin>>m>>n){
        for(int i=0; i<n; i++)cin>>arr[i].first>>arr[i].second;
        sort(arr,arr+n);
        memset(dp,-1,sizeof(dp));
        cout<<solve(0,0)<<endl;
    }
return 0;
}
