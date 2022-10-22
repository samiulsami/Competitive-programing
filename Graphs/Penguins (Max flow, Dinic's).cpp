#include<bits/stdc++.h>
/*
    Problem: LightOJ 1154 - Penguins
    Verdict: AC
*/
using namespace std;
typedef long long ll;

#define xx first
#define yy second
#define si(x) scanf("%d",&x)
#define sl(x) scanf("%d",&x)
#define FOR(n) for(int i=0; i<n; i++)
#define FORR(startVal,n) for(int i=startVal; i<n; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl

namespace Dinic{

        struct edge{
            short u,v;
            short cap, flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        const int MAX=206;

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

        void addEdge(int u, int v, int cap, bool bidirectional = false){
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

        int maxFlow(int s=-1, int t=-1){
            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }
            if(S==T)return 0;

            int flow=0,f=0;

            while(bfs()){
                for(int i=0; i<n; i++)nxt[i]=0;
                while(f=dfs(S,INT_MAX))flow+=f;
            }
            return flow;
        }
}

        #define Multiple_Test_Cases

double minDist(int x, int y, int x1, int y1){
    if(x==x1)return abs(y-y1);
    if(y==y1)return abs(x-x1);

    int axis1 = abs(x-x1);
    int axis2 = abs(y-y1);
    axis1*=axis1;
    axis2*=axis2;

    return (double)sqrt(double(axis1) + double(axis2));
}

struct icefloe{
    short x,y,capacity;
    icefloe(short x, short y, short capacity):x(x),y(y),capacity(capacity){}
};

inline void Solve(int Case){
    int n,penguins,cap,total_penguins=0;
    double maxJump,dist;

    scanf("%d%lf",&n,&maxJump);
    vector<icefloe>icefloes;
    vector<short>possible_floes;
    Dinic::init(2*n+5);
    int source = 2*n+3;

    for(int i=0,x,y; i<n; i++){
        scanf("%d%d%d%d",&x,&y,&penguins,&cap);
        icefloes.emplace_back(x,y,cap);
        total_penguins+=penguins;
        Dinic::addEdge(source,i,penguins);
        Dinic::addEdge(i,i+n,cap);
    }

    for(int i=0; i<n; i++){
        icefloe &a=icefloes[i];
        for(int j=i+1; j<n; j++){
            if(i==j)continue;
            icefloe &b=icefloes[j];
            dist = minDist(a.x,a.y,b.x,b.y);
            if(dist<=maxJump){
                Dinic::addEdge(i+n, j, a.capacity);
                Dinic::addEdge(j+n, i, b.capacity);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<Dinic::edge_cnt; j++)Dinic::edges[j].flow=0;

        int mxFlow=Dinic::maxFlow(source,i);
        if(mxFlow == total_penguins)possible_floes.push_back(i);
        //printf("i: %d, maxflow: %d, totalpenguins: %d\n",i,mxFlow,total_penguins);
    }

    printf("Case %d:",Case);
    if(possible_floes.size()==0)possible_floes.push_back(-1);
    for(int i:possible_floes)printf(" %d",i);
    printf("\n");
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
