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
    int data;
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
};

int nodeCnt=0;
node Tree[40*N];

inline node *newNode(int data=0, node *left=NULL, node *right=NULL){
    node *ret = &Tree[nodeCnt++];
    ret->data=data;
    ret->left=left;
    ret->right=right;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r)return;
    cur->left = newNode();
    cur->right = newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
    cur->data = cur->left->data + cur->right->data;
}

node *cloneAndUpdate(node *cur, int l, int r, int pos, int val){
    if(l>pos || r<pos)return cur;
    if(l==r){
        node *tmp = newNode(val);
        return tmp;
    }
    node *tmp = newNode();
    int mid = (l+r)>>1;
    tmp->left = cloneAndUpdate(cur->left,l,mid,pos,val);
    tmp->right = cloneAndUpdate(cur->right,mid+1,r,pos,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}

int query(node *cur, int l, int r, int posl, int posr){
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left,l,mid,posl,posr) + query(cur->right,mid+1,r,posl,posr);
}

int Search(node *cur, int l, int r, int val){
    if(l==r)return l;
    int cnt = cur->left->data;
    int mid = (l+r)>>1;
    if(cnt>val)return Search(cur->left,l,mid,val);
    return Search(cur->right,mid+1,r,val-cnt);
}

int n;
int arr[N];
int prevIndex[N];

inline void Solve(int Case){
    si(n);
    memset(prevIndex,-1,sizeof(prevIndex));
    for(int i=1; i<=n; i++)si(arr[i]);

    vector<node*>roots(n+2);
    roots[n+1]=newNode();
    int lim = n+5;
    build(roots[n+1],1,lim);

    for(int i=n; i>=1; i--){
        node *tmp=roots[i+1];
        int val = arr[i];
        if(prevIndex[val]==-1)
            tmp = cloneAndUpdate(tmp,1,lim,i,1);
        else{
            tmp = cloneAndUpdate(tmp,1,lim,prevIndex[val],0);
            tmp = cloneAndUpdate(tmp,1,lim,i,1);
        }
        prevIndex[val]=i;
        roots[i]=tmp;
    }

    /*while(1){
        int aa,bb;
        sii(aa,bb);
        pf("val: %d\n",Search(roots[bb],1,n,aa));
    }*/

    for(int i=1; i<=n; i++){
        int ans=0;
        int ind=1;
        int tmp=i;
        while(ind<=n){
            ind = Search(roots[ind],1,lim,i);

            //dbug(ind);
            ans++;
        }
        pf("%d ",ans);
    }

    nl;

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
