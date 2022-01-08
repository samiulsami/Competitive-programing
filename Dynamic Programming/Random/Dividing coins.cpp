#include<bits/stdc++.h>
using namespace std;

int n;
int dp[102][50002];
int arr[205];

int solve(int i=0, int cur=0){
    if(i==n)return cur;
    int &ret = dp[i][cur];
    if(ret!=-1)return ret;
    return ret = min(solve(i+1,cur+arr[i]),solve(i+1,abs(cur-arr[i])));
}

int main(){
    int t;
    //freopen("output.txt","w",stdout);
    cin>>t;
    while(t--){
        cin>>n;
        sum=0;
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<n; i++)cin>>arr[i];
        cout<<solve()<<endl;
    }
return 0;
}
