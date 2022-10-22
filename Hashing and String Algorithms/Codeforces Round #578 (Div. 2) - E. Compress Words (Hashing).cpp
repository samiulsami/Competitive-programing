#include<bits/stdc++.h>
///Codeforces Round #578 (Div. 2) - E. Compress Words
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
#define nl "\n"
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

const int N = 1e6+5;
const int _hashCnt=2;
const int mods[_hashCnt] = {2100032603,2104050497};
const int bases[_hashCnt] = {rand(137,1<<14),rand(149,1<<15)};

vector<int>P[_hashCnt];

struct Hash{
    vector<int>H[_hashCnt];
    int n;

    inline void initP(int ind){
        while((int)P[ind].size()<=n){
            if(P[ind].empty())P[ind].push_back(1);
            else P[ind].push_back((1LL*P[ind].back()*bases[ind])%mods[ind]);
        }
    }

    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            initP(ind);
            H[ind].resize(n+1);H[ind][0]=0;
            for(int i=0; i<n; i++)
                H[ind][i+1] = ((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]))%mods[ind];
        }
    }

    template<typename T>
    void append(T c){
        n++;
        for(int ind=0; ind<_hashCnt; ind++){
            initP(ind);
            H[ind].push_back(((1LL*H[ind].back()*bases[ind]) + (ll)c)%mods[ind]);
        }
    }

    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - (1LL*H[ind][l-1] * P[ind][r-l+1])%mods[ind];
        return (h<0?h+mods[ind]:h);
    }
    inline ll getHash(int l, int r){return combineHash(singleHash(l,r,0), singleHash(l,r,1));}
};

int check(Hash &a, Hash &b){
    ///match suffix of 'a' with prefix of 'b';
    int alen=a.n,blen=b.n,mx=0;
    int n = min(alen,blen);
    for(int i=1; i<=n; i++){
        if(a.getHash(alen-i+1,alen)==b.getHash(1,i))
            mx=i;
    }
    return mx;
}

inline int read(char *s){
    int len=0;
    while(s[len]=getchar()){
        if(s[len]=='\n' || s[len]==' ')break;
        len++;
    }
    s[len]='\0';
    return len;
}

char ans[N],inp[N];

inline void Solve(int Case){
    int cnt;
    si(cnt);
    cnt--;
    getchar();
    int len = read(ans);
    Hash a(ans,len);
    int len2;

    FOR(cntr,cnt){
        len2=read(inp);
        Hash tmp(inp,len2);
        int maxMatch = check(a,tmp);
        for(int i=maxMatch; i<len2; i++){
                a.append(inp[i]);
                ans[len++]=inp[i];
        }
    }
    ans[len]='\0';
    pf("%s\n",ans);


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
