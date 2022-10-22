/**
    Minimum cost Maximum flow with Dijkstra, using Johnson's algorithm to handle negative weights

    To initialize, call mcmf::init(n) where n is the number of nodes
    mcmf::addEdge(u,v,cap,cst) adds a directed edge u-v with capacity=cap and cost=cst.
    For undirected edges add another edge v-u.
    mcmf::MincostMaxflow(S,T) returns Minimum cost Maximum Flow pair(cost,flow) from S to T

    For Maximum cost Maximum Flow multiply the costs by '-1' before adding edges

    Time Complexity: ????
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<long long, int>pli;

namespace mcmf{

        struct edge{
            int u,v;
            ll cap, flow, cost;
            edge(){}
            edge(int u, int v, ll cap, ll cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        const int MAX = 1e4+5;
        const ll INF = 1e18;

        vector<edge>edges;
        vector<int>graph[MAX];
        int parent[MAX];
        ll h[MAX],dist[MAX];
        int n,edge_cnt,S,T;
        priority_queue<pli, vector<pli>, greater<pli> >pq;

        void init(int nn, int SS=0, int TT=0){
            n=nn;
            S=SS;
            T=TT;
            edges.clear();
            for(int i=0; i<n; i++)graph[i].clear();
            edge_cnt=0;
        }

        void addEdge(int u, int v, ll cap, ll cost){
            edges.emplace_back(u,v,cap,cost);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0,-cost);
            graph[v].push_back(edge_cnt++);
        }

        bool dijkstra(){
            for(int i=0; i<n; i++){
                    parent[i]=-1;
                    dist[i]=INF;
            }

            dist[S]=0;
            pq.push({0,S});

            while(!pq.empty()){
                int u = pq.top().second;
                ll cost = pq.top().first;
                pq.pop();
                if(dist[u]<cost)continue;

                for(int id:graph[u]){
                    edge &v = edges[id];
                    if(v.cap<=v.flow)continue;
                    ll newCost = cost + v.cost + h[v.u] - h[v.v];
                    if(newCost<dist[v.v]){
                        dist[v.v]=newCost;
                        parent[v.v]=id;
                        pq.push({dist[v.v],v.v});
                    }
                }
            }

            return (dist[T]!=INF);
        }

        pair<ll,ll> MincostMaxflow(int s=-1, int t=-1){
            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }
            if(S==T)return {0,0};

            for(int i=0; i<n; i++)h[i]=0;

            bool done=0;
            for(int i=0; i<n-1 && !done; i++){
                done=1;
                for(edge e:edges){
                    if(e.cap>e.flow && h[e.v] > h[e.u] + e.cost){
                        h[e.v]=h[e.u]+e.cost;
                        done=0;
                    }
                }
            }

            ll flow=0,cost=0;
            ll tmpCost=0;

            while(dijkstra()){
                ll min_flow=LLONG_MAX;
                int cur,id;
                tmpCost=0;

                cur=T;
                do{
                    id=parent[cur];
                    edge &edgeID = edges[id];
                    min_flow=min(min_flow,(ll)(edgeID.cap-edgeID.flow));
                    cur = edgeID.u;
                    tmpCost += edgeID.cost;
                }while(cur!=S);

                cur=T;
                do{
                    id=parent[cur];
                    edges[id].flow+=min_flow;
                    edges[id^1].flow-=min_flow;
                    cur=edges[id].u;
                }while(cur!=S);

                flow+=min_flow;
                cost+=tmpCost*min_flow; /// If cost is for per unit of flow

            }

            return {cost,flow};
        }
}

int main(){


return 0;
}
