#include<bits/stdc++.h>
using namespace std;

struct edge{
    int u,v,cap,flow;
    edge(){}
    edge(int u, int v, int cap):u(u),v(v),cap(cap){
        flow=0;
    }
};

struct Dinic{

        vector<edge>edges;
        vector<vector<int> > graph;
        vector<int> lvl,nxt;
        int n,edge_cnt,S,T;

        Dinic(int n):n(n),graph(n),lvl(n),nxt(n){
            edge_cnt=0;
        }

        void addEdge(int u, int v, int cap){
            edges.emplace_back(u,v,cap);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0);
            graph[v].push_back(edge_cnt++);
        }

        bool bfs(){
            queue<int>q;
            q.push(S);
            fill(lvl.begin(),lvl.end(),-1);
            lvl[S]=0;
            while(!q.empty()){
                int u=q.front();
                if(u==T)break;
                q.pop();
                for(int edgeID : graph[u]){
                    edge &v = edges[edgeID];
                    if(v.cap<=v.flow || lvl[v.v]!=-1)continue;
                    lvl[v.v]=lvl[u]+1;
                    q.push(v.v);
                }
            }
            return lvl[T]!=-1;
        }

        int dfs(int u, int pathFlow){
            if(pathFlow==0 || u==T)return pathFlow;
            int ret=0;
            int id;
            for(int &edgeID=nxt[u]; edgeID<(int)graph[u].size(); edgeID++){
                id = graph[u][edgeID];
                edge &v = edges[id];
                if(lvl[v.v]!=lvl[u]+1 || v.cap<=v.flow)continue;
                if(ret=dfs(v.v, min(pathFlow, v.cap-v.flow))){
                    edges[id].flow+=ret;
                    edges[id^1].flow-=ret;
                    return ret;
                }
            }
            return 0;
        }

        int maxFlow(int s, int t){
            S=s;
            T=t;
            int flow=0,f=0;
            while(bfs()){
                fill(nxt.begin(),nxt.end(),0);
                while(f=dfs(S,INT_MAX))flow+=f;
            }
            return flow;
        }

};

int a[500];
int b[500];
typedef pair<int,int>pii;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; i++){
                scanf("%d",&a[i]);
        }
        int source=n+m+2;
        int sink=source+1;
        Dinic dinic(n+m+10);
        vector<pii>edges;
        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            edges.push_back(pii(dinic.edge_cnt, dinic.edge_cnt+2));
            dinic.addEdge(i,u+m,1);
            dinic.addEdge(i,v+m,1);
            dinic.addEdge(source,i,1);
        }
        for(int i=1; i<=n; i++){
            dinic.addEdge(i+m,sink,a[i]);
        }

        int mx=m-dinic.maxFlow(source,sink);
        printf("%d\n",max(0,mx));
        for(pii e:edges){
            if(dinic.edges[e.first].flow)printf("1");
            else printf("0");
        }
        printf("\n");
    }

return 0;
}
