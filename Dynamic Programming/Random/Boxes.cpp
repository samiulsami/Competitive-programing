#include<bits/stdc++.h>
using namespace std;

int dp[1005][3005];
pair<int,int>boxes[1005];
int n;
#define xx first
#define yy second

int solve(int i,int weight){
    if(i==n)return 0;
    int &ret=dp[i][weight];
    if(~ret)return ret;
    if(weight==0)return ret=max(solve(i+1,boxes[i].yy)+1,solve(i+1,0));
    int minweight=min(weight-boxes[i].xx,boxes[i].yy);
    if(minweight<0)return ret=solve(i+1,weight);
    if(minweight==0)return ret=1;
    return ret=max(solve(i+1,minweight)+1,solve(i+1,weight));
}

int main(){
    //freopen("output.txt","w",stdout);
    while(cin>>n,n){
        for(int i=0; i<n; i++)cin>>boxes[i].xx>>boxes[i].yy;
        memset(dp,-1,sizeof(dp));
        cout<<solve(0,0)<<endl;
    }
return 0;
}
