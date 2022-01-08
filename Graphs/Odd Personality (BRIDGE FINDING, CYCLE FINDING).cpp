#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1300 - Odd Personality
    verdict: AC
*/

vector<int>graph[10005];
int discovery_time[10005];
int min_time[10005];
set<pair<int,int> >cutEdges;
int Time=0;
bool vis[10005];
int lvl[10005];
int NodesInComponent;

void dfs(int src, int parent){
    discovery_time[src]=min_time[src]=++Time;
    for(int v:graph[src]){
        if(v==parent)continue;
        if(discovery_time[v])
            min_time[src]=min(min_time[src],discovery_time[v]);
        else{
            dfs(v,src);
            min_time[src]=min(min_time[src],min_time[v]);
            if(discovery_time[src]<min_time[v]){
                cutEdges.insert(make_pair(min(src,v),max(src,v)));
            }
        }
    }
}

bool dfs2(int src,int parent){
    vis[src]=1;
    NodesInComponent++;
    bool ret=0;
    for(int v:graph[src]){
        if(v==parent || cutEdges.find(make_pair(min(src,v),max(src,v)))!=cutEdges.end())continue;
        if(vis[v]){
            if((lvl[src]-lvl[v]+1)%2)ret=1;
            //printf("lvl[%d] = %d, lvl[%d] = %d\n",src,lvl[src],v,lvl[v]);
            //cout<<"ret: "<<ret<<endl;
        }
        else{
            vis[v]=1;
            lvl[v]=lvl[src]+1;
            ret|=dfs2(v,src);
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

        for(int i=0; i<=n; i++){
            graph[i].clear();
            discovery_time[i]=min_time[i]=0;
            vis[i]=0;
            lvl[i]=0;
        }
        Time=0;
        cutEdges.clear();

        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        for(int i=0; i<n; i++){
            if(!discovery_time[i])dfs(i,i);
        }

        int ans=0;
        for(int i=0,component; i<n; i++){
            if(!vis[i]){
                NodesInComponent=0;
                //cout<<i<<endl;
                if(dfs2(i,i))ans+=NodesInComponent;
            }
        }
        printf("Case %d: %d\n",cas,ans);
    }

return 0;
}
