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
const int N = 2e5+5;

vi graph[N];
vi Tree[N];
int dTime[N];
int lgVal[N+N];
int Time=0;
bool cutEdge[N+N];
pii edges[N+N];
int parent[N];

void resetALL(int n){
    Time=0;
    for(int i=0; i<=n; i++){
        parent[i]=i;
        Tree[i].clear();
        graph[i].clear();
        dTime[i]=0;
    }
}

int tarjan_bcc(int u, int p){
    int low=dTime[u]=++Time;
    for(int e:graph[u]){
        int v=edges[e].second;
        if(v==p)continue;
        else if(dTime[v])low=min(low,dTime[v]);
        else{
            int subtreeMin = tarjan_bcc(v,u);
            low=min(low,subtreeMin);
            if(subtreeMin>dTime[u]){
                cutEdge[e]=1;
                cutEdge[e^1]=1;
            }
        }
    }
    return low;
}

int Find(int u){
    if(parent[u]==u)return u;
    return parent[u] = Find(parent[u]);
}

struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>discoveryTime,lvl;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(int n, int root):n(n+1),discoveryTime(n+1),lvl(n+1){
        lvl[root]=0;
        Time=0;
        LOG = lgVal[n]+2;
        sparseTable.resize(LOG, vector<int>(1+n<<1));
        dfs(root,-1);

        for(int i=1; i<LOG; i++){
            for(int j=1; j+(1<<i)-1<=Time; j++){
                int left=sparseTable[i-1][j];
                int right=sparseTable[i-1][j+(1<<(i-1))];
                if(lvl[left]<lvl[right])sparseTable[i][j] = left;
                else sparseTable[i][j] = right;
            }
        }
    }

    void dfs(int u, int p){
        discoveryTime[u]=++Time;
        sparseTable[0][Time]=u;
        for(int v:Tree[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
    }

    inline int lca(int u, int v){
        u=discoveryTime[u];
        v=discoveryTime[v];
        if(u>v)swap(u,v);
        int logVal = lgVal[v-u+1];
        int x=sparseTable[logVal][u];
        int y=sparseTable[logVal][v-(1<<logVal)+1];
        if(lvl[x]<lvl[y])return x;
        return y;
    }

    int dist(int u, int v){
        u=Find(u);
        v=Find(v);
        return lvl[u]+lvl[v] - 2*lvl[lca(u,v)];
    }
};




inline void Solve(int Case){
    int n,m;
    sii(n,m);
    for(int i=0; i<=m+m+1; i++)cutEdge[i]=0;
    resetALL(n);
    int edgeCnt=0;

    for(int i=0,u,v; i<m; i++){
        sii(u,v);
        edges[edgeCnt]=pii(u,v);
        edges[edgeCnt+1]=pii(v,u);
        graph[u].push_back(edgeCnt);
        graph[v].push_back(edgeCnt+1);
        edgeCnt+=2;
    }
    tarjan_bcc(1,1);

    for(int i=1; i<=n; i++){
        for(int e:graph[i]){
            int v=edges[e].second;
            if(!cutEdge[e] && !cutEdge[e^1]){
                    parent[Find(v)]=Find(i);
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int e:graph[i]){
            if(cutEdge[e])Tree[Find(i)].push_back(Find(edges[e].second));
        }
    }


    LCA lca(n,Find(1));

    int q,l,r;
    si(q);
    pf("Case %d:\n",Case);
    while(q--){
        sii(l,r);
        pf("%d\n",lca.dist(l,r));
    }
}
/**
1
5 5
1 2
2 3
3 1
2 4
3 5
100
*/


///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
    lgVal[0]=lgVal[1]=0;
    for(int i=2; i<=400005; i++)lgVal[i]=lgVal[i>>1]+1;
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
