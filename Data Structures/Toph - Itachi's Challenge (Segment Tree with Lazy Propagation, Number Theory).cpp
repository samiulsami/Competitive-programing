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

ll modMul(ll a, ll b){
    ll ret=0;
    if(b>a)swap(a,b);
    a%=MOD;
    while(b>0){
            if(b&1)ret=(ret+a)%MOD;
            b>>=1;
            a=(a<<1)%MOD;
    }
    return ret%MOD;
}

int arr[N];

template<typename T>
struct segTreeLazy{
    struct TreeNode{
        T data,lazy;
    };
    vector<TreeNode>Tree;
    int n;
    segTreeLazy(){}
    segTreeLazy(int n):n(n),Tree(4*n){}
    inline void build(){build(1,1,n);}
    void build(int node, int l, int r){
        if(l==r){
                Tree[node].data=arr[l-1];
                Tree[node].lazy=0;
        }
        else{
            int mid = (l+r)>>1;
            build(node*2,l,mid);
            build(node*2+1,mid+1,r);
            Tree[node].data = (Tree[node*2].data + Tree[node*2+1].data)%MOD;
        }
    }

    inline void push_update(int node, int l, int r){
        if(Tree[node].lazy!=0){
            Tree[node].data += (1LL*(r-l+1)*Tree[node].lazy)%MOD;
            Tree[node].data%=MOD;
            if(l!=r){
                Tree[node*2].lazy+=Tree[node].lazy;
                Tree[node*2].lazy%=MOD;
                Tree[node*2+1].lazy+=Tree[node].lazy;
                Tree[node*2+1].lazy%=MOD;
            }
            Tree[node].lazy=0;
        }
    }

    inline void range_update(int posl, int posr, T val){range_update(1,1,n,posl,posr,val);}
    void range_update(int node, int l, int r, int posl ,int posr, T val){
        push_update(node,l,r);
        if(posl>r || posr<l || l>r)return;
        if(l>=posl && r<=posr){
            Tree[node].lazy+=val;
            Tree[node].lazy%=MOD;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            range_update(node*2, l, mid, posl, posr, val);
            range_update(node*2+1, mid+1, r, posl, posr, val);
            Tree[node].data = (Tree[node*2].data + Tree[node*2+1].data)%MOD;
        }
    }

    inline T query(int posl, int posr){return query(1,1,n,posl,posr);}
    T query(int node, int l, int r, int posl, int posr){
        push_update(node,l,r);
        if(l>posr || r<posl || l>r)return 0;
        if(l>=posl && r<=posr)return Tree[node].data;
        int mid = (l+r)>>1;
        return (query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr))%MOD;
    }
};


inline void Solve(int Case){
    int n;
    si(n);
    FOR(i,n)si(arr[i]);
    segTreeLazy<ll> segTree(n);
    segTree.build(1,1,n);
    int m,l,r;
    ll k;
    si(m);
    while(m--){
        sii(l,r);
        sl(k);
        ll val = ((bigMod(r-l+2,k,MOD)-1LL+1LL*MOD)%MOD) * bigMod(r-l+1,MOD-2, MOD)%MOD;
        val%=MOD;
        ll toAdd = (segTree.query(l,r)%MOD * val%MOD)%MOD;
        segTree.range_update(l,r,toAdd);
    }
    for(int i=1; i<=n; i++)pf("%lld ",segTree.query(i,i)%MOD);
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
