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
#define sl(x) scanf("%ulld",&x)
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
const double PI = 2*acos(0.0);
inline int readline(char *s, char d='\n'){int len=0;while((s[len]=getchar())!=d)len++;s[len]='\0';return len;}
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const int N = 1e4+5;
const int mod1 = (1LL<<31)-1;
const int bases[2] = {rand(4393,1<<21),rand(7833,1<<22)};


inline int mod(ll x) {
        x+=mod1;
        x=(x>>31)+(x&mod1);
        return ((x>>31)+(x&mod1));
}

inline int bigMod(ll x, ll pw){
    if(pw==0)return 1;
    x=mod(x);
    pw=mod(pw);
    ull ret=1;
    while(pw){
        if(pw&1)ret = mod(ret*x);
        x = mod(x*x);
        pw>>=1;
    }
    return ret;
}

int len;

int gsum(int r, int n){
    int numerator = bigMod(r,n)-1;
    if(numerator<0)numerator+=mod1;
    int denominator = bigMod(r-1,mod1-2);
    numerator = mod(1LL*numerator*denominator);
    return numerator;
}

inline void appendRightSingle(int &h, int &r, char c, int ind, int z){
    int b = bases[ind];
    int a = mod(1ull*c*bigMod(b,len));
    h = mod(1ull*h+1ull*mod(1LL*a*gsum(b,z)));

    r = mod(1ull*r*bigMod(b,z));
    a = (ll)c;
    r = mod(1ull*r + 1ull*mod(1LL*a*gsum(b,z)));
}

inline void appendLeftSingle(int &h, int &r, char c, int ind, int z){
    int b = bases[ind];
    int a = mod(1ull*c*bigMod(b,len));
    r = mod(1ull*r+1ull*mod(1LL*a*gsum(b,z)));

    h = mod(1ull*h*bigMod(b,z));
    a = (ull)c;
    h = mod(1ull*h + 1ull*mod(1LL*a*gsum(b,z)));
}

inline void appendRight(ll &H, ll &R, char c, int z){
    int h1=H>>32;
    int h2=(1ull*h1<<32)^H;
    int r1=R>>32;
    int r2=(1ull*r1<<32)^R;
    appendRightSingle(h1,r1,c,0,z);
    appendRightSingle(h2,r2,c,1,z);
    H = (1ull*h1<<32)^h2;
    R = (1ull*r1<<32)^r2;
}

inline void appendLeft(ll &H, ll &R, char c, int z){
    int h1=H>>32;
    int h2=(1ull*h1<<32)^H;
    int r1=R>>32;
    int r2=(1ull*r1<<32)^R;
    appendLeftSingle(h1,r1,c,0,z);
    appendLeftSingle(h2,r2,c,1,z);
    H = (1ull*h1<<32)^h2;
    R = (1ull*r1<<32)^r2;
}
char s[N];

inline void Solve(int Case){
    getchar();
    len=readline(s);
    int tmp=len;
    len=0;
    ll H=0,R=0;

    for(int i=0; i<tmp; i++){
        appendRight(H,R,s[i],1);
        len++;
    }
    //cout<<H<<" "<<R<<endl;
    int q,z;
    char x,y;
    pf("Case %d:\n",Case);
    si(q);
    while(q--){
        getchar();
        x=getchar();
        getchar();
        y=getchar();
        si(z);
        if(x=='L'){
                appendLeft(H,R,y,z);
                len+=z;
        }
        else {
                appendRight(H,R,y,z);
                len+=z;
        }

        if(H==R)pf("Yes\n");
        else pf("No\n");
    }
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
        #endif
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
