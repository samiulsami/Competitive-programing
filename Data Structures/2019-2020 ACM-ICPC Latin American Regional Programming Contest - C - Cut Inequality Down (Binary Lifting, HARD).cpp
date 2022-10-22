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

const int Div=100;
const ll INF=1e16;
ll cSum[N];
int arr[N];
int lgVal[N]={0};
int n;
ll L,U;
ll minTable[20][N],maxTable[20][N];
pll Table[2][20][N];

void build(){
    for(int i=2; i<N; i++)lgVal[i]=lgVal[i>>1]+1;
    int LOG=ceil(log2(n))+1;
    for(int i=1; i<LOG; i++){
        for(int j=1; j+(1<<i)-1<=n; j++){
            minTable[i][j] = min(minTable[i-1][j], minTable[i-1][j+(1<<(i-1))]);
            maxTable[i][j] = max(maxTable[i-1][j], maxTable[i-1][j+(1<<(i-1))]);
        }
    }
}

pll query(int l, int r){
    int LOG = lgVal[r-l+1];
    ll x = min(minTable[LOG][l], minTable[LOG][r-(1<<LOG)+1]);
    ll y = max(maxTable[LOG][l], maxTable[LOG][r-(1<<LOG)+1]);
    return pll(y,x);
}

pii Find(int l, int r, int LInd, ll val){
    int low=1,high=r-l+1,ans=1e9,mid;
    while(low<=high){
        mid=(low+high)>>1;
        pll cur=query(l,l+mid-1);
        if((val+cur.ff-cSum[LInd-1])>=U || (val+cur.ss-cSum[LInd-1]<=L)){
                high=mid-1;
                ans=min(ans,l+mid-1);
        }
        else low=mid+1;
    }
    int b=0;
    if(ans==1e9)return pii(1e9,0);
    if(val+cSum[ans]-cSum[LInd-1]>=U)b=1;
    else b=0;

    return pii(ans+1,b);///b==0 if val<L, b==1 if val>U
}



inline void Solve(int Case){
    for(int i=0; i<20; i++){
        for(int j=0; j<N; j++){
            minTable[i][j]=INF;
            maxTable[i][j]=-INF;
            for(int k=0; k<2; k++){
                Table[k][i][j]=pii(1e9,0);
            }
        }
    }
    si(n);
    sll(L,U);
    cSum[0]=0;
    for(int i=1; i<=n; i++){
            si(arr[i]);
            cSum[i] = cSum[i-1]+(ll)arr[i];
            minTable[0][i]=cSum[i];
            maxTable[0][i]=cSum[i];
    }
    build();

    for(int i=1; i<=n; i++){
        Table[1][0][i]=Find(i,n,i,U);
        Table[0][0][i]=Find(i,n,i,L);
    }

    int K=ceil(log2(n))+1;
    for(int i=1; i<K; i++){
        for(int j=1; j<=n; j++){
            for(int m=0; m<2; m++){
                if(Table[m][i-1][j].ff!=1e9){
                    pii prev = Table[m][i-1][j];
                    Table[m][i][j] = Table[prev.ss][i-1][prev.ff];
                }
            }
        }
    }

    /*for(int i=1; i<=n; i++){
        for(int j=0; j<2; j++){
            if(Table[j][0][i].ff!=1e9){
                pf("%c jump: %d -> %d\n",(j?'U':'L'),i,Table[j][0][i].ff);
            }
        }
    }*/

    int m,x,y,k;
    si(m);
    while(m--){
        siii(x,y,k);
        pii cur=Find(x,y,x,(ll)k);

        int i=cur.ff;
        int b=cur.ss;
        ll val;
        if(i>y){
            val = (ll)k + cSum[y]-cSum[x-1];
        }
        else{

            for(int k=K-1; k>=0; k--){
                if(Table[b][k][i].ff!=1e9 && Table[b][k][i].ff<=y){
                    pii tmp=Table[b][k][i];
                    i=tmp.ff;
                    b=tmp.ss;
                }
            }

            if(b)val=U;
            else val=L;
            val = val+cSum[y]-cSum[i-1];
        }

        if(val>U)val=U;
        if(val<L)val=L;

        pf("%lld\n",val);
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
