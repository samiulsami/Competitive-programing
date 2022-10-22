#include<bits/stdc++.h>
/*
    Problem: SPOJ NHAY - A Needle in the Haystack
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
mt19937 rng(ull(chrono::steady_clock::now().time_since_epoch().count())^ull(new ull));
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
const int SZ = 1e5+5;

const int mod1 = 1000005541;
const int mod2 = 1000011823;
const int b1 = rand(149,1<<10), b2 = rand(137,1<<9);

vector<pair<int,int> >P{{1,1}};

struct Hash{
    vector<pair<int,int> >H;
    int n;
    Hash(string &s, int n):n(n), H(n+2){
        while((int)P.size()<=n+1)
            P.push_back({(1LL*P.back().first*b1)%mod1, (1LL*P.back().second*b2)%mod2});

        for(int i=0; i<n; i++){
            H[i+1].first = (1LL*H[i].first + (1LL*(s[i]-'a'+1)*P[i].first))%mod1;
            H[i+1].second = (1LL*H[i].second + (1LL*(s[i]-'a'+1)*P[i].second))%mod2;
        }
    }

    pair<int,int> getHash(int l, int r){
        int h1 = (H[r].first-H[l-1].first+mod1)%mod1;
        h1 = (1LL*h1*P[n-r].first)%mod1;
        int h2 = (H[r].second-H[l-1].second+mod2)%mod2;
        h2 = (1LL*h2*P[n-r].second)%mod2;
        return {h1,h2};
    }
};

pair<int,int> computeHash(string &s, int n){
    int h1=0,h2=0;
    while((int)P.size()<=n+1)
            P.push_back({(1LL*P.back().first*b1)%mod1, (1LL*P.back().second*b2)%mod2});

    for(int i=0; i<n; i++){
        h1 = (1LL*h1 + (1LL*(s[i]-'a'+1)*P[i].first))%mod1;
        h2 = (1LL*h2 + (1LL*(s[i]-'a'+1)*P[i].second))%mod2;
    }
    return {h1,h2};
}

string a,b;
int n,m;

inline void Solve(int Case){

    while(cin>>n){
        cin>>a>>b;
        m = (int)b.length();
        pii needleHash = computeHash(a,n);
        Hash haystack(b,m);

        needleHash.first = (1LL*needleHash.first*P[max(0,m-n)].first)%mod1;
        needleHash.second = (1LL*needleHash.second*P[max(0,m-n)].second)%mod2;

        for(int i=1,len=(int)b.length(); i<=len-n+1; i++){
            if(needleHash==haystack.getHash(i,i+n-1))cout<<i-1<<endl;
        }

        cout<<endl;
    }


}

  //#define Multiple_Test_Cases
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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
