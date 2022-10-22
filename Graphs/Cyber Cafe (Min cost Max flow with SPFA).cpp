#include<bits/stdc++.h>
/*
    problem: LightOJ 1237 - Cyber Cafe
    verdict: AC
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
#define dbug(x) cout<<"dbug: "<<x<<endl
#define eikhane cout<<"Eikhane"<<endl

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

namespace mcmf{

        struct edge{
            int u,v;
            int cap, flow, cost;
            edge(){}
            edge(int u, int v, int cap, int cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        const int MAX = 110;
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

int Entry[55],Exit[55];

inline ll calc(ll a, ll b, ll k){
    ll ret = max(a,b)-min(a,b)-k;
    return ret*ret;
}

inline void Solve(int Case){
    int n,k,g;
    siii(n,k,g);

    FOR(i,n-1)si(Entry[i]);
    FOR(i,n-1)si(Exit[i]);

    mcmf::init(2*n+5);
    int source = 2*n+1;
    int sink = source+1;

    for(int i=0; i<n; i++){
        mcmf::addEdge(source,i,1,0);

        for(int j=0; j<n; j++){
            if(Entry[i]>=Exit[j])continue;
            //pf("edge: %d - %d, cost: %lld\n",Entry[i],Exit[j],min(calc(Entry[i],Exit[j],k),1LL*g));
            mcmf::addEdge(i,j+n,1,(int)min(calc(Entry[i],Exit[j],k),1LL*g));
        }

        mcmf::addEdge(i+n,sink,1,0);
    }

    bool pos=1;
    ll val1,val2;

    pii ans = mcmf::MincostMaxflow(source,sink);
    if(ans.second!=n)pos=0;
    val1 = ans.first;
    //dbug(ans);

    for(int i=0; i<mcmf::edge_cnt; i++){
        mcmf::edges[i].flow=0;
        mcmf::edges[i].cost*=-1;
    }

    pii ans2 = mcmf::MincostMaxflow(source,sink);

    if(ans2.second!=n)pos=0;
    val2 = ans2.first*(-1LL);
    //dbug(ans2);

    pf("Case %d: ",Case);
    if(pos)pf("%lld %lld\n",val1,val2);
    else pf("impossible\n");
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
