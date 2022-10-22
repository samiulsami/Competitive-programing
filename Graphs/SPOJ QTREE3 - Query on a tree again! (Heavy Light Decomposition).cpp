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
int cost[N]={0};

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    int Tree[N<<1];

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);
    void tree_update(int ind, int val);
    int tree_query(int l, int r);

    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        for(int i=0,lim=n<<1; i<lim; i++)Tree[i]=0;

    }

    inline int Merge(int x, int y){///Segtree Combiner
        return x+y;
    }

    void update(int u, int val=1){///Update node u
        tree_update(posInChain[u],val);
    }

    int query(int u, int v){///Query the path from node u to v
        int topChain=-1,ind=-1;
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            int val = tree_query(posInChain[chainRoot[u]], posInChain[u]);
            if(val>0){
                topChain=posInChain[chainRoot[u]];
                ind = posInChain[u];
            }
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);

        if(tree_query(u,v)>0){
            topChain = u;
            ind = v;
        }
        if(topChain==-1)return -1;

        int low=topChain,high=ind,mid,ans=1e9;
        while(low<=high){
            mid = (low+high)>>1;
            if(tree_query(topChain, mid)>0){
                high=mid-1;
                ans=min(ans,mid);
            }
            else low=mid+1;
        }

        if(ans==1e9)return -1;
        return chainArr[ans];
    }

    int dfs(int u, int p){
        parent[u]=p;
        int ret=1, mx=0,nxt=-1,subtreeSize;
        for(int v:graph[u]){
            if(v==p)continue;
            lvl[v]=lvl[u]+1;
            subtreeSize=dfs(v,u);
            ret+=subtreeSize;
            if(subtreeSize>mx){
                mx=subtreeSize;
                nxt=v;
            }
        }
        maxSubtree[u]=nxt;
        return ret;
    }

    void hld(int u, int p, int chainParent){
        chainRoot[u]=chainParent;
        posInChain[u]=++posCnt;
        chainArr[posCnt]=u;

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
    }

    void tree_update(int ind, int val){
        ind+=n-1;
        Tree[ind]^=1;
        for(;ind>1; ind>>=1)Tree[ind>>1] = Merge(Tree[ind],Tree[ind^1]);
    }

    int tree_query(int l, int r){
        if(l>r)return 0;
        l+=n-1;
        r+=n;
        int ret=0;
        for(;l<r; l>>=1,r>>=1){
            if(l&1)ret=Merge(ret,Tree[l++]);
            if(r&1)ret=Merge(ret,Tree[--r]);
        }
        return ret;
    }
}

inline void Solve(int Case){
    int n,q;
    sii(n,q);
    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HLD::init(n,1);
    int x,y;
    while(q--){
        sii(x,y);
        if(x==0)HLD::update(y);
        else pf("%d\n",HLD::query(1,y));
    }

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
