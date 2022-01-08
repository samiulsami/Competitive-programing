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
const int N = 3e4+5;

vector<vector<int> >graph;
int dTime[N],eTime[N],euler[N+N];
int Time1;
int arr[N];
int lgVal[N+N]={0};

struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>discoveryTime,lvl;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(int n, int root=1):n(n),discoveryTime(n+1),lvl(n+1){
        lvl[root]=0;
        Time=0;
        Time1=0;
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
        dTime[u]=++Time1;
        euler[Time1]=u;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
        eTime[u]=++Time1;
        euler[Time1]=u;
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
};

template<typename T>
struct segTree{
    vector<T>Tree;
    int n;
    segTree(){}
    segTree(int n):n(n),Tree(4*n){}

    inline T Combine(T a, T b){
        return a+b;
    }

    inline void update(int pos, T val){update(1,1,n,pos,val);}
    void update(int node, int l, int r, int pos, T val){
        if(l>r || l>pos || r<pos)return;
        if(l==pos && r==pos)Tree[node]=val;
        else{
            int mid = (l+r)>>1;
            if(pos<=mid)update(node*2, l, mid, pos, val);
            else update(node*2+1, mid+1, r, pos, val);
            Tree[node] = Combine(Tree[node*2], Tree[node*2+1]);
        }
    }

    inline T query(int posl, int posr){return query(1,1,n,posl,posr);}
    T query(int node, int l, int r, int posl, int posr){
        if(l>posr || r<posl || l>r)return 0;
        if(l>=posl && r<=posr)return Tree[node];
        int mid = (l+r)>>1;
        return Combine(query(node*2, l, mid, posl, posr), query(node*2+1, mid+1, r, posl, posr));
    }
};


inline void Solve(int Case){

    int n;
    si(n);
    graph.clear();
    graph.assign(n+5,vector<int>());
    for(int i=1,x; i<=n; i++)si(arr[i]);

    for(int i=0,u,v; i<n-1; i++){
        sii(u,v);
        u++;
        v++;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    LCA lca(n,1);
    segTree<int> st(n+n);

    for(int i=1; i<=n; i++){
        st.update(dTime[i],arr[i]);
        st.update(eTime[i],-arr[i]);
    }

    int q,u,v,qt;
    si(q);
    pf("Case %d:\n",Case);
    while(q--){
        si(qt);
        if(qt==0){
            sii(u,v);
            u++;
            v++;
            if(dTime[u]>dTime[v])swap(u,v);
            int L = lca.lca(u,v);

            if(u==L)pf("%d\n",st.query(dTime[L],dTime[v]));
            else{
                int ans = st.query(dTime[L],dTime[u]) + st.query(dTime[L],dTime[v]) - arr[L];
                pf("%d\n",ans);
            }
        }
        else{
            sii(u,v);
            u++;
            st.update(dTime[u],v);
            st.update(eTime[u],-v);
            arr[u]=v;
        }

    }
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
    lgVal[2]=1;
    for(int i=2; i<=60002; i++)lgVal[i]=lgVal[i>>1]+1;

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
