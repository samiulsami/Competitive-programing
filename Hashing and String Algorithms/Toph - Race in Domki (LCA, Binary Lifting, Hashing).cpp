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
const int N = 2e5+5;

const int MOD=(1LL<<31)-1;
const int base = 1832;
int P[N];
vector<int>graph[N];
int cost[N];

inline int mod(ll x) {
    if(x<MOD)return x;
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}

namespace asdfgh{
    int parent[N],lvl[N];
    int Table[20][N];
    int hashTable[20][N];
    int hashTableR[20][N];
    ll xorTable[20][N];
    int n;
    int LOG;

    void dfs(int u, int p){
        parent[u]=p;
        for(int v:graph[u]){
            if(v==p)continue;
            lvl[v]=lvl[u]+1;
            Table[0][v]=u;
            dfs(v,u);
        }
    }

    void init(int x, int root=1){
        n=x;
        lvl[root]=0;
        dfs(root,root);
        LOG = ceil(log2(n))+1;
        for(int i=1; i<=n; i++){
            hashTable[0][i]=hashTableR[0][i]=cost[i];
            xorTable[0][i] = (1LL<<cost[i]);
        }
        Table[0][root]=-1;

        for(int i=1; i<LOG; i++){
            for(int j=1; j<=n; j++){
                if(Table[i-1][j]!=-1){
                        Table[i][j] = Table[i-1][Table[i-1][j]];
                        xorTable[i][j] = xorTable[i-1][j]^xorTable[i-1][Table[i-1][j]];

                        int down = hashTable[i-1][j];
                        int top = hashTable[i-1][Table[i-1][j]];
                        int mul = P[1<<(i-1)];
                        hashTable[i][j] = mod(1LL*down + 1LL*mul*top);

                        down = hashTableR[i-1][j];
                        top = hashTableR[i-1][Table[i-1][j]];
                        hashTableR[i][j] = mod(1LL*top + 1LL*mul*down);
                }
                else{
                    Table[i][j]=-1;
                    xorTable[i][j]=hashTable[i][j]=hashTableR[i][j]=0;
                }
            }
        }
    }

    int pathHash(int u, int v, int L){
        int d1 = lvl[u]-lvl[L]+1;
        int d2 = lvl[v]-lvl[L];
        int lefth=0,cntleft=0;
        int righth=0;

        for(int i=LOG-1; i>=0; i--){
            int j=(1<<i);
            if(j<=d1){
                lefth = mod(1LL*lefth + 1LL*P[cntleft]*hashTable[i][u]);
                u=Table[i][u];
                cntleft+=j;
                d1-=j;
            }
        }

        for(int i=LOG-1; i>=0; i--){
            int j=(1<<i);
            if(j<=d2){
                righth = mod(1LL*righth*P[j] + 1LL*hashTableR[i][v]);
                v=Table[i][v];
                d2-=j;
            }
        }

        int h = mod(1LL*lefth + mod(1LL*P[cntleft]*righth));
        return h;
    }

    ll pathXor(int u, int v, int L){
        int d1 = lvl[u]-lvl[L]+1;
        int d2 = lvl[v]-lvl[L];
        ll ret=0;

        for(int i=LOG-1; i>=0; i--){
            int j=(1<<i);
            if(j<=d1){
                ret^=xorTable[i][u];
                u=Table[i][u];
                d1-=j;
            }
        }

        for(int i=LOG-1; i>=0; i--){
            int j=(1<<i);
            if(j<=d2){
                ret^=xorTable[i][v];
                v=Table[i][v];
                d2-=j;
            }
        }
        return ret;
    }

    int LCA(int u, int v){
        if(lvl[u]!=lvl[v]){
            if(lvl[v]<lvl[u])swap(u,v);
            for(int i=LOG-1; i>=0; i--){
                if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u])v=Table[i][v];
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

    bool query1(int u, int v){///check if palindrome can be formed
        return __builtin_popcountll(pathXor(u,v,LCA(u,v)))<=1;
    }

    bool query2(int u, int v){///check if path is palindrome
        int L = LCA(u,v);
        if(pathHash(u,v,L)==pathHash(v,u,L))return 1;
        return 0;
    }

    bool query3(int u, int v, int x, int y){/// check if paths are identical
        int L1=LCA(u,v);
        int L2=LCA(x,y);
        if(pathHash(u,v,L1)==pathHash(x,y,L2))return 1;
        return 0;
    }
}

inline void Solve(int Case){
    int n;
    si(n);
    for(int i=1; i<=n; i++)si(cost[i]);

    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    asdfgh::init(n,1);
    int q,qt,a,b,c,d;

    si(q);
    pf("Case %d:\n",Case);
    while(q--){
        si(qt);
        bool flag;
        if(qt==1){
            sii(a,b);
            flag=asdfgh::query1(a,b);
        }
        else if(qt==2){
            sii(a,b);
            flag=asdfgh::query2(a,b);
        }
        else{
            sii(a,b);
            sii(c,d);
            flag=asdfgh::query3(a,b,c,d);
        }
        if(flag)pf("YES\n");
        else pf("NO\n");
    }

    for(int i=0; i<=n+1; i++)graph[i].clear();

}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
    P[0]=1;
    for(int j=1; j<=200001; j++)P[j] = mod(1LL*P[j-1]*base);

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
