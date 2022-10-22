#include<bits/stdc++.h>
using namespace std;

int n,m,d;
int dp[300][50][50];///index, sum%d, #taken
int arr[201];

int solve(int i=0, int sum=0, int counter=0){
    if(counter==m)return sum==0;
    if(i==n)return 0;
    int &ret = dp[i][sum][counter];
    if(~ret)return ret;
    return ret = solve(i+1,(sum+arr[i])%d,counter+1)+solve(i+1,sum,counter);
}

int main(){
    int q;
    int Set=0;
    while(cin>>n>>q,n||q){
        for(int i=0; i<n; i++)cin>>arr[i];
        printf("SET %d:\n",++Set);
        for(int query=1; query<=q; query++){
            memset(dp,-1,sizeof(dp));
            cin>>d>>m;
            printf("QUERY %d: %d\n",query,solve());
        }
    }
return 0;
}
