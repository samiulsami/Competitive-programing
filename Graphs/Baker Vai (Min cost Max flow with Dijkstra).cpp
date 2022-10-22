#include<bits/stdc++.h>
/*
    Problem: LightOJ 1071 - Baker Vai
    verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%d",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(n) for(int i=0; i<=n; i++)
#define FORR(l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl
#define printCase(cs) printf("Case %d: ",cs)
#define printCaseNL(cs) printf("Case %d:\n",cs)

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);

typedef pair<int, int>pli;

namespace mcmf{

        struct edge{
            int u,v;
            int cap, flow, cost;
            edge(){}
            edge(int u, int v, int cap, int cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        const int MAX = 20005;
        const int INF = 1e9;

        vector<edge>edges;
        vector<int>graph[MAX];
        int parent[MAX];
        int h[MAX],dist[MAX];
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

        void addEdge(int u, int v, int cap, int cost){
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
                int cost = pq.top().first;
                pq.pop();
                if(dist[u]<cost)continue;

                for(int id:graph[u]){
                    edge &v = edges[id];
                    if(v.cap<=v.flow)continue;
                    int newCost = cost + v.cost + h[v.u] - h[v.v];
                    if(newCost<dist[v.v]){
                        dist[v.v]=newCost;
                        parent[v.v]=id;
                        pq.push({dist[v.v],v.v});
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

            int flow=0,cost=0;
            int tmpCost=0;

            while(dijkstra()){
                int min_flow=INT_MAX;
                int cur,id;
                tmpCost=0;

                cur=T;
                do{
                    id=parent[cur];
                    edge &edgeID = edges[id];
                    min_flow=min(min_flow,edgeID.cap-edgeID.flow);
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

int grid[105][105];
int offset;
int m,n;

inline int id(int i, int j){
    return m*(i-1)+j;
}

inline void Solve(int Case){

    sii(n,m);
    offset = id(n,m)+1;
    int source = id(1,1);
    int sink = id(n,m)+offset;
    mcmf::init(offset*2+2,source,sink);

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){

            si(grid[i][j]);
            int idij=id(i,j);
            if(idij==source || idij+offset==sink)mcmf::addEdge(idij,idij+offset,2,0);
            else mcmf::addEdge(idij, idij+offset, 1, -grid[i][j]);

            if(i+1<=n)mcmf::addEdge(idij+offset, id(i+1,j), 1, 0);
            if(j+1<=m)mcmf::addEdge(idij+offset, id(i,j+1), 1, 0);
        }
    }

    printf("Case %d: %d\n", Case, -mcmf::MincostMaxflow(source,sink).first + grid[1][1] + grid[n][m]);
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
