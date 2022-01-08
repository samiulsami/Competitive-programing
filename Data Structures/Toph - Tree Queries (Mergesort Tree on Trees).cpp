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
const int N = 5e5+5;
int discoveryTime[N]={0};
int Time=0;
int subtreeMax[N]={0};
pii vertexVal[N];
vector<int>graph[N];
vector<int> Tree[4*N];

void Merge(vi &ret, vi &L, vi &R){
    int i=0,j=0,limL=sz(L),limR=sz(R);
    int total=limL+limR;
    ret.resize(total);
    for(int k=0; k<total; k++){
        if(i==limL)ret[k]=R[j++];
        else if(j==limR)ret[k]=L[i++];
        else{
            if(L[i]>R[j])ret[k]=L[i++];
            else ret[k]=R[j++];
        }
    }
}

void build(int node, int l, int r){
    if(l==r)Tree[node].push_back(vertexVal[l].second);
    else{
        int mid = (l+r)>>1;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Merge(Tree[node], Tree[node*2], Tree[node*2+1]);
    }
}

int query(int node, int l, int r, int posl, int posr, int k){
    if(l>r || r<posl || l>posr)return 0;
    if(l>=posl && r<=posr){
        int low=0,high=sz(Tree[node])-1,mid,cur=-1;
        while(low<=high){
            mid=(low+high)>>1;
            if(Tree[node][mid]>=k){
                cur=max(cur,mid);
                low=mid+1;
            }
            else high=mid-1;
        }
        return cur+1;
    }
    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr, k) + query(node*2+1, mid+1, r, posl, posr, k);
}

int dfs(int u, int p){
    subtreeMax[u]=discoveryTime[u]=++Time;
    for(int v:graph[u]){
        if(v==p)continue;
        subtreeMax[u]=max(subtreeMax[u],dfs(v,u));
    }
    return subtreeMax[u];
}

inline void Solve(int Case){
    int n,m;
    sii(n,m);
    for(int i=2,u; i<=n; i++){
        si(u);
        graph[u].push_back(i);
    }

    for(int i=1; i<=n; i++)
        si(vertexVal[i].second);

    dfs(1,1);
    for(int i=1; i<=n; i++)
        vertexVal[i].first=discoveryTime[i];

    sort(vertexVal+1, vertexVal+n+1);

    build(1,1,n);

    int v,x;
    while(m--){
        sii(v,x);
        pf("%d\n",query(1,1,n,discoveryTime[v],subtreeMax[v],x));
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
