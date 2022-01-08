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
const int N = 402;


typedef pair<ll,bool> pli;

pli dp[N][N];
pii dir[N][N];
int vis[N][N]={0};
int curMask;
int weight[N][N];
int color[N][N];
int curColor=1;
int n,k,w;

pli f(int i, int j){
    if(i>n || j>n)return pli(1e15,0);
    if(!checkBit(curMask,color[i][j]))return pli(1e15,0);
    if(i==n && j==n)return pli(weight[n][n],1);
    pli &ret=dp[i][j];
    if(vis[i][j]==curColor)return ret;
    vis[i][j]=curColor;
    ret={1e15,0};

    if(i+1<=n){
        pli tmp=f(i+1,j);
        tmp.first+=weight[i][j];
        if(tmp.second && tmp.first<=w){
            ret=tmp;
            dir[i][j]={i+1,j};
        }
    }
    if(j+1<=n){
        pli tmp=f(i,j+1);
        tmp.first+=weight[i][j];
        if(tmp.first<=w){
            if(tmp.second && ret.second==0){
                ret=tmp;
                dir[i][j]={i,j+1};
            }
            else if(tmp.second && ret.second){
                if(tmp.first<ret.first){
                    ret=tmp;
                    dir[i][j]={i,j+1};
                }
            }
        }
    }

    return ret;
}


inline void Solve(int Case){
    siii(n,k,w);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)si(weight[i][j]);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
                si(color[i][j]);
                color[i][j]--;
        }
    }

    vi masks[12];

    for(int i=1, lim=(1<<k)-1; i<=lim; i++){
        masks[(int)__builtin_popcount(i)].push_back(i);
    }

    int low=1,high=k,mid;
    int possibleMask=-1;
    while(low<=high){
        mid=(low+high)/2;

        bool possible=0;
        for(int i:masks[mid]){
            curMask=i;
            curColor++;
            pli tmp=f(1,1);
            if(tmp.second && tmp.first<=w){
                possible=1;
                possibleMask=i;
                break;
            }
        }

        if(possible)high=mid-1;
        else low=mid+1;
    }

    if(possibleMask==-1)pf("-1\n");
    else{
        pf("%d\n",(int)__builtin_popcount(possibleMask));
        curMask=possibleMask;
        curColor++;
        f(1,1);
        int i=1,j=1;
        pf("1 1");
        while(i<n || j<n){
            pii tmp=dir[i][j];
            i=tmp.ff;
            j=tmp.ss;
            pf(" %d %d",i,j);
        }
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
