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
const int INF=1e8+1;

int lvl[N];
int Table[20][N];
int LOG;
int dist[N];
int cnt[N];
vector<pii>graph[N];
bool vis[N];
vector<int>dominator[N];
vector<int>dag[N];
vector<int>parents[N];
stack<int>toposort;

void dfs(int u){
    vis[u]=1;
    for(int v:dag[u]){
        if(!vis[v]){
            dfs(v);
        }
    }
    toposort.push(u);
}

void dfs2(int u, int p){
    cnt[u]=1;
    for(int v:dominator[u]){
        if(v!=p){
            dfs2(v,u);
            cnt[u]+=cnt[v];
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
        if(Table[i][u]!=Table[i][v]){
            u=Table[i][u];
            v=Table[i][v];
        }
    }

    return Table[0][u];
}

void resetAll(int n){
    while(!toposort.empty())toposort.pop();
    for(int i=0; i<=n; i++){
            dist[i]=INF;
            vis[i]=0;
            dominator[i].clear();
            dag[i].clear();
            graph[i].clear();
            parents[i].clear();
            for(int j=0; j<=LOG; j++)Table[j][i]=-1;
            cnt[i]=0;
    }
}

inline void Solve(int Case){
    int n,m;
    sii(n,m);

    LOG = ceil(log2(n))+1;
    resetAll(n);
    for(int i=0,u,v,w; i<m; i++){
        siii(u,v,w);
        graph[u].push_back(pii(w,v));
        graph[v].push_back(pii(w,u));
    }

    priority_queue<pii, vector<pii>, greater<pii> >pq;
    dist[0]=0;
    pq.push(pii(0,0));

    ///Make DAG
    while(!pq.empty()){
        pii top = pq.top();
        pq.pop();
        int u=top.ss;
        int u_cst=top.ff;


        for(pii e:graph[u]){
            int v=e.ss;
            int v_cst=e.ff;

            if(dist[v]>u_cst+v_cst){
                dist[v]=u_cst+v_cst;
                pq.push(pii(dist[v],v));
                parents[v].clear();
                parents[v].push_back(u);
            }
            else if(dist[v]==u_cst+v_cst){
                parents[v].push_back(u);
            }
        }
    }

    for(int u=0; u<n; u++){
        for(int v:parents[u]){
            dag[v].push_back(u);
        }
    }
    ///Make Dominator Tree
    lvl[0]=0;
    dfs(0);
    toposort.pop();
    while(!toposort.empty()){
        int u=toposort.top();
        toposort.pop();

        int p=parents[u][0];
        for(int i=1; i<sz(parents[u]); i++)
                p=lca(p,parents[u][i]);

        dominator[p].push_back(u);
        lvl[u]=lvl[p]+1;
        Table[0][u]=p;

        for(int i=1; i<LOG; i++){
            if(Table[i-1][u]!=-1){
                Table[i][u] = Table[i-1][Table[i-1][u]];
            }
        }
    }

    dfs2(0,0);
    int q,k;
    si(q);

    pf("Case %d:\n",Case);
    while(q--){
        si(k);
        int L=-1;
        for(int i=0,u; i<k; i++){
            si(u);
            if(dist[u]<INF){
                if(L==-1)L=u;
                else L=lca(L,u);
            }
        }

        if(L==-1)pf("0\n");
        else pf("%d %d\n",lvl[L]+1,cnt[L]);
    }

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
