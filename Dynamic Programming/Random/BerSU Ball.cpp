#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[105],b[105];
int dp[105][105];

int solve(int i, int j){
    if(i>=n || j>=m)return 0;
    int &ret = dp[i][j];
    if(ret!=-1)return ret;
    if(a[i]-b[j]>=-1 && a[i]-b[j]<=1)return ret = max(solve(i+1,j+1)+1, max(solve(i+1,j), solve(i,j+1)));
    return ret = max(solve(i+1, j), solve(i, j+1));
}

int main(){
    memset(dp, -1, sizeof(dp));
    cin>>n;
    for(int i=0; i<n; i++)cin>>a[i];
    cin>>m;
    for(int i=0; i<m; i++)cin>>b[i];
    sort(a, a+n);
    sort(b, b+m);
    cout<<solve(0,0);
return 0;
}
