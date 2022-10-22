#include<bits/stdc++.h>
/*
    Problem: LightOJ 1177 - Angry Programmer
    Verdict: AC
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

const int MAX = 1e5+5;
const double PI = 2*acos(0.0);

namespace Dinic{

        struct edge{
            int u,v;
            int cap, flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        const int MAX=105;

        vector<edge>edges;
        vector<int> graph[MAX];
        int lvl[MAX],nxt[MAX];
        int n,edge_cnt,S,T;

        void init(int nn, int SS=0, int TT=0){
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

inline void Solve(int Case){
    int n,source,sink,m;
    sii(n,m);
    Dinic::init(2*n+3,0,n-1);
    source = 1;
    sink = n*2;

    Dinic::addEdge(1,1+n,INT_MAX);
    Dinic::addEdge(n,n+n,INT_MAX);

    for(int i=2; i<=n-1; i++){
        int c;
        si(c);
        Dinic::addEdge(i,i+n,c);
    }

    for(int i=0; i<m; i++){
        int u,v,c;
        siii(u,v,c);
        Dinic::addEdge(u+n,v,c);
        Dinic::addEdge(v+n,u,c);
    }

    pf("Case %d: %d\n",Case,Dinic::maxFlow(source,sink));
}

  #define Multiple_Test_Cases
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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
