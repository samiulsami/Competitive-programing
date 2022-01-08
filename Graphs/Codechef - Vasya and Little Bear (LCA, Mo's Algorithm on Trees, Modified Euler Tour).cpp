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
const int N = 1e5+5;

vector<int>graph[N];
int dTime[N];
int eTime[N];
int euler[N+N];
int lvl[N]={0};
int Time=0;
ll color[N];
ll val[N];
int n;

namespace LCA{
    int Table[20][N];
    int LOG;
    void dfs(int u, int p);

    void init(){
        memset(Table,-1,sizeof(Table));
        dfs(1,-1);
        LOG = ceil(log2(n))+1;
        for(int i=1; i<LOG; i++){
            for(int j=1; j<=n; j++){
                if(Table[i-1][j]!=-1){
                    Table[i][j] = Table[i-1][Table[i-1][j]];
                }
            }
        }
    }

    void dfs(int u, int p){
        dTime[u]=++Time;
        euler[Time]=u;
        Table[0][u]=p;
        for(int v:graph[u]){
            if(v!=p){
                    lvl[v]=lvl[u]+1;
                    dfs(v,u);
            }
        }
        euler[++Time]=u;
        eTime[u]=Time;
    }

    int lca(int u, int v){
        if(lvl[u]!=lvl[v]){
            if(lvl[v]<lvl[u])swap(u,v);
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
}

struct query{
    int i,l,r,L,x;
    query(){}
    query(int i, int l, int r, int L):i(i),l(l),r(r),L(L){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return (x&1)?r<q.r:r>q.r;
    }
}queries[N];
ll ans[N];
bool vis[N]={0};
deque<int>dq[12];
ll colorSum[12]={0};

inline void AddR(int x){
    int curColor=color[x];
    if(dq[curColor].empty())dq[curColor].push_back(x);
    else{
        int top=dq[curColor].back();
        colorSum[curColor] += (val[x]-val[top])*(val[x]-val[top]);
        dq[curColor].push_back(x);
    }
}

inline void AddL(int x){
    int curColor=color[x];
    if(dq[curColor].empty())dq[curColor].push_front(x);
    else{
        int top=dq[curColor].front();
        colorSum[curColor] += (val[x]-val[top])*(val[x]-val[top]);
        dq[curColor].push_front(x);
    }
}

inline void RemR(int x){
    int curColor=color[x];
    dq[curColor].pop_back();
    if(!dq[curColor].empty()){
        int top = dq[curColor].back();
        colorSum[curColor] -= (val[x]-val[top])*(val[x]-val[top]);
    }
}

inline void RemL(int x){
    int curColor=color[x];
    dq[curColor].pop_front();
    if(!dq[curColor].empty()){
        int top = dq[curColor].front();
        colorSum[curColor] -= (val[x]-val[top])*(val[x]-val[top]);
    }
}

inline ll getAns(int x){
    ll ret=0;
    for(int i=0; i<=10; i++){
        if(i==x)continue;
        ret+=colorSum[i];
    }
    return ret;
}

inline void checkR(int x){
    x=euler[x];
    if(vis[x])RemR(x);
    else AddR(x);
    vis[x]^=1;
}

inline void checkL(int x){
    x=euler[x];
    if(vis[x])RemL(x);
    else AddL(x);
    vis[x]^=1;
}

inline void Solve(int Case){
    si(n);
    FOR(i,n)sl(color[i+1]);
    FOR(i,n)sl(val[i+1]);
    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    LCA::init();
    int q;
    si(q);
    for(int i=0,u,v; i<q; i++){
        sii(u,v);
       // dbug(LCA::lca(u,v));
        if(dTime[u]>dTime[v])swap(u,v);
        int L=LCA::lca(u,v);
        if(u==L){
            u=dTime[u];
            v=dTime[v];
        }
        else{
            u=eTime[u];
            v=dTime[v];
        }
        queries[i] = query(i,u,v,L);
        queries[i].x = u/400;
    }
    sort(queries,queries+q);

    int l=1,r=0;
    for(int i=0; i<q; i++){
        while(r<queries[i].r)checkR(++r);
        while(l>queries[i].l)checkL(--l);
        while(r>queries[i].r)checkR(r--);
        while(l<queries[i].l)checkL(l++);
        ans[queries[i].i]=getAns(color[queries[i].L]);
    }

    for(int i=0; i<q; i++)pf("%lld\n",ans[i]);
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
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
