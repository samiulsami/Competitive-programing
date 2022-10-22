#include<bits/stdc++.h>
/*
    Problem: LightOJ 1379 - Toll Management
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
const int MAX = 1e4+5;

int dist[2][MAX];
int n,m;
vector<pii>graph1[MAX],graph2[MAX];

inline void dijkstra(bool s, int S, vector<pii> *graph){
    for(int i=0; i<n; i++)dist[s][i]=-1;
    dist[s][S]=0;

    priority_queue<pii, vector<pii>, greater<pii> >pq;
    pq.push({0,S});
    while(!pq.empty()){
        pii top = pq.top();
        pq.pop();
        int u = top.second;
        int cst = top.first;
        //if(dist[s][u]<cst)continue;

        for(pii e:graph[u]){
            int v = e.second;
            int v_cst = e.first;
            if(dist[s][v]==-1 || dist[s][v]>dist[s][u]+v_cst){
                dist[s][v]=dist[s][u]+v_cst;
                pq.push({dist[s][v],v});
            }
        }
    }
}

inline void Solve(int Case){
    sii(n,m);
    int s,t,p;
    FOR(i,n-1){
        graph1[i].clear();
        graph2[i].clear();
    }
    siii(s,t,p);
    s--;
    t--;
    int u,v,c;
    //vector<pii>edges;
    FOR(i,m-1){
        siii(u,v,c);
        u--;
        v--;
        //edges.pb({u,v});
        graph1[u].pb({c,v});
        graph2[v].pb({c,u});
    }
    dijkstra(0,s,graph1);
    dijkstra(1,t,graph2);
    int mx=-1;

    if(dist[0][t]!=-1 && dist[0][t]<=p){
        FOR(u,n-1){
            for(pii e:graph1[u]){
                int v = e.second;
                if(dist[0][u]==-1 || dist[1][v]==-1)continue;
                if(dist[0][u]+e.first+dist[1][v]<=p)mx=max(mx,e.first);
            }
        }
    }

    pf("Case %d: %d\n",Case, mx);
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
