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
const int N = 4e5+5;
const int mod1 = (1LL<<31)-1;
const int _hashCnt=2;
const int bases[_hashCnt] = {rand(11887,1<<21),rand(15661,1<<22)};
int n;
int P[_hashCnt][N];
int d;
char s[N];

inline int mod(ll x) {
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct node{
    int h[_hashCnt],r[_hashCnt];
    node(){for(int i=0; i<_hashCnt; i++)h[i]=r[i]=0;}
    void update(int ind, char val){
        for(int i=0; i<_hashCnt; i++){
            h[i]=mod(1LL*val*P[i][ind]);
            r[i]=mod(1LL*val*P[i][n-ind-1]);
        }
    }
    node operator+(const node &nd)const{
        node ret;
        for(int i=0; i<_hashCnt; i++){
            ret.h[i]=mod(1LL*h[i]+1LL*nd.h[i]);
            ret.r[i]=mod(1LL*r[i]+1LL*nd.r[i]);
        }
        return ret;
    }
}Tree[2*N];


void point_update(int ind, char val){
    ind+=n;
    Tree[ind].update(ind-n,val);
    for(;ind>1; ind>>=1)Tree[ind>>1] = Tree[ind]+Tree[ind^1];
}

node range_query(int l, int r){ ///[l,r]
    l+=n;
    r+=n+1;
    node ret;
    for(;l<r; l>>=1,r>>=1){
        if(l&1)ret=ret+Tree[l++];
        if(r&1)ret=ret+Tree[--r];
    }
    return ret;
}

bool isPalindrome(int l, int r){
    if(l>r || r>=n)return 0;
    node tmp = range_query(l,r);
    int H,R;
    for(int i=0; i<_hashCnt; i++){
        H = mod(1LL*tmp.h[i]*P[i][n-r-1]);
        R = mod(1LL*tmp.r[i]*P[i][l]);
        if(H!=R)return 0;
    }
    return 1;
}


inline void Solve(int Case){
    sf("%d %s",&d,&s);
    n=strlen(s);

    if(d==1){
        pf("Impossible\n");
        return;
    }

    for(int i=0; i<_hashCnt; i++){
        P[i][0]=1;
        for(int j=1; j<=n+1; j++)P[i][j] = mod(1LL*P[i][j-1]*bases[i]);
    }

    for(int i=0; i<n; i++)
        point_update(i,s[i]);

    int palInd=-1;
    for(int i=0; i<n; i++){
        if(isPalindrome(i,i+d-1)){
            palInd=i+d-1;
            break;
        }
        if(isPalindrome(i,i+d)){
            palInd=i+d;
            break;
        }
    }

    if(palInd==-1)palInd=n-1;
    int nextPalInd=-1;

    for(int i=palInd; i>=0; i--){
        for(char c=s[i]+1; c<='z'; c++){
            s[i]=c;
            point_update(i,c);
            if(i>=d-1 && isPalindrome(i-d+1,i))continue;
            if(i>=d && isPalindrome(i-d,i))continue;
            nextPalInd=i;
            break;
        }
        if(nextPalInd!=-1)break;
    }

    if(nextPalInd==-1){
        pf("Impossible\n");
        return;
    }

    for(int i=nextPalInd+1; i<n; i++){
        s[i]='a';
        point_update(i,'a');
    }

    for(int i=0; i+d-1<n; i++){
        if(isPalindrome(i,i+d-1)){
            s[i+d-1]++;
            point_update(i+d-1,s[i+d-1]);
            if(i>0 && isPalindrome(i-1,i+d-1)){
                s[i+d-1]++;
                point_update(i+d-1,s[i+d-1]);
            }
        }

        if(isPalindrome(i,i+d)){
            s[i+d]++;
            point_update(i+d,s[i+d]);
        }
    }

    pf("%s\n",s);
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
