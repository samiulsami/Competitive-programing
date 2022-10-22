#include<bits/stdc++.h>
using namespace std;

struct edge{
    int v,c;
    edge(){}
    edge(int v,int c){this->v=v;this->c=c;}
};

class cmp{
public:
    bool operator()(edge &a, edge &b){
        return a.c>b.c;
    }
};

int main(){
    //freopen("output.txt","w",stdout);
    int t,n,exit_cell,time_lim,m;
    cin>>t;
    while(t--){
        cin>>n>>exit_cell>>time_lim>>m;
        vector<edge>edges[n+1];
        int dist[n+1];
        memset(dist,-1,sizeof(dist));
        for(int i=0,u,v,c; i<m; i++){
            cin>>u>>v>>c;
            edges[v].push_back(edge(u,c));
        }
        priority_queue<edge,vector<edge>,cmp>pq;
        pq.push(edge(exit_cell,0));
        dist[exit_cell]=0;
        int possible_count=1;
        bool vis[105]={0};
        vis[exit_cell]=1;
        while(!pq.empty()){
            edge top=pq.top();
            pq.pop();
            if(dist[top.v]<top.c)continue;
            for(int i=0; i<edges[top.v].size(); i++){
                int v=edges[top.v][i].v;
                int u=top.v;
                int cst=edges[top.v][i].c;
                if(dist[v]==-1 || (dist[v]>dist[u]+cst)){
                    dist[v]=dist[u]+cst;
                    if(dist[v]<=time_lim && !vis[v]){
                        vis[v]=1;
                        possible_count++;
                    }
                    pq.push(edge(v,dist[v]));
                }
            }
        }
        cout<<possible_count<<endl;
        if(t)cout<<endl;
    }
return 0;
}
