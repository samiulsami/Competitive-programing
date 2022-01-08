#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int N=3004;
int dp[N][N];
int lvl[N];
int val[N];
vector<int>graph[N];

int f(int i, int k){
    if(lvl[i]>k)return 0;
    int &ret = dp[i][k];
    if(~ret)return ret;
    ret=0;
    if(lvl[i]<=k)ret=max(ret,val[i]+f(1,k-lvl[i]));
    for(int v:graph[i]){
        ret=max(ret,f(v,k-1));
    }
    return ret;
}

int main(){
    int n,m,t;
    scanf("%d%d%d",&n,&m,&t);
    for(int i=2; i<=n; i++)scanf("%d",&val[i]);
    for(int i=0,l,r; i<m; i++){
        scanf("%d%d",&l,&r);
        graph[l].push_back(r);
        graph[r].push_back(l);
    }

    memset(dp,-1,sizeof(dp));
    memset(lvl,-1,sizeof(lvl));

    queue<int>q;
    q.push(1);
    lvl[1]=0;

    while(!q.empty()){
        int top=q.front();
        q.pop();

        for(int v:graph[top]){
            if(lvl[v]==-1){
                lvl[v]=lvl[top]+1;
                q.push(v);
            }
        }
    }

    for(int i=1; i<=t; i++)printf("%d ",f(1,i));
return 0;
}
