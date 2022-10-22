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
const int MOD = (1LL<<31)-1;
const int base = 9831;
const int N = 1e4+5;

int n;
pii Table[20][N];
int lgval[N]={0};
char s[50];
int H[50],R[50],P[50];

inline pii Combine(pii a, pii b){
    if(a.first>b.first)return a;
    if(a.first<b.first)return b;
    return pii(a.first,min(a.second,b.second));
}

inline int mod(ll x) {
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}


inline int Hash(int l, int r){
    int h = 1LL*H[r] - mod(1LL*H[l-1]*P[r-l+1]);
    if(h<0)h+=MOD;
    return h;
}

inline int reverseHash(int l, int r){
    int h = 1LL*R[l] - mod(1LL*R[r+1]*P[r-l+1]);
    if(h<0)h+=MOD;
    return h;
}

int getcnt(const char *s){
    int len = strlen(s);
    H[0]=0;
    R[len+1]=0;
    for(int i=0; i<len; i++){
        H[i+1] = mod(1LL*H[i]*base + 1LL*s[i]);
        R[len-i] = mod(1LL*R[len-i+1]*base + 1LL*s[len-i-1]);
        assert(H[i+1]>0 && R[len-i]>0);
    }

    int low,high,mid,mx;
    int ret=0;
    for(int i=1; i<=len; i++){
        low=1,high=min(i,len-i+1);
        mx=0;
        while(low<=high){
            mid = (low+high)>>1;
            if(Hash(i-mid+1,i)==reverseHash(i,i+mid-1)){
                mx=max(mx,mid);
                low=mid+1;
            }
            else high=mid-1;
        }
        ret+=mx;

        low=1,high=min(i,len-i);
        mx=0;
        while(low<=high){
            mid = (low+high)>>1;
            if(Hash(i-mid+1,i)==reverseHash(i+1,i+mid)){
                mx=max(mx,mid);
                low=mid+1;
            }
            else high=mid-1;
        }
        ret+=mx;
    }
    return ret;
}

inline void Solve(int Case){
    int q;
    sii(n,q);

    auto gethash = [&](const char *s){
        int h=0;
        for(int i=0;s[i];i++)h=mod(1LL*h*base + 1LL*s[i]);
        return h;
    };

    unordered_map<int,int>mp;
    mp.reserve(1024);
    mp.max_load_factor(0.25);

    for(int i=1; i<=n; i++){
        sf(" %s",&s);
        Table[0][i]=pii(getcnt(s),i);
        mp[gethash(s)]=i;
    }

    for(int i=1; i<20; i++){
        for(int j=1; j+(1<<i)-1<=n; j++){
            Table[i][j]=Combine(Table[i-1][j],Table[i-1][j+(1<<(i-1))]);
        }
    }

    int l,r;
    while(q--){
        sf(" %s",&s);
        l=mp[gethash(s)];

        sf(" %s",&s);
        r=mp[gethash(s)];
        if(l>r)swap(l,r);

        int LOG = lgval[r-l+1];
        pii ans = Combine(Table[LOG][l],Table[LOG][r-(1<<LOG)+1]);
        pf("%d\n",ans.second);
    }


}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
    P[0]=1;
    for(int i=1; i<35; i++)P[i]=mod(1LL*P[i-1]*base);
    lgval[0]=lgval[1]=0;
    for(int i=2; i<=10003; i++)lgval[i]=lgval[i>>1]+1;
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
