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

struct node{
    ll data;
    int cnt;
    node *left,*right;
    node(){
        data=0;
        cnt=0;
        left=right=this;
    }
    node(ll data, int cnt, node *left=NULL, node *right=NULL):data(data),cnt(cnt),left(left),right(right){}
}Tree[21*N];
int nodeCnt=0;
int arr[N];

inline node *newNode(ll data=0, int cnt=0, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data,cnt,left,right);
    return &Tree[nodeCnt++];
}

void build(node *cur, int l, int r){
    if(l==r)return;
    cur->left=newNode();
    cur->right=newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
}

node *update(node *cur, int l, int r, int pos, ll val){
    if(l>r || l>pos || r<pos)return cur;
    if(l==pos && r==pos)return newNode(cur->data+val, cur->cnt+1);
    int mid = (l+r)>>1;
    node *tmp = newNode();
    tmp->left = update(cur->left,l,mid,pos,val);
    tmp->right = update(cur->right,mid+1,r,pos,val);
    tmp->data = tmp->left->data + tmp->right->data;
    tmp->cnt = tmp->left->cnt + tmp->right->cnt;
    return tmp;
}

int Search(node *curL, node *curR, int l, int r, ll k){
    if(curR->data - curL->data<=k)return curR->cnt - curL->cnt;
    if(l==r){
            if(curR->data - curL->data<=k)return curR->cnt - curL->cnt;
            return 0;
    }
    int mid = (l+r)>>1;
    ll val = curR->left->data - curL->left->data;
    if(val>k)return Search(curL->left, curR->left, l, mid, k);
    return curR->left->cnt - curL->left->cnt + Search(curL->right, curR->right, mid+1, r, k-val);
}

inline void Solve(int Case){
    int n;
    si(n);

    vector<pii>tmp(1);
    for(int i=1; i<=n; i++){
        si(arr[i]);
        tmp.push_back({arr[i],i});
    }

    sort(all(tmp));
    for(int i=1; i<=n; i++){
        arr[tmp[i].second]=i;
    }

    vector<node*>roots({newNode()});
    build(roots.back(),1,n);

    for(int i=1; i<=n; i++){
        roots.push_back(update(roots.back(),1,n,arr[i],tmp[arr[i]].first));
    }
    int q,l,r;
    ll k;
    si(q);
    while(q--){
        sf("%d%d%lld",&l,&r,&k);
        pf("%d\n",Search(roots[l-1],roots[r],1,n,k));
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
