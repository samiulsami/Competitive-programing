#include<bits/stdc++.h>
using namespace std;

int n,p[1005],w[1005],people,peopleCount,g,ans;
int dp[1005][35];

int knapsack(int i=0,int cap=g){
    if(i>=n || cap<0)return 0;
    if(dp[i][cap]!=-1)return dp[i][cap];
    if(cap-w[i]>=0){
        return dp[i][cap] = max(knapsack(i+1, cap-w[i])+p[i], knapsack(i+1, cap));
    }
    return dp[i][cap] = knapsack(i+1, cap);
}

int main(){
    int t;
    cin>>t;
    while(t--){
        ans = 0;
        memset(dp, -1, sizeof(dp));
        cin>>n;
        for(int i=0; i<n; i++)cin>>p[i]>>w[i];
        cin>>peopleCount;
        while(peopleCount--){
            cin>>g;
            ans+=knapsack(0, g);
        }
        cout<<ans<<endl;
    }

return 0;
}
