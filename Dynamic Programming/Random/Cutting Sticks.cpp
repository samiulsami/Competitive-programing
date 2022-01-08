#include<bits/stdc++.h>
using namespace std;

int l,n;
int arr[53];
int dp[53][53];

int solve(int i=0, int j=n+1){
    if(i==j-1)return 0;
    int &ret=dp[i][j];
    if(~ret)return ret;
    ret=INT_MAX;
    for(int k=i+1; k<j; k++)
        ret=min(ret,solve(i,k)+solve(k,j)+arr[j]-arr[i]);
    return ret;
}

int main(){
    while(cin>>l){
        if(!l)break;
        cin>>n;
        arr[0]=0;
        for(int i=1; i<=n; i++)cin>>arr[i];
        arr[n+1]=l;
        memset(dp,-1,sizeof(dp));
        cout<<"The minimum cutting is "<<solve()<<"."<<endl;
    }
return 0;
}
