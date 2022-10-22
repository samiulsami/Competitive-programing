#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1034 - HIT THE LIGHT SWITCHES
    Verdict: AC
*/

vector<int>graph[10005];
int finishing_time[10005];
bool vis[10005];
bool vis2[10005];
int Time=0;

void dfs(int u){
    vis[u]=1;

    for(int v:graph[u]){
        if(!vis[v]){
            vis[v]=1;
            dfs(v);
        }
    }

    finishing_time[u]+=++Time;
}

void dfs2(int u){
    vis2[u]=1;
    for(int v:graph[u]){
        if(!vis2[v]){
            vis2[v]=1;
            dfs2(v);
        }
    }
}

int main(){
    //freopen("output.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);

        for(int i=1; i<=n; i++){
            graph[i].clear();
            finishing_time[i]=0;
            vis[i]=0;
            vis2[i]=0;
        }
        Time=0;

        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
        }

        vector<pair<int,int> >toposort;

        for(int i=1; i<=n; i++){

            if(!vis[i])
                dfs(i);

            toposort.push_back(make_pair(finishing_time[i],i));
        }


        sort(toposort.begin(),toposort.end(),greater<pair<int,int> >());

        int ans=0;

        for(auto i:toposort){
            if(!vis2[i.second]){
                dfs2(i.second);
                ans++;
            }
        }

        printf("Case %d: %d\n",cas,ans);
    }

return 0;
}
