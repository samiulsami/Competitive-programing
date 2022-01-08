#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

struct mk_lines{
    int u,v,c;
    mk_lines(int u,int v,int c){
        this->u=u;
        this->v=v;
        this->c=c;
    }
};

int prims(vector<pii>graph[]){
    priority_queue<pii,vector<pii>,greater<pii> >pq;
    pq.push({0,1});
    int total=0;
    map<int,int>vis;
    while(!pq.empty()){
        pii top=pq.top();
        pq.pop();
        int u=top.second,w=top.first;
        if(!vis[u]){
            total+=w;
            vis[u]=1;
        }
        else continue;
        for(int i=0; i<graph[u].size(); i++){
            if(vis[graph[u][i].second])continue;
            pq.push(graph[u][i]);
        }
    }
    return total;
}

int main(){
    //freopen("output.txt","w",stdout);
    int n,k,m;
    bool first=1;
    while(scanf("%d",&n)==1){
        if(first)first=0;
        else printf("\n");
        vector<pii>graph[n+1];
        for(int i=0,u,v,c; i<n-1; i++){
            scanf("%d%d%d",&u,&v,&c);
            graph[u].push_back({c,v});
            graph[v].push_back({c,u});
        }
        scanf("%d",&k);
        vector<mk_lines>k_lines;
        for(int i=0,u,v,c; i<k; i++){
            scanf("%d%d%d",&u,&v,&c);
            k_lines.push_back(mk_lines(u,v,c));
        }
        scanf("%d",&m);
        for(int i=0,u,v,c; i<m; i++){
            scanf("%d%d%d",&u,&v,&c);
            graph[u].push_back({c,v});
            graph[v].push_back({c,u});
        }
        printf("%d\n",prims(graph));
        for(int i=0,u,v,c; i<k; i++){
            u=k_lines[i].u;
            v=k_lines[i].v;
            c=k_lines[i].c;
            graph[u].push_back({c,v});
            graph[v].push_back({c,u});
        }
        printf("%d\n",prims(graph));
    }
return 0;
}
