#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1168 - WISHING SNAKE
    verdict: AC
*/

typedef pair<int,bool> pbi;

bitset<1005>vis;
vector<int>graph[1005];
int discovery_time[1005];
int Time;
int scc;
int parent[1005];
int totalNodes;
stack<int>curPath;
bitset<1005>inPath;

int tarjan_scc(int u){
    int low=discovery_time[u]=++Time;
    curPath.push(u);
    inPath[u]=1;

    for(int v:graph[u])
        if(!discovery_time[v])
            low=min(low,tarjan_scc(v));
        else if(inPath[v])
            low=min(low,discovery_time[v]);

    if(low==discovery_time[u]){
        int top;

        do{
            top=curPath.top();
            curPath.pop();
            inPath[top]=0;
            parent[top]=scc;
        }while(u!=top && !curPath.empty());

        scc++;
    }

    return low;
}

bool dfs(int u){
    vis[u]=1;

    int children=0;
    bool pos=1;
    totalNodes--;

    for(int v:graph[u])
        if(!vis[v]){

            vis[v]=1;

            if(parent[u]!=parent[v])
                children++;
            //cout<<u<<" -> "<<v<<endl;
            pos = pos && dfs(v);

        }
        else if(parent[u]!=parent[v])return 0;

    return (pos && children<2);
}

int main(){
    //freopen("output.txt","w",stdout);
    int t,n,k;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){

        for(int i=0; i<1005; i++){
            graph[i].clear();
            discovery_time[i]=0;
            parent[i]=i;
        }
        Time=0;
        totalNodes=0;
        scc=0;
        vis.reset();
        //inPath.reset();

        scanf("%d",&n);

        vector<int>Nodes;

        for(int i=0; i<n; i++){

            scanf("%d",&k);

            for(int j=0,u,v; j<k; j++){

                scanf("%d%d",&u,&v);

                if(!vis[u])Nodes.push_back(u);
                if(!vis[v])Nodes.push_back(v);

                vis[u]=vis[v]=1;
                graph[u].push_back(v);
            }

        }

        totalNodes=(int)Nodes.size();

        for(int i:Nodes)
            if(!discovery_time[i])
                tarjan_scc(i);

        vis.reset();
        bool possible=dfs(0);

        if(possible && totalNodes==0)possible=1;
        else possible=0;

        // cout<<"res.first: "<<res.first<<endl;
        //cout<<"res.second: "<<res.second<<endl

        //cout<<"scc: "<<scc<<endl;
        printf("Case %d: ",cas);
        if(possible)printf("YES\n");
        else printf("NO\n");

    }

return 0;
}

/*
1
2
4
1 2
2 3
3 1
1 4
3
4 5
5 6
6 4
*/
