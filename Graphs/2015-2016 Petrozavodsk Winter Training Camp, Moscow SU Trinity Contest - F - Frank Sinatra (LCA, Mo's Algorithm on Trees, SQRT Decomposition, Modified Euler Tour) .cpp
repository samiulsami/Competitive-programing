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
const int Div = 400;
const int Div2 = 320;

vector<int>graph[N];
int dTime[N],eTime[N],euler[N+N];
int lvl[N]={0};
int Time=0;
int cost[N]={0};
int BlockSum[Div2+5]={0};

struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>lgVal;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time1=0;

    LCA(int n, int root=1):n(n),lgVal(1+n<<1){
        lvl[root]=0;
        for(int i=2,lim=n+n; i<=lim; i++)lgVal[i]=lgVal[(i>>1)]+1;
        LOG = lgVal[n]+2;
        sparseTable.resize(LOG, vector<int>(1+n<<1));
        dfs(root,-1);
        for(int i=1; i<LOG; i++){
            for(int j=1; j+(1<<i)-1<=Time1; j++){
                int left=sparseTable[i-1][j];
                int right=sparseTable[i-1][j+(1<<(i-1))];
                if(lvl[left]<lvl[right])sparseTable[i][j] = left;
                else sparseTable[i][j] = right;
            }
        }
    }

    void dfs(int u, int p){
        dTime[u]=++Time;
        sparseTable[0][++Time1]=u;
        euler[Time]=u;
        for(int v:graph[u]){
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time1]=u;
            }
        }
        eTime[u]=++Time;
        euler[Time]=u;
    }

    inline int lca(int u, int v){
        u=dTime[u];
        v=dTime[v];
        if(u>v)swap(u,v);
        int logVal = lgVal[v-u+1];
        int x=sparseTable[logVal][u];
        int y=sparseTable[logVal][v-(1<<logVal)+1];
        if(lvl[x]<lvl[y])return x;
        return y;
    }
};

struct query{
    int i,l,r,x;
    query(){}
    query(int i, int l, int r):i(i),l(l),r(r){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return (x&1)?r<q.r:r>q.r;
    }
}queries[int(1e5+5)];
int ans[int(1e5+5)];
bool vis[N]={0};
int costCnt[N]={0};

inline void Add(int x){
    x=euler[x];
    if(cost[x]==-1 || cost[x]>=100002)return;
    if(vis[x]==0){
        vis[x]=1;
        if(++costCnt[cost[x]]==1)BlockSum[cost[x]/Div2]++;
    }
    else{
        vis[x]=0;
        if(--costCnt[cost[x]]==0)BlockSum[cost[x]/Div2]--;
    }
}

inline int Find(){
    int offset=0;
    for(int i=0; i<Div2; i++){
        if(BlockSum[i]!=Div2){
            offset = i*Div2;
            break;
        }
    }

    for(int i=0; i<Div2;i++){
        if(costCnt[i+offset]==0)return i+offset;
    }
    return 1e8;
}

inline void Solve(int Case){
    int n,q;
    sii(n,q);
    int nodeCnt=n;
    for(int i=1,u,v,c; i<n; i++){
        siii(u,v,c);
        nodeCnt++;
        graph[u].push_back(nodeCnt);
        graph[v].push_back(nodeCnt);
        graph[nodeCnt].push_back(v);
        graph[nodeCnt].push_back(u);
        cost[u]=cost[v]=-1;
        cost[nodeCnt]=c;
    }
    LCA lca(n+n-1,1);

    for(int i=0,u,v,L; i<q; i++){
        sii(u,v);
        if(dTime[u]>dTime[v])swap(u,v);
        L=lca.lca(u,v);
        if(u==L){
            u=dTime[u];
            v=dTime[v];
        }
        else{
            u=eTime[u];
            v=dTime[v];
        }
        queries[i]=query(i,u,v);
        queries[i].x=u/Div;
    }
    sort(queries,queries+q);

    int l=1,r=0;
    for(int i=0; i<q; i++){
        while(r<queries[i].r)Add(++r);
        while(l>queries[i].l)Add(--l);
        while(r>queries[i].r)Add(r--);
        while(l<queries[i].l)Add(l++);

        ans[queries[i].i]=Find();
    }

    for(int i=0; i<q; i++)pf("%d\n",ans[i]);
}

/**
7 1
2 1 1
3 1 2
1 4 0
4 5 1
5 6 3
5 7 4
3 5
*/

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
