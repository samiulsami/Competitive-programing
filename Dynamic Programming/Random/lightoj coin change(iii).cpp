#include<bits/stdc++.h>
using namespace std;

int main(){
    int t,n,m;
    int coins[105],cnt[105];
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n>>m;
        for(int i=0; i<n; i++)cin>>coins[i];
        for(int i=0; i<n; i++)cin>>cnt[i];
        bool vis[m+1]={0};
        vis[0]=1;
        int ans=0;
        int counter[m+1];
        for(int i=0; i<n; i++){
            for(int j=0; j<=m; j++)counter[j]=0;
            for(int j=coins[i]; j<=m; j++){
                if(!vis[j] && vis[j-coins[i]] && counter[j-coins[i]]<cnt[i]){
                    counter[j]=counter[j-coins[i]]+1;
                    ans++;
                    vis[j]=1;
                }
            }
        }
        cout<<"Case "<<cas<<": "<<ans<<endl;
    }

return 0;
}
