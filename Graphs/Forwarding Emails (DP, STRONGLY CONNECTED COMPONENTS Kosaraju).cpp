#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1417 - Forwarding Emails
    verdict: AC
*/

const int MAX = 50005;

vector<int>graph[MAX],reverseGraph[MAX];
bitset<MAX>vis;
stack<int>topoSort;
int parent[MAX];
int counter[MAX];
int dp[MAX];
int n;

int Find(int u){
    return parent[u] = parent[u]==u? u : Find(parent[u]);
}

void dfs(int u){//topoSort
    vis[u]=1;
    for(int v: graph[u]){
        if(!vis[v]){
            vis[v]=1;
            dfs(v);
        }
    }
    topoSort.push(u);
}

void dfs1(int u){//Find SCC's
    vis[u]=1;
    int root = Find(u);

    for(int v:reverseGraph[u]){
        if(!vis[v]){
            vis[v]=1;
            dfs1(v);
            parent[v]=root;
        }
    }
}

int solve(int u){
    int &ret=dp[u];
    if(ret!=-1)return ret;

    int root=Find(u);
    ret=counter[root];

    for(int v:graph[u]){
        if(Find(v)!=root)ret=max(ret,counter[root]+solve(v));
        else ret=max(ret,solve(v));
    }

    return ret;
}

int main(){
    int t;
    scanf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        scanf("%d",&n);

        for(int i=0; i<=n; i++){
            graph[i].clear();
            reverseGraph[i].clear();
            parent[i]=i;
            counter[i]=0;
            dp[i]=-1;
        }

        for(int i=0,u,v; i<n; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            reverseGraph[v].push_back(u);
        }

        vis.reset();
        for(int i=1; i<=n; i++)
            if(!vis[i])
                dfs(i);

        vis.reset();
        while(!topoSort.empty()){
            int top=topoSort.top();
            topoSort.pop();

            if(!vis[top])
                dfs1(top);
        }

        for(int i=1; i<=n; i++)
            counter[Find(i)]++;

        int maxNodes=-1;
        int startingNode=-1;

        for(int i=1; i<=n; i++){
            //cout<<Find(i)<<"-"<<counter[Find(i)]<<endl;
            int val=solve(i);

            if(val>maxNodes){
                maxNodes=val;
                startingNode=i;
            }
            else if(val==maxNodes && i<startingNode){
                startingNode=i;
            }
        }

        printf("Case %d: %d\n",cas,startingNode);
    }

return 0;
}
