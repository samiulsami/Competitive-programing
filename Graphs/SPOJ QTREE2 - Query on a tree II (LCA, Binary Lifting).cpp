#include<bits/stdc++.h>

using namespace std;
typedef int64_t ll;
typedef uint64_t ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define ff first
#define ss second
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"debug: "<<x<<"\n"
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define pb emplace_back
#define chk cerr<<"----------------\nCAME HERE\n----------------\n";
seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc(),
(uint64_t) (uintptr_t) make_unique<char>().get()};
mt19937 rng(seq);
mt19937_64 rng64(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}
template<typename T>inline bool MAX(T &a, T b){return b>a?a=b,1:0;}
template<typename T>inline bool MIN(T &a, T b){return b<a?a=b,1:0;}
inline bool checkBit(int n, int pos){return bool(n&(1<<pos));}
inline int setBit(int n, int pos){return n|(1<<pos);}
inline int toggleBit(int n, int pos){return n^(1<<pos);}
inline int readline(char *s, char d='\n'){int len=0;while((s[len]=getchar())!=d)len++;s[len]='\0';return len;}
ll modMul(ll a, ll b, ll MOD){ll ret=0;a%=MOD;while(b>0){if(b&1)ret=(ret+a)%MOD;b>>=1;a=(a<<1)%MOD;}return ret%MOD;}
ll bigMod(ll a, ll b, ll MOD){if(a==0)return 0;ll ret=1;a%=MOD;while(b>0){if(b&1)ret=(ret*a)%MOD;b>>=1;a=(a*a)%MOD;}return ret%MOD;}
ll lcm(ll a, ll b){return ((a/__gcd(a,b))*b);}
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int N = 1e4+5;

vector<pii>graph[N];

struct LCA{
    vector<int>lvl,cost;
    vector<vector<int>>Table;
    int n,LOG;

    LCA(int n, int root=1):n(n),lvl(n+1),cost(n+1){
        LOG = ceil(log2(n))+1;
        Table.assign(LOG, vector<int>(n+1,-1));
        dfs(root,-1);

        for(int i=1; i<LOG; i++){
            for(int j=1; j<=n; j++){
                if(Table[i-1][j]!=-1){
                    Table[i][j] = Table[i-1][Table[i-1][j]];
                }
            }
        }
    }

    void dfs(int u, int p){
        Table[0][u]=p;
        for(pii e:graph[u]){
            int v=e.second;
            if(v!=p){
                lvl[v]=lvl[u]+1;
                cost[v]=cost[u]+e.first;
                dfs(v,u);
            }
        }
    }

    int lca(int u, int v){
        if(lvl[u]!=lvl[v]){
            if(lvl[u]>lvl[v])swap(u,v);
            for(int i=LOG-1; i>=0; i--){
                if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u]){
                    v=Table[i][v];
                }
            }
        }
        if(u==v)return u;

        for(int i=LOG-1; i>=0; i--){
            if(Table[i][v]!=Table[i][u]){
                u=Table[i][u];
                v=Table[i][v];
            }
        }

        return Table[0][u];
    }

    int dist(int u, int v){
        return cost[u] + cost[v] - 2*cost[lca(u,v)];
    }

    int kth(int u, int v, int k){
        int L = lca(u,v);
        int distUtoL = lvl[u]-lvl[L]+1;
        int ret;

        if(distUtoL==k)return L;
        else if(distUtoL>k){
            k--;
            ret=u;
            for(int i=LOG-1; i>=0; i--){
                if(Table[i][ret]!=-1 && k-(1<<i)>=0){
                    ret=Table[i][ret];
                    k-=(1<<i);
                }
            }
        }
        else{
            k = k-distUtoL+1;
            k = (lvl[v]-lvl[L])-k+1;
            ret=v;
            for(int i=LOG-1; i>=0; i--){
                if(Table[i][ret]!=-1 && k-(1<<i)>=0){
                    ret=Table[i][ret];
                    k-=(1<<i);
                }
            }
        }

        return ret;
    }
};
/**
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 5 3
*/

inline void Solve(int Case){
    int n;
    si(n);
    for(int i=0; i<=n; i++)graph[i].clear();
    for(int i=1,a,b,c; i<n; i++){
        siii(a,b,c);
        graph[a].push_back({c,b});
        graph[b].push_back({c,a});
    }

    LCA lca(n);

    char q[10];
    int a,b,k;
    while(sf(" %s",&q)){
        if(q[0]=='K'){
            siii(a,b,k);
            pf("%d\n",lca.kth(a,b,k));
        }
        else if(q[0]=='D' && q[1]=='I'){
            sii(a,b);
            pf("%d\n",lca.dist(a,b));
        }
        else break;
    }

    nl;
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
    #ifdef fastio
        ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #endif
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        #ifdef fastio
            cin>>T;
        #else
            scanf("%d",&T);
        #endif
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
