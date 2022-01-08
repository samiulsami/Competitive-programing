#include<bits/stdc++.h>
///Codeforces Beta Round #7 - D. Palindrome Degree
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
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}
template<typename T>inline bool MAX(T &a, T b){return b>a?a=b,1:0;}
template<typename T>inline bool MIN(T &a, T b){return b<a?a=b,1:0;}
inline bool checkBit(int n, int pos){return bool(n&(1<<pos));}
inline int setBit(int n, int pos){return n|(1<<pos);}
inline int toggleBit(int n, int pos){return n^(1<<pos);}
const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
ll modMul(ll a, ll b){ll ret=0;a%=MOD;while(b>0){if(b&1)ret=(ret+a)%MOD;b>>=1;a=(a<<1)%MOD;}return ret%MOD;}
ll bigMod(ll a, ll b){if(a==0)return 0;ll ret=1;a%=MOD;while(b>0){if(b&1)ret=(ret*a)%MOD;b>>=1;a=(a*a)%MOD;}return ret%MOD;}
ll lcm(ll a, ll b){return ((a/__gcd(a,b))*b);}
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const int N = 5e6+5;
int getBase(int l, int r){
    int ret = rand(l,r);
    if(ret&1)return ret;
    return ret-1;
}
const int mod1 = (1LL<<31)-1;
const int base1=getBase(11887,1<<25);
vector<int>P;

struct Hash{
    vector<int>H;
    vector<int>R;
    int n;
    inline int mod(ll x) {/// dmkozyrev
        x+=mod1;
        x=(x>>31)+(x&mod1);
        return int((x>>31)+(x&mod1));
    }
    inline void initP(){
        while((int)P.size()<=n){
            if(P.empty())P.push_back(1);
            else P.push_back(mod(1LL*P.back()*base1));
        }
    }
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
            initP();
            H.resize(n+1);H[0]=0;
            R.resize(n+2);R[n+1]=0;R[0]=0;
            for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
                H[i+1] = mod((1LL*H[i]*base1)+(ll)s[i]);
                R[j-1] = mod((1LL*R[j]*base1) + (ll)s[j-2]);
            }
    }
    inline int getHash(int l, int r){
        int h1 = H[r] - mod(1LL*H[l-1]*P[r-l+1]);
        return h1<0?h1+mod1:h1;

    }
    inline int reverseHash(int l, int r){
        int h1 = R[l] - mod(1LL*R[r+1]*P[r-l+1]);
        return h1<0?h1+mod1:h1;
    }
};


char s[N];
inline int read(char *st){
    int len=0;
    while((s[len]=getchar())!='\n')len++;
    s[len]='\0';
    return len;
}

int arr[N]={0};

inline void Solve(int Case){
    int n = read(s);
    Hash a(s,n);
    int ans=0;
    for(int i=1; i<=n; i++){
        if(a.getHash(1,i)==a.reverseHash(1,i)){
            arr[i]=arr[i/2]+1;
            ans+=arr[i];
        }
    }
    pf("%d\n",ans);
    //for(int i=1; i<=n; i++)pf("%d: %d\n",i,arr[i]);

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
