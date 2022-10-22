#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1063 - Ant Hills
    verdict: AC
*/

/*
    Blog on Articulation Points
    https://codeforces.com/blog/entry/71146
*/

int n;
vector<int>graph[10005];
int discovery_time[10005];
int min_time[10005];
int Time;

int dfs(int src, int parent){
    discovery_time[src]=min_time[src]=++Time;
    int ret=0;
    bool cutVertex=0;
    int children=0;
    for(int v:graph[src]){
        if(v==parent)continue;
        if(discovery_time[v]){//Back edge to ancestor of 'src' found
            min_time[src]=min(min_time[src],discovery_time[v]);
        }
        else{
            children++;
            ret+=dfs(v,src);
            if(discovery_time[src]<=min_time[v]){
                if(src==1){
                    if(children>1)cutVertex=1;
                }
                else cutVertex=1;
            }
            min_time[src]=min(min_time[src],min_time[v]);
        }
    }
    return ret+(int)cutVertex;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t,m;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);

        for(int i=0; i<=n; i++){
            graph[i].clear();
            discovery_time[i]=min_time[i]=0;
        }
        Time=0;

        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        printf("Case %d: %d\n",cas,dfs(1,1));
    }

return 0;
}
