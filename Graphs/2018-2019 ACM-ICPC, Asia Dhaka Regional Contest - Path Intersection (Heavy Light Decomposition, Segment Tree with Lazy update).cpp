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

vector<int>graph[N];

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int n,posCnt;

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);

    struct data{
        int mx,cnt,lazy;
        data(){mx=lazy=0;cnt=1;}
        data(int mx, int cnt, int lazy):mx(mx),cnt(cnt),lazy(lazy){}
    }Tree[N<<2];

    inline data Merge(data a, data b){
        if(a.mx==b.mx)return data(a.mx, a.cnt+b.cnt, 0);
        if(a.mx<b.mx)return b;
        return a;
    }

    void build(int node, int l, int r){
        if(l==r)Tree[node] = data(0,1,0);
        else{
            int mid = (l+r)>>1;
            build(node*2,l,mid);
            build(node*2+1,mid+1,r);
            Tree[node] = Merge(Tree[node*2], Tree[node*2+1]);
        }
    }

    inline void push_update(int node, int l, int r){
        if(Tree[node].lazy!=0){
            Tree[node].mx+=Tree[node].lazy;
            if(l!=r){
                Tree[node*2].lazy+=Tree[node].lazy;
                Tree[node*2+1].lazy+=Tree[node].lazy;
            }
            Tree[node].lazy=0;
        }
    }

    void tree_update(int node, int l, int r, int posl, int posr, int val){
        push_update(node,l,r);
        if(l>r || posl>r || posr<l)return;
        if(l>=posl && r<=posr){
            Tree[node].lazy+=val;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            tree_update(node*2, l, mid, posl, posr, val);
            tree_update(node*2+1, mid+1, r, posl, posr, val);
            Tree[node] = Merge(Tree[node*2], Tree[node*2+1]);
        }
    }

    data tree_query(int node, int l, int r, int posl, int posr){
        push_update(node,l,r);
        if(l>r || posl>r || posr<l)return data(0,0,0);
        if(l>=posl && r<=posr)return Tree[node];
        int mid = (l+r)>>1;
        return Merge(tree_query(node*2, l, mid, posl, posr), tree_query(node*2+1, mid+1, r, posl, posr));
    }


    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        build(1,1,posCnt);
    }

    void addPath(int u, int v, int val){
        int ret=0;
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            tree_update(1,1,posCnt,posInChain[chainRoot[u]], posInChain[u], val);
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        tree_update(1,1,posCnt,u,v,val);
    }

    int getAns(int k){
        if(Tree[1].mx==k)return Tree[1].cnt;
        return 0;
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

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
    }

}


inline void Solve(int Case){
    int n;
    si(n);
    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HLD::init(n,1);
    int q,k,l,r;
    vector<pii>paths;
    si(q);
    pf("Case %d:\n",Case);

    while(q--){
        si(k);
        paths.clear();
        for(int i=0; i<k; i++){
            sii(l,r);
            paths.emplace_back(pii(l,r));
            HLD::addPath(l,r,1);
        }
        pf("%d\n",HLD::getAns(k));
        for(pii &x:paths)HLD::addPath(x.ff,x.ss,-1);

    }

    for(int i=0; i<=n+1; i++)graph[i].clear();

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
