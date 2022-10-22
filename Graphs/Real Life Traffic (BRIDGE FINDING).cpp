#include<bits/stdc++.h>
using namespace std;
/*
    LightOJ: 1291 - Real Life Traffic
    verdict: AC
*/
int n,m;
vector<int>graph[10005];
set<pair<int,int> >cutEdges;
int discovery_time[10005];
int min_time[10005];
int parent[10005];
int degree[10005];
int Time;

void dfs(int src, int parent){
    discovery_time[src]=min_time[src]=++Time;
    for(int v : graph[src]){
        if(v==parent)continue;
        if(discovery_time[v])
            min_time[src]=min(min_time[src],discovery_time[v]);
        else{
            dfs(v,src);
            min_time[src]=min(min_time[src],min_time[v]);
            if(discovery_time[src]<min_time[v])
                cutEdges.insert(make_pair(min(src,v),max(src,v)));
        }
    }
}

int Find(int r){
    if(parent[r]==r)return r;
    return parent[r]=Find(parent[r]);
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);

        for(int i=0; i<=n; i++){
            graph[i].clear();
            discovery_time[i]=min_time[i]=0;
            parent[i]=i;
            degree[i]=0;
        }
        Time=0;
        cutEdges.clear();

        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        dfs(0,0);

        for(int i=0,u,v; i<n; i++){
            for(int j:graph[i]){
                u=min(i,j);
                v=max(i,j);
                if(cutEdges.find((make_pair(u,v)))==cutEdges.end()){
                    u=Find(u);
                    v=Find(v);
                    if(u!=v)parent[u]=v;
                }
            }
        }

        for(pair<int,int>edge:cutEdges){
            int u=edge.first;
            int v=edge.second;
            u=Find(u);
            v=Find(v);
            degree[u]++;
            degree[v]++;
        }

        int ans=0;
        for(int i=0; i<n; i++){
            if(degree[i]==1)ans++;
        }

        printf("Case %d: %d\n",cas,(ans+1)/2);
    }

return 0;
}
