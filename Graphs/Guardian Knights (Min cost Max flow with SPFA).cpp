#include<bits/stdc++.h>
/*
    Problem: LightOJ 1243 - Guardian Knights
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<=n; i++)
#define FORR(i,l,r) for(int i=l; i<=r; i++)
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define eikhane cerr<<"Eikhane"<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;

namespace mcmf{

        struct edge{
            int u,v;
            int cap, flow, cost;
            edge(){}
            edge(int u, int v, int cap, int cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        const int MAX = 1e3+5;
        const int INF = 1e9;

        vector<edge>edges;
        vector<int>graph[MAX];
        int parent[MAX];
        int dist[MAX];
        bool inQueue[MAX];
        int n,edge_cnt,S,T;
        queue<int>q;

        void init(int nn, int SS=0, int TT=0){
            n=nn;
            S=SS;
            T=TT;
            edges.clear();
            for(int i=0; i<n; i++)graph[i].clear();
            edge_cnt=0;
        }

        void addEdge(int u, int v, int cap, int cost){
            edges.emplace_back(u,v,cap,cost);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0,-cost);
            graph[v].push_back(edge_cnt++);
        }

        bool spfa(){
            for(int i=0; i<n; i++){
                    parent[i]=-1;
                    dist[i]=INF;
                    inQueue[i]=0;
            }

            dist[S]=0;
            q.push(S);

            while(!q.empty()){
                int u = q.front();
                int cost = dist[u];
                inQueue[u]=0;
                q.pop();

                for(int id:graph[u]){
                    edge &v = edges[id];
                    if(v.cap<=v.flow)continue;
                    if(cost+v.cost<dist[v.v]){
                        dist[v.v]=cost+v.cost;
                        parent[v.v]=id;
                        if(!inQueue[v.v]){
                                q.push(v.v);
                                inQueue[v.v]=1;
                        }
                    }
                }
            }

            return (dist[T]!=INF);
        }

        pair<int,int> MincostMaxflow(int s=-1, int t=-1){
            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }
            if(S==T)return {0,0};

            int flow=0,cost=0;

            while(spfa()){
                int min_flow=INT_MAX;
                int cur,id;

                cur=T;
                do{
                    id=parent[cur];
                    edge &edgeID = edges[id];
                    min_flow=min(min_flow,(edgeID.cap-edgeID.flow));
                    cur = edgeID.u;
                }while(cur!=S);

                cur=T;
                do{
                    id=parent[cur];
                    edges[id].flow+=min_flow;
                    edges[id^1].flow-=min_flow;
                    cur=edges[id].u;
                }while(cur!=S);

                flow+=min_flow;
                cost+=dist[T]*min_flow;///If cost is for 1 unit of flow
            }

            return {cost,flow};
        }
}

char grid[32][32];
bool vis[32][32];
int lvl[32][32];
int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

inline void bfs(int i, int j, int n){
    queue<pii>q;
    memset(vis,0,sizeof(vis));
    vis[i][j]=1;
    lvl[i][j]=0;
    q.push({i,j});

    while(!q.empty()){
        pii top = q.front();
        vis[top.xx][top.yy]=1;
        q.pop();

        for(int ii=0; ii<4; ii++){
            int newi = top.xx+dx[ii];
            int newj = top.yy+dy[ii];
            if(!(newi>=0 && newi<n && newj>=0 && newj<n))continue;
            if(vis[newi][newj] || grid[newi][newj]=='#')continue;

            vis[newi][newj] = 1;
            lvl[newi][newj] = lvl[top.xx][top.yy]+1;
            if(grid[newi][newj]=='m'){
                mcmf::addEdge((i*n)+j, (newi*n)+newj, 1, lvl[newi][newj]);
            }
            q.push({newi,newj});
        }
    }
    /*pf("for %d %d\n",i,j);
    FOR(i,n-1){
        FOR(j,n-1){
            pf("%d ",lvl[i][j]);
        }
        nl;
    }
    pf("-------------\n");*/
}

inline void Solve(int Case){
    int n,m,k;
    siii(n,k,m);

    int knightCap[30]={0};
    int source = n*n+1;
    int sink = source+1;

    mcmf::init(n*n+4,source,sink);

    ///read grid, and add edges from mills to sink
    FOR(i,n-1){
        sf("%s",grid[i]);
        FOR(j,n-1){
            if(grid[i][j]=='m')mcmf::addEdge((i*n)+j, sink, 1, 0);
        }
    }

    FOR(i,k-1){
        int cap;
        si(cap);
        knightCap[i]=cap;
    }


    FOR(i,n-1){
        FOR(j,n-1){
            if(grid[i][j]<='Z' && grid[i][j]>='A'){

                ///add edges from source to knights
                //pf("knight: %c : %d\n",grid[i][j], knightCap[((int)grid[i][j]-'A')]);
                mcmf::addEdge(source, (i*n)+j, knightCap[((int)grid[i][j]-'A')], 0);

                ///add edges from knights to mills
                bfs(i,j,n);
            }
        }
    }

    pf("Case %d: %d\n",Case, mcmf::MincostMaxflow(source,sink).first);
}

  #define Multiple_Test_Cases
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
