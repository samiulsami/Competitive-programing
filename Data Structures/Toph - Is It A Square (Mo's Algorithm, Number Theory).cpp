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
const int Div=320;
vi primes;
bool status[N]={0};
int arr[N];
vector<pii> factors[N];
int pref[N]={0};
int zeroCount[N]={0};
bool ans[N];

struct query{
    int i,l,r,x;
    query(){}
    query(int i, int l, int r):i(i),l(l),r(r){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return (x&1)?r<q.r:r>q.r;
    }
}queries[N];

vector<pii> factorize(int x){
    vector<pii>ret;
    for(int p:primes){
        if(1LL*p*p>x)break;
        if(x%p==0){
            int power=0;
            while(x%p==0){
                x/=p;
                power++;
            }
            ret.push_back(pii(p,power));
        }
    }
    if(x>1)ret.push_back(pii(x,1));
    return ret;
}

int pcnt[N]={0};
int oddFactorCount=0;

inline void Add(int x){
    for(pii factor:factors[x]){
        if(pcnt[factor.ff]&1)oddFactorCount--;
        pcnt[factor.ff]+=factor.ss;
        if(pcnt[factor.ff]&1)oddFactorCount++;
    }
}

inline void Remove(int x){
    for(pii factor:factors[x]){
        if(pcnt[factor.ff]&1)oddFactorCount--;
        pcnt[factor.ff]-=factor.ss;
        if(pcnt[factor.ff]&1)oddFactorCount++;
    }
}



inline void Solve(int Case){
    int n,m;
    sii(n,m);
    for(int i=1; i<=n; i++){
        si(arr[i]);
        factors[i]=factorize(abs(arr[i]));
        if(arr[i]>0)pref[i]=0;
        else if(arr[i]<0)pref[i]=1;
        else zeroCount[i]=1;
        zeroCount[i]+=zeroCount[i-1];
        pref[i]+=pref[i-1];
    }

    for(int i=0,l,r; i<m; i++){
        sii(l,r);
        queries[i]=query(i,l,r);
        queries[i].x=l/Div;
    }

    sort(queries,queries+m);

    int l=1,r=0;
    for(int i=0; i<m; i++){
        while(l>queries[i].l)Add(--l);
        while(r<queries[i].r)Add(++r);
        while(r>queries[i].r)Remove(r--);
        while(l<queries[i].l)Remove(l++);

        int negativeCount=pref[r]-pref[l-1];
        if(zeroCount[r]-zeroCount[l-1]>0)ans[queries[i].i]=1;
        else if(negativeCount&1)ans[queries[i].i]=0;
        else ans[queries[i].i]=bool(oddFactorCount==0);
    }

    for(int i=0; i<m; i++){
        if(ans[i])pf("Yes\n");
        else pf("No\n");
    }
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  //#define fastio
int main(){
    for(int i=2; i<=1e5; i+=2)status[i]=1;
    int sq = (sqrt(1e5)+5);
    for(int i=3; i<=sq; i+=2)
        if(!status[i])
            for(int j=i*i; j<=1e5; j+=i+i)
                status[j]=1;

    primes.push_back(2);
    for(int i=3; i<=1e5; i+=2)if(!status[i])primes.push_back(i);

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
