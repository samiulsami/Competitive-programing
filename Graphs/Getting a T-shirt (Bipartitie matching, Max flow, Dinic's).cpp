#include<bits/stdc++.h>
/*
    problem: LightOJ 1176	Getting a T-shirt
    verdict: AC
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
            int u,v;
            int cap, flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        const int MAX=65;

        vector<edge>edges;
        vector<int> graph[MAX];
        int lvl[MAX],nxt[MAX];
        int n,edge_cnt,S,T;

        void init(int nn, int SS, int TT){
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
            if(S==T)return 0;

            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }

            int flow=0,f=0;

            while(bfs()){
                for(int i=0; i<n; i++)nxt[i]=0;
                while(f=dfs(S,INT_MAX))flow+=f;
            }

            return flow;
        }
}

        #define Multiple_Test_Cases

map<string,int>shirtMap;
string shirtArr[] = {"XXL", "XL", "L", "M", "S", "XS"};

inline void Solve(int Case){
    int n,m;
    //for(int i=0; i<6; i++)cout<<shirtArr[i]<<" "<<shirtMap[shirtArr[i]]<<endl;

    string u,v;
    cin>>n>>m;

    int offset=6;
    int source = m+7;
    int sink = m+8;

    Dinic::init(m+9,source,sink);
    for(int i=0; i<6; i++){
            Dinic::addEdge(i,sink,n);
            //cout<<"i: "<<i<<", sink: "<<sink<<", n: "<<n<<endl;
    }

    for(int i=0,shirt1,shirt2; i<m; i++){
        cin>>u>>v;

        Dinic::addEdge(source,offset+i,1);
        Dinic::addEdge(offset+i,shirtMap[u],1);
        Dinic::addEdge(offset+i,shirtMap[v],1);
    }

    bool possible=0;
    if(Dinic::maxFlow(source,sink)==m)possible=1;

    cout<<"Case "<<Case<<": "<<(possible?"YES\n":"NO\n");
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    for(int i=0; i<6; i++)shirtMap[shirtArr[i]] = i;
    int T=1;

    #ifdef Multiple_Test_Cases
        cin>>T;
        //si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        solve(0);
    #endif

return 0;
}
