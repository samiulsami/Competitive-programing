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

double dp[61][61][61];
int dir[61][61][61];
double W,E,X;
int vis[61][61][61]={0};
int color=1;

double f(int r, int p, int s){
    if(r+p+s==60)return 0;
    double &ret = dp[r][p][s];
    if(vis[r][p][s]==color)return ret;
    ret=0;
    vis[r][p][s]=color;

    double total=double(r+p+s);
    if(total==0){
        ret=f(1,0,0)+(1.0/3.0)*W + (1.0/3.0)*E;
        dir[0][0][0]=0;
        double tmp = f(0,1,0)+(1.0/3.0)*W + (1.0/3.0)*E;
        if(tmp>ret){
            ret=tmp;
            dir[0][0][0]=1;
        }
        tmp = f(0,0,1)+(1.0/3.0)*W + (1.0/3.0)*E;
        if(tmp>ret){
            ret=tmp;
            dir[0][0][0]=2;
        }
    }
    else{
        ///rock
        ret = f(r+1,p,s) + (double(s)/total)*E + (double(p)/total)*W;
        dir[r][p][s]=0;

        ///scissors
        double tmp = f(r,p,s+1) + (double(p)/total)*E + (double(r)/total)*W;
        if(tmp>ret){
            ret=tmp;
            dir[r][p][s]=2;
        }

        ///paper
        tmp = f(r,p+1,s) + (double(r)/total)*E + (double(s)/total)*W;
        if(tmp>ret){
            ret=tmp;
            dir[r][p][s]=1;
        }
    }

    return ret;
}

inline void Solve(int Case){
    color++;
    scanf("%lf%lf",&W,&E);
    f(0,0,0);

    int r=0,p=0,s=0;
    pf("Case #%d: ",Case);
    while(r+p+s<60){
        int x=dir[r][p][s];
        if(x==0)pf("R"),r++;
        else if(x==1)pf("P"),p++;
        else pf("S"),s++;
    }

    nl;

}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
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
            scanf("%lf",&X);
        #endif
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
