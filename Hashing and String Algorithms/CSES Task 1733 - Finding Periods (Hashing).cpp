#include<bits/stdc++.h>
///CSES Task 1733 - Finding Periods
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
(uint64_t) __builtin_ia32_rdtsc()};
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

int getBase(int l, int r){
    int ret = rand(l,r);
    if(ret&1)return ret;
    return ret-1;
}
const int mod1 = (1LL<<31)-1;
const int base1=getBase(11887,1<<25);
const ull base2=(ull)getBase(15661,1<<27);
vector<pair<int,ull> >P;

struct Hash{
    vector<pair<int,ull> >H;
    int n;
    inline int mod(ll x) {/// dmkozyrev
        x+=mod1;
        x=(x>>31)+(x&mod1);
        return int((x>>31)+(x&mod1));
    }
    inline void initP(){
        while((int)P.size()<=n){
            if(P.empty())P.push_back({1,1});
            else P.push_back({mod(1LL*P.back().first*base1), (ull)P.back().second*base2});
        }
    }
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
            initP();
            H.resize(n+1);H[0]={0,0};
            for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
                H[i+1].first = mod((1LL*H[i].first*base1)+(ll)s[i]);
                H[i+1].second = H[i].second*base2 + (ull)s[i];
            }
    }
    inline pair<int,ull>getHash(int l, int r){
        int h1 = H[r].first - mod(1LL*H[l-1].first*P[r-l+1].first);
        ull h2 = H[r].second - (H[l-1].second*P[r-l+1].second);
        return {h1<0?h1+mod1:h1, h2};
    }
};

char s[N];
inline int read(char *s){
    int len =0;
    while((s[len]=getchar())!='\n')len++;
    s[len]='\0';
    return len;
}

inline void Solve(int Case){
    int n = read(s);
    Hash a(s,n);

    for(int len=1; len<=n; len++){
        bool possible=1;
        pair<int,ull> H = a.getHash(1,len);

        for(int i=len+1; possible && i<=n; i+=len){
            if(i+len-1<=n){
                if(a.getHash(i,i+len-1)!=H){
                    possible=0;
                    break;
                }
            }
            else{
                if(a.getHash(i,n)!=a.getHash(1,n-i+1)){
                    possible=0;
                    break;
                }
            }
        }

        if(possible)pf("%d ",len);
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
