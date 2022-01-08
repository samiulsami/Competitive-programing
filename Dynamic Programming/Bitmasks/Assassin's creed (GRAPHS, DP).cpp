#include<bits/stdc++.h>
using namespace std;

vector<int>graph[20],dag[20];
int dp[(1<<16)+2];
bool vis[(1<<16)+2],vis2[16][(1<<16)+2];

void showmask(int mask){
    for(int i=1; i<=15; i++)cout<<bool(mask&(1<<i));
    cout<<endl;
}

void dfs(int u, int mask){
    mask|=(1<<u);
    //cout<<"dfs mask: ";
    //showmask(mask);
    vis[mask]=1;
    vis2[u][mask]=1;
    for(int v:graph[u])
        if(!vis2[v][mask|(1<<v)])
            dfs(v,mask);
}

int solve(int mask){
    if(mask==0)return 0;

    int &ret=dp[mask];
    if(ret!=-1)return ret;
    ret=16;

    for(int i=mask; i>0; i=(i-1)&mask){
        if(vis[i]){
            //cout<<"ret: "<<ret<<endl;
            ret=min(ret,solve(i^mask)+1);
        }
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);

        for(int i=0; i<=n; i++)
            graph[i].clear();

        for(int u=0; u<=n; u++){
            for(int i=0,mx=(1<<(n+1))-2; i<=mx; i++){
                dp[i]=-1;
                vis[i]=0;
                vis2[u][i]=0;
            }
        }

        for(int u,v,i=0; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
        }

        for(int i=1; i<=n; i++)
            dfs(i,0);

        printf("Case %d: %d\n",cas,solve((1<<(n+1))-2));
    }

return 0;
}
