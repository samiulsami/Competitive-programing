#include<bits/stdc++.h>
using namespace std;
/*
    problem: LightOJ 1153 - Internet Bandwidth
    verdict: AC
*/

typedef long long ll;

class Dinic{
    private:

        struct edge{
            int u,v;
            ll cap, flow;
            edge(){}
            edge(int u, int v, ll cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        vector<edge>edges;
        vector<vector<int> > graph;
        vector<int>lvl,nxt;
        int n,edge_cnt,S,T;

    public:

        Dinic(int n, int S, int T):n(n),S(S),T(T){
            graph.resize(n);
            lvl.resize(n);
            nxt.resize(n);
            edge_cnt=0;
        }

        void addEdge(int u, int v, ll cap, bool bidirectional = false){
            edges.emplace_back(u,v,cap);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,(bidirectional?cap:0));
            graph[v].push_back(edge_cnt++);
        }

        bool bfs(){
            queue<int>q;
            q.push(S);
            for(int i=0; i<n; i++)lvl[i]=-1;
            lvl[S]=0;

            while(!q.empty()){
                int u=q.front();
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

        ll dfs(int u, ll pathFlow){
            if(pathFlow==0 || u==T)return pathFlow;

            ll ret=0;
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

        ll maxFlow(int s=-1, int t=-1){
            if(S==T)return 0;

            if(s!=-1 && t!=-1){
                this->S=s;
                this->T=t;
            }

            ll flow=0,f=0;

            while(bfs()){
                for(int i=0; i<n; i++)nxt[i]=0;
                ll f=0;
                while(f=dfs(S,LLONG_MAX))flow+=f;
            }

            return flow;
        }
};

#define sf scanf
#define pf printf

int main(){
    int t,n,S,T,c;
    sf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        sf("%d",&n);
        sf("%d%d%d",&S,&T,&c);

        T--;
        S--;
        Dinic dinic(n,S,T);

        for(int i=0,u,v,cst; i<c; i++){
            scanf("%d%d%d",&u,&v,&cst);
            u--;
            v--;
            dinic.addEdge(u,v,cst,1);
        }

        printf("Case %d: %lld\n",cas,dinic.maxFlow(S,T));

    }

return 0;
}
