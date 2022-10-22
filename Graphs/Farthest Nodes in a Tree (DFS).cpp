#include<bits/stdc++.h>

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

const int MAX = 3e5+5;
const double PI = 2*acos(0.0);

vector<pii>graph[MAX];
int L[MAX],R[MAX];
int dist[MAX];
bool vis[MAX];

void reset(int n){
    FOR(n-1){
        dist[i]=0;
        vis[i]=0;
    }
}

void dfs1(int u, int &cost, int &x){
    vis[u]=1;
    for(pii v:graph[u]){
        if(vis[v.yy])continue;
        dist[v.yy]=dist[u]+v.xx;

        if(dist[v.yy]>cost){
            cost=dist[v.yy];
            x=v.yy;
        }
        dfs1(v.yy,cost,x);
    }
}

inline void Solve(int Case){
    int n;
    si(n);
    FOR(n){
        graph[i].clear();
    }
    for(int i=0; i<n-1; i++){
        int u,v,cst;
        siii(u,v,cst);
        graph[u].push_back({cst,v});
        graph[v].push_back({cst,u});
    }

    int fst=0,snd=0,cost=0;
    reset(n);
    dfs1(0,cost,fst);

    reset(n);
    cost=0;
    dfs1(fst,cost,snd);

    int ans=0;
    FOR(n-1)ans=max(ans,dist[i]);

    pf("Case %d: %d\n",Case,ans);
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
