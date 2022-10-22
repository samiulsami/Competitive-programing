#include<bits/stdc++.h>
///Codeforces Round #291 (Div. 2) - C. Watto and Mechanism
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

const int N = 6e5+5;

const int mods[2]={2100032603,2104050497};
const int bases[2] = {rand(137,1<<14),rand(149,1<<15)};
int P[2][N];

int singleHash(const char *s, int n, int ind){
    int h=0;
    for(int i=0; i<n; i++)h = ((1LL*h*bases[ind]) + 1LL*s[i])%mods[ind];
    return h;
}
ll doubleHash(const char *s, int n){
    ll h1 = singleHash(s,n,0);
    ll h2 = singleHash(s,n,1);
    return (h1<<32)^h2;
}

int modifySingleHash(int h, int pos, int n, char oldChar, char newChar, int ind){
    h-=(1LL*oldChar*P[ind][n-pos])%mods[ind];
    h=(1LL*h+(1LL*newChar*P[ind][n-pos]))%mods[ind];
    return h<0?h+mods[ind]:h;
}

ll modifyHash(ll h, int pos, int n, char oldChar, char newChar){
    n--;
    int h1 = h>>32;
    int h2 = (1LL*h1<<32)^h;
    ll H = modifySingleHash(h1,pos,n,oldChar,newChar,0);
    H<<=32;
    H^=modifySingleHash(h2,pos,n,oldChar,newChar,1);
    return H;
}

inline int read(char *s){
    int len=0;
    while((s[len]=getchar())!='\n')len++;
    s[len]='\0';
    return len;
}

char s[N];

inline void Solve(int Case){
    int n,m,len;
    sii(n,m);
    getchar();
    unordered_map<ll,bool>hashes;
    hashes.max_load_factor(0.25);
    FOR(i,n){
        len = read(s);
        hashes[doubleHash(s,len)]=1;
    }

    ll H,tmpH;
    FOR(i,m){
        len = read(s);
        H = doubleHash(s,len);
        bool found=0;

        for(int j=0; !found && j<len; j++){
            char newChar;
            found=0;
            for(int k=1; k<3; k++){
                int ind = s[j]-'a';
                ind+=k;
                ind%=3;
                newChar = 'a'+ind;
                tmpH = modifyHash(H,j,len,s[j],newChar);
                if(hashes.count(tmpH)){
                    found=1;
                    break;
                }
            }
        }
        if(found)pf("YES\n");
        else pf("NO\n");
    }

}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  //#define fastio
int main(){
    for(int i=0; i<2; i++){
        P[i][0]=1;
        for(int j=1; j<N; j++){
            P[i][j] = (1LL*P[i][j-1]*bases[i])%mods[i];
        }
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
