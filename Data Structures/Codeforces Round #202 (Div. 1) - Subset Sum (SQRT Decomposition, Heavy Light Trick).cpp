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
const int BLOCK=400;

ll arr[N];
bool isHeavy[N]={0};
vector<int>heavy,light;
vector<vector<int> >Set;
int n,m;
int heavymap[N]={0};
int intersection[N][402]={0};
ll setSum[N]={0};
ll setAdd[N]={0};

void updateHeavy(int ind, ll add){
    setAdd[ind]+=add;
    setSum[ind]+=add*1LL*sz(Set[ind]);
    for(int i=0; i<sz(heavy); i++){
        if(heavy[i]==ind)continue;
        setSum[heavy[i]] += 1LL*intersection[heavy[i]][heavymap[ind]]*add;
    }
}

void updateLight(int ind, ll add){
    for(int i:Set[ind])arr[i]+=add;
    for(int i=0; i<sz(heavy); i++){
        setSum[heavy[i]] += 1LL*intersection[ind][i]*add;
    }
}

ll queryHeavy(int ind){
    return setSum[ind];
}

ll queryLight(int ind){
    ll ret=0;
    for(int i:Set[ind])ret+=arr[i];
    for(int i=0; i<sz(heavy); i++){
        ret += 1LL*intersection[ind][i]*setAdd[heavy[i]];
    }
    return ret;
}


inline void Solve(int Case){
    int q;
    siii(n,m,q);
    Set.push_back(vector<int>());
    for(int i=1; i<=n; i++)sl(arr[i]);
    int hcnt=0;

    for(int i=1,k; i<=m; i++){
        si(k);
        if(k<BLOCK){
                isHeavy[i]=0;
                light.push_back(i);
        }
        else {
                isHeavy[i]=1;
                heavy.push_back(i);
                heavymap[i]=hcnt++;
        }

        vector<int>tmp(k);
        for(int j=0; j<k; j++){
                si(tmp[j]);
                setSum[i]+=arr[tmp[j]];
        }
        Set.push_back(tmp);
    }

    bitset<N>bs;
    for(int i=0; i<sz(heavy); i++){
        bs.reset();
        for(int k:Set[heavy[i]])bs[k]=1;
        for(int j=1; j<=m; j++){
            if(heavy[i]==j)continue;
            for(int k:Set[j]){
                if(bs[k])intersection[j][i]++;
            }
            //printf("pre: %d %d: %d\n",heavy[i],j,intersection[j][heavymap[heavy[i]]]);
        }
    }

    char c;
    int ind;
    ll add;
    while(q--){
        sf(" %c",&c);
        if(c=='?'){
            si(ind);
            ll ans=0;
            if(isHeavy[ind])ans=queryHeavy(ind);
            else ans=queryLight(ind);
            pf("%lld\n",ans);
        }
        else{
            sf("%d %lld",&ind,&add);
            if(isHeavy[ind])updateHeavy(ind,add);
            else updateLight(ind,add);
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
