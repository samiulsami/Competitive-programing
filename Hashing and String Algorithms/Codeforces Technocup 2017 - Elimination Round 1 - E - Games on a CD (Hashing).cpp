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

const ull mod1 = (1ull<<61) - 1;
inline ull hashmodmul(ull a, ull b){
	ull l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	ull ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod1) + (ret>>61);
	ret = (ret & mod1) + (ret>>61);
	return ret-1;
}
inline ull hashAdd(ull a, ull b){a+=b;return a>=mod1?a-mod1:a;}
inline ull hashSub(ull a, ull b){a-=b;return a>=mod1?a+mod1:a;}
const ull base1 = (ull)rand(15661,1<<22);
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--)H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
};

inline void Solve(int Case){
    int n,k;
    string s,in;
    cin>>n>>k>>s;
    int len=sz(s);
    s+=s;
    Hash H(s,sz(s));

    map<ull,int>mp;
    int g;
    cin>>g;
    for(int i=1; i<=g; i++){
        cin>>in;
        ull curh=0;
        for(char c:in)
            curh = hashAdd(hashmodmul(curh,base1),c);
        mp[curh]=i;
    }

    for(int i=1; i<=k; i++){
        set<ll>st;
        vi ans;
        for(int j=i; j+k-1<=sz(s) && j-i+k<=len; j+=k){
            ll curh = H.getHash(j,j+k-1);
            if(mp.count(curh) && !st.count(curh)){
                ans.push_back(mp[curh]);
                st.insert(curh);
            }
            else{
                ans.clear();
                break;
            }
        }
        if(sz(ans)!=n)continue;

        cout<<"YES"<<endl;
        for(int x:ans)cout<<x<<" ";
        return;
    }
    cout<<"NO"<<endl;
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  #define fastio
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
