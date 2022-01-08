#include<bits/stdc++.h>
/*
    Problem: acmp.ru - PROBLEM #1157 Sub-palindromes
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
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
const int SZ = 1e6+5;

const int _hashCnt=2;
const int mods[_hashCnt] = {1003741961,1004766439};
const int bases[_hashCnt] = {rand(137,1<<13),rand(149,1<<15)};

vector<int>P[_hashCnt];

struct Hash{
    vector<int>H[_hashCnt];
    vector<int>R[_hashCnt];
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            while((int)P[ind].size()<=n){
                if(P[ind].empty())P[ind].push_back(1);
                else P[ind].push_back((1LL*P[ind].back()*bases[ind])%mods[ind]);
            }
            H[ind].resize(n+1);H[ind][0]=0;
            R[ind].resize(n+2);R[ind][n+1]=0;R[ind][0]=0;
            for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
                H[ind][i+1] = ((1LL*H[ind][i]*bases[ind]) + (s[i]+1LL))%mods[ind];
                R[ind][j-1] = ((1LL*R[ind][j]*bases[ind]) + (s[j-2]+1LL))%mods[ind];
            }
        }
    }

    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    ll getHash(int l, int r){
        int h1 = H[0][r] - (1LL*H[0][l-1] * P[0][r-l+1])%mods[0];
        int h2 = H[1][r] - (1LL*H[1][l-1] * P[1][r-l+1])%mods[1];
        return combineHash(h1<0?h1+mods[0]:h1, h2<0?h2+mods[1]:h2);
    }
    ll reverseHash(int l, int r){
        int h1 = R[0][l] - (1LL*R[0][r+1] * P[0][r-l+1])%mods[0];
        int h2 = R[1][l] - (1LL*R[1][r+1] * P[1][r-l+1])%mods[1];
        return combineHash(h1<0?h1+mods[0]:h1, h2<0?h2+mods[1]:h2);
    }
};

char s[SZ];

inline void Solve(int Case){
    sf("%s",&s);
    int n = strlen(s);
    Hash stHash(s,n);

    int low,high,mid;
    ll ans=0;
    for(int i=1,len; i<=n; i++){
        low=1;
        high=min(i,n-i+1);
        len=0;
        ///Odd length palindromes
        ///([i-mid+1,i],[i,i+mid-1])
        while(low<=high){
            mid=(low+high)/2;
            if(stHash.getHash(i-mid+1,i)==stHash.reverseHash(i,i+mid-1)){
                low=mid+1;
                len=max(len,mid);
            }
            else high=mid-1;
        }
        ans+=len;

        low=1;
        high=min(i,n-i);
        len=0;
        ///Even length palindromes
        ///([i-mid+1,i],[i+1,i+mid])
        while(low<=high){
            mid=(low+high)/2;
            if(stHash.getHash(i-mid+1,i)==stHash.reverseHash(i+1,i+mid)){
                low=mid+1;
                len=max(len,mid);
            }
            else high=mid-1;
        }
        ans+=len;

    }

    pf("%lld\n",ans);
}

  //#define Multiple_Test_Cases
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
