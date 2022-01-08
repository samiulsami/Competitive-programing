#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1210 - Efficient Traffic System
    Verdict: AC
*/

vector<int>graph[20005],reverseGraph[20005];
stack<int>topoSort;
bool vis[20005],vis2[20005],cmpVis[20005];
int parent[20005];
int inDegree[20005];
int outDegree[20005];

int Find(int r){
    if(parent[r]==r)return r;
    return parent[r]=Find(parent[r]);
}

void dfs(int u){//toposort
    vis[u]=1;

    for(int v:graph[u]){
        if(!vis[v]){
            vis[v]=1;
            dfs(v);
        }
    }

    topoSort.push(u);
}

void dfs2(int u){//Find SCC's
    vis2[u]=1;

    for(int v:reverseGraph[u]){
        if(!vis2[v]){
            parent[Find(v)]=Find(u);
            vis2[v]=1;
            dfs2(v);
        }
    }
}

void dfs3(int u){//Calculate in/out degrees of SCC's
    int x=Find(u),y;
    cmpVis[u]=1;
    for(int v:graph[u]){
        y=Find(v);
        if(x!=y){
            inDegree[y]++;
            outDegree[x]++;
        }
        else if(!cmpVis[v])dfs(v);
    }
}

int main(){
    //freopen("output.txt","w",stdout);

    int t,n,m;
    scanf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);

        for(int i=0; i<=n; i++){
            graph[i].clear();
            reverseGraph[i].clear();
            vis[i]=vis2[i]=cmpVis[i]=0;
            parent[i]=i;
            inDegree[i]=outDegree[i]=0;
        }

        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            reverseGraph[v].push_back(u);
        }


        for(int i=1; i<=n; i++)
            if(!vis[i])
                dfs(i);

        while(!topoSort.empty()){
            int top=topoSort.top();
            topoSort.pop();

            if(!vis2[top])
                dfs2(top);
        }

        set<int>Components;

        for(int i=1; i<=n; i++){
            if(!cmpVis[i])
                dfs3(i);

            Components.insert(Find(i));
        }

        int inZero=0;
        int outZero=0;
        int ans=0;

        for(int x:Components){
            if(inDegree[x]==0)inZero++;
            if(outDegree[x]==0)outZero++;
        }

        ans=max(inZero,outZero);
        if(Components.size()<=1)ans=0;

        printf("Case %d: %d\n",cas,ans);
    }

return 0;
}

/*

10
8 5
3 1
1 2
4 5
5 6
7 8

*/
