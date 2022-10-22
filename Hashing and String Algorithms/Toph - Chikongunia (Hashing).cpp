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
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const int N = 1e5+5;
const int _hashCnt=2;
const int mod1 = (1LL<<31)-1;
const int bases[_hashCnt] = {rand(11887,1<<21),rand(15661,1<<22)};

vector<int>P[_hashCnt];
inline int mod(ll x) {
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}
struct Hash{
    vector<int>H[_hashCnt];
    int n;
    inline void initP(int ind){
        while((int)P[ind].size()<=n){
            if(P[ind].empty())P[ind].push_back(1);
            else P[ind].push_back(mod(1LL*P[ind].back()*bases[ind]));
        }
    }
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            initP(ind);
            H[ind].resize(n+1);H[ind][0]=0;
            for(int i=0; i<n; i++){
                H[ind][i+1] = mod(1LL*H[ind][i] + 1LL*s[i]*P[ind][i]);
            }
        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0,bool flag=0){
        int h = H[ind][r] - H[ind][l-1];
        if(h<0)h+=mod1;
        if(flag)return h;
        return mod(1LL*h*P[ind][n-r]);
    }
    inline ll getHash(int l, int r){return combineHash(singleHash(l,r,0), singleHash(l,r,1));}

    ll modifiedHash(int pos, char newChar){
        int left1=0,right1=0,left2=0,right2=0;
        if(pos>1){
                left1=singleHash(1,pos-1,0,1);
                left2=singleHash(1,pos-1,1,1);
        }
        if(pos<n){
                right1=singleHash(pos+1,n,0,1);
                right2=singleHash(pos+1,n,1,1);
        }
        int combinedHash1 = mod((ll)left1 + 1LL*newChar*P[0][pos-1] + (ll)right1);
        int combinedHash2 = mod((ll)left2 + 1LL*newChar*P[1][pos-1] + (ll)right2);
        return combineHash(combinedHash1,combinedHash2);
    }
};


char s[N];

inline void Solve(int Case){
    int n,m;
    sii(n,m);
    unordered_map<ll,int>mp;
    mp.max_load_factor(0.25);
    ll ans=0;

    FOR(i,n){
        sf(" %s",&s);
        Hash a(s,m);
        mp[a.getHash(1,m)]++;

        for(int j=1; j<=m; j++){
            for(char c='a'; c<='z'; c++){
                if(c==s[j-1])continue;
                ll h1 = a.modifiedHash(j,c);
                if(mp.count(h1))ans+=mp[a.modifiedHash(j,c)];
            }
        }
    }
    pf("%lld\n",ans);
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
