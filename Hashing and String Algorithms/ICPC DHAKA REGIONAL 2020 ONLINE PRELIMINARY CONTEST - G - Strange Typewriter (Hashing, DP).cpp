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

const int _hashCnt=2;
const int mod1 = (1LL<<31)-1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};
int dp[N];
int vis[N]={0};
int color=1;
int P[_hashCnt][N];

inline int mod(ll x) {
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{
    vector<int>H[_hashCnt];
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            H[ind].resize(n+1);H[ind][0]=0;
            for(int i=0; i<n; i++)
                H[ind][i+1] = mod((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]));

        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - mod(1LL*H[ind][l-1] * P[ind][r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline ll getHash(int l, int r){return combineHash(singleHash(l,r,0), singleHash(l,r,1));}
};

char s[N];
ll computeHash(const char *str, int &x){
    x=0;
    ll h=0,h1=0;
    for(int i=0; str[i]; i++){
        h = mod(1LL*h*bases[0] + ll(str[i]));
        x++;
    }
    for(int i=0; str[i]; i++){
        h1 = mod(1LL*h1*bases[1] + ll(str[i]));
    }
    return (h<<32)^h1;
}

vector<vector<ll> >hashlen;
int lenArr[N];
Hash sHash;
int n;

int f(int i){
    if(i>n)return 0;
    int &ret = dp[i];
    if(vis[i]==color)return ret;
    vis[i]=color;
    ret=1e7;
    for(int j=0; j<sz(hashlen); j++){
        if(i+lenArr[j]-1>n)break;
        if(binary_search(all(hashlen[j]), sHash.getHash(i,i+lenArr[j]-1))){
                ret = min(ret,f(i+lenArr[j])+1);
        }
    }
    return ret;
}

inline void Solve(int Case){
    color++;
    si(n);
    hashlen.clear();
    vector<pair<int,ll>>hashes;
    for(int i=0,x; i<n; i++){
        sf(" %s",&s);
        ll h=computeHash(s,x);
        hashes.push_back(pair<int,ll>(x,h));
    }
    sort(all(hashes));
    vector<ll>tmp;

    for(int i=0; i<n; i++){
        if(i){
            if(hashes[i-1].ff!=hashes[i].ff){
                    lenArr[sz(hashlen)]=hashes[i-1].ff;
                    hashlen.push_back(tmp);
                    tmp.clear();
            }
        }
        tmp.push_back(hashes[i].ss);
    }
    if(!tmp.empty()){
            lenArr[sz(hashlen)]=hashes.back().ff;
            hashlen.push_back(tmp);
    }

    sf(" %s",&s);
    n=strlen(s);
    sHash = Hash(s,n);
    int ans=f(1);
    pf("Case %d: ",Case);
    if(ans<1e7)pf("%d\n",ans);
    else pf("impossible\n");
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
    for(int j=0; j<_hashCnt; j++){
        P[j][0]=1;
        for(int i=1; i<N; i++)P[j][i] = mod(1LL*P[j][i-1]*bases[j]);
    }
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
