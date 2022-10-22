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
int arr[N];
int n,d;
typedef long double ld;
typedef pair<ld,bool>pdb;
ld lgval[N];

pdb dp[N][12];
bool vis[N][12]={0};
pii Dir[N][12];

pdb f(int i, int digit){
    if(i==n)return pdb(0,bool(digit==d));
    pdb &ret = dp[i][digit];
    if(vis[i][digit])return ret;
    vis[i][digit]=1;
    ret=pdb(0,0);

    ret=f(i+1,digit);
    Dir[i][digit]=pii(digit,0);

    pdb tmp = f(i+1,(digit*arr[i])%10);
    tmp.first+=lgval[i];
    if(tmp.second && tmp.first>ret.first){
        ret=tmp;
        Dir[i][digit] = pii((digit*arr[i])%10,1);
    }
    return ret;
}


inline void Solve(int Case){

    sii(n,d);
    FOR(i,n){
        si(arr[i]);
        lgval[i] = log10((ld)arr[i]);
    }

    pdb cur(0,0);
    int start=-1;
    for(int i=0; i<n; i++){
        pdb tmp=f(i+1,arr[i]%10);
        tmp.first+=lgval[i];
        if(tmp.second && tmp.first>cur.first){
            Dir[i][0]=pii(arr[i]%10,1);
            start=i;
            cur=tmp;
        }
    }

    if(start==-1)pf("-1\n");
    else{
        vi ans;
        int i=start;
        int digit=0;
        while(i<n){
            if(Dir[i][digit].second){
                ans.pb(i);
                digit = Dir[i][digit].first;
            }
            i++;
        }

        pf("%d\n",sz(ans));
        for(int i:ans)pf("%d ",arr[i]);
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
