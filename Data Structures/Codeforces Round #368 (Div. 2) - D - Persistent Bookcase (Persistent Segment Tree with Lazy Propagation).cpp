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
const int N = 1e3+5;

struct node{
    int data;
    int lazy;
    node *left,*right;
    node(int val=0, int  lazy=0, node* left=NULL, node *right=NULL):lazy(lazy),data(val),left(left),right(right){}
}Tree[N*N*10];

int nodeCnt=0;

inline node *newNode(int data=0, int lazy=0, node *left=NULL, node *right=NULL){
    node *ret = &Tree[nodeCnt++];

    ret->data=data;
    ret->left=left;
    ret->right=right;
    ret->lazy=lazy;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r){
        cur->data=0;
        cur->lazy=0;
        return;
    }
    cur->left = newNode();
    cur->right = newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
    cur->data = cur->left->data + cur->right->data;
}



inline void push_update_clone(node *cur, int l, int r){
    if(cur->lazy!=0){
        cur->data = (r-l+1)-cur->data;
        if(l!=r){
            cur->left = newNode(cur->left->data, cur->left->lazy^1, cur->left->left, cur->left->right);
            cur->right = newNode(cur->right->data, cur->right->lazy^1, cur->right->left, cur->right->right);
        }
        cur->lazy=0;
    }
}


node *cloneAndRangeUpdate(node *cur, int l, int r, int posl, int posr, int val){
    push_update_clone(cur,l,r);
    if(l>posr || r<posl)return cur;
    if(l>=posl && r<=posr){
        node *tmp = newNode();
        tmp->data = (r-l+1)-cur->data;
        if(l!=r){
            int mid = (l+r)>>1;
            tmp->left = newNode(cur->left->data, cur->left->lazy^1, cur->left->left, cur->left->right);
            tmp->right = newNode(cur->right->data, cur->right->lazy^1, cur->right->left, cur->right->right);
        }
        return tmp;
    }
    node *tmp = newNode();
    int mid = (l+r)>>1;
    tmp->left = cloneAndRangeUpdate(cur->left,l,mid,posl,posr,val);
    tmp->right = cloneAndRangeUpdate(cur->right,mid+1,r,posl,posr,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}

int query(node *cur, int l, int r, int posl, int posr){
    push_update_clone(cur,l,r);
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left, l,mid,posl,posr) + query(cur->right, mid+1,r,posl,posr);
}

int n,m,q;
inline int calc(int i, int j){
    return (i-1)*m+j;
}

inline void Solve(int Case){

    siii(n,m,q);
    vector<node*>roots;
    roots.emplace_back(newNode());
    int mx = n*m;
    build(roots.back(),1,mx);
    int qtype,i,j,pos;

    while(q--){
        si(qtype);

        if(qtype==1){
            sii(i,j);
            pos=calc(i,j);
            if(query(roots.back(),1,mx,pos,pos)==0){
                    roots.push_back(cloneAndRangeUpdate(roots.back(),1,mx,pos,pos,1));
            }
            else roots.push_back(roots.back());
        }
        else if(qtype==2){
            sii(i,j);
            pos=calc(i,j);
            if(query(roots.back(),1,mx,pos,pos)==1){
                    roots.push_back(cloneAndRangeUpdate(roots.back(),1,mx,pos,pos,1));
            }
            else roots.push_back(roots.back());
        }
        else if(qtype==3){
            si(i);
            pos=(i-1)*(m)+1;
            roots.push_back(cloneAndRangeUpdate(roots.back(),1,mx,pos,pos+m-1,1));
        }
        else{
            si(i);
            roots.push_back(roots[i]);
        }

        pf("%d\n",query(roots.back(),1,mx,1,mx));
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
