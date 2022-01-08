#include<bits/stdc++.h>
/*
    Problem: LightOJ 1155 - Power Transmission
    verdict: AC
*/

using namespace std;
typedef long long ll;

#define xx first
#define yy second
#define sf scanf
#define pf printf
#define dbug(x) cout<<"dbug: "<<x<<endl

namespace Dinic{

        struct edge{
            int u,v;
            ll cap, flow;
            edge(){}
            edge(int u, int v, ll cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        const int MAX=1e4+5;

        vector<edge>edges;
        vector<int> graph[MAX];
        int lvl[MAX],nxt[MAX];
        int n,edge_cnt,S,T;

        void init(int nn, int SS=-1, int TT=-1){
            n=nn;
            S=SS;
            T=TT;
            edges.clear();
            for(int i=0; i<n; i++)graph[i].clear();
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
                S=s;
                T=t;
            }

            ll flow=0,f=0;

            while(bfs()){
                for(int i=0; i<n; i++)nxt[i]=0;
                while(f=dfs(S,LLONG_MAX))flow+=f;
            }

            return flow;
        }
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int t,n,m,B,D;
    sf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        sf("%d",&n);
        Dinic::init(2*n+3,1+2*n,2+2*n);
        int source = 1+2*n;
        int sink = 2+2*n;

        for(int i=0,cap; i<n; i++){
            sf("%d",&cap);
            Dinic::addEdge(i,i+n,cap);
        }

        scanf("%d",&m);
        for(int i=0,u,v,c; i<m; i++){
            scanf("%d%d%d",&u,&v,&c);
            u--;
            v--;
            Dinic::addEdge(u+n,v,c);
        }

        sf("%d%d",&B,&D);
        for(int i=0,u; i<B; i++){
                sf("%d",&u);
                u--;
                Dinic::addEdge(source,u,INT_MAX);
        }

        for(int i=0,u; i<D; i++){
                sf("%d",&u);
                u--;
                Dinic::addEdge(u+n,sink,INT_MAX);
        }

        printf("Case %d: %lld\n", cas, Dinic::maxFlow(source,sink));
    }



return 0;
}
