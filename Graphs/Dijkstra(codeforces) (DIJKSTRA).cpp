#include<bits/stdc++.h>
using namespace std;

struct edge{
    int v,c;
    edge(){}
    edge(int v,int c){
        this->v=v;
        this->c=c;
    }
};
class cmp{
public:
    bool operator()(edge &a, edge &b){
        return a.c>b.c;
    }
};
void print_path(int r, int parent[]){
    if(parent[r]!=-1)print_path(parent[r],parent);
    cout<<r<<" ";
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<edge>graph[n+1];
    for(int i=0,u,v,c; i<m; i++){
        cin>>u>>v>>c;
        graph[u].push_back(edge(v,c));
        graph[v].push_back(edge(u,c));
    }
    priority_queue<edge,vector<edge>,cmp>pq;
    pq.push(edge(1,0));
    long long dist[n+1];
    dist[1]=0;
    memset(dist,-1,sizeof(dist));
    int parent[n+1];
    while(!pq.empty()){
        int u=pq.top().v;
        int cost=pq.top().c;
        pq.pop();
        if(dist[u]<cost && dist[u]!=-1)continue;
        for(int i=0; i<graph[u].size(); i++){
            int v=graph[u][i].v;
            int cst=graph[u][i].c;
            if(dist[v]==-1 || dist[v]>dist[u]+cst){
                parent[v]=u;
                dist[v]=dist[u]+cst;
                pq.push(edge(v,dist[v]));
            }
        }
    }
    parent[1]=-1;
    if(dist[n]==-1)cout<<"-1",exit(0);
    print_path(n,parent);
return 0;
}
