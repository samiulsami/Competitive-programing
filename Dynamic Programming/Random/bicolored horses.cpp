#include<bits/stdc++.h>
using namespace std;

int arr[505];
int dp[505][505];

int solve(int n,int k){
    int &ret = dp[n][k];
    if(ret!=-1)return ret;
    if(k==0)return ret = arr[n]*(n-arr[n]);
    for(int i=1; i<=n && n-i>=k-1; i++){
        int cost = solve(n-i,k-1) + (arr[n]-arr[n-i])*(i-arr[n]+arr[n-i]);
        if(ret==-1 || cost<ret)ret=cost;
    }
    return ret;
}

int main(){
    memset(dp,-1,sizeof(dp));
    int n,k;
    cin>>n>>k;
    arr[0]=0;
    for(int i=1; i<=n; i++){
        cin>>arr[i];
        arr[i]+=arr[i-1];
    }
    cout<<solve(n,k-1);
return 0;
}
