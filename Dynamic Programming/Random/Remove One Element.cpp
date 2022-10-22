#include<bits/stdc++.h>
using namespace std;

/*
    Codeforces 1272D - Remove One Element
*/

vector<map<int,int> >dp[2];
vector<map<int,bool> >vis[2];
int arr[200005];
int n;

int f(int i, int prev, bool taken){
    if(i==n-1)return arr[i]>prev;
    int &ret = dp[taken][i][prev];
    if(vis[taken][i][prev])return ret;
    vis[taken][i][prev]=1;
    if(arr[i]>prev){
        ret=f(i+1,arr[i],taken)+1;
        if(!taken)ret=max(ret,f(i+1,prev,1));
    }
    else if(!taken){
        ret=f(i+1,prev,1);
    }
    else ret=0;
    return ret;
}


int main(){
    scanf("%d",&n);
    dp[0].resize(n+5);
    dp[1].resize(n+5);
    vis[0].resize(n+5);
    vis[1].resize(n+5);
    for(int i=0; i<n; i++){
            scanf("%d",&arr[i]);
    }
    int ans=f(0,0,0);
    for(int i=0; i<n; i++)ans=max(ans,f(i,0,0));
    printf("%d",ans);
return 0;
}
