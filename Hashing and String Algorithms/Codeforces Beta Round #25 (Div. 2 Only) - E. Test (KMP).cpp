#include<bits/stdc++.h>
///Codeforces Beta Round #25 (Div. 2 Only) - E. Test
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

const int N = 1e5+5;

void prefixFunction(string &a, vector<int>&pi){
    int n = a.length();
    pi.resize(n+1);
    pi[0]=0;
    for(int i=1,j; i<n; i++){
        j=pi[i-1];
        while(j>0 && a[i]!=a[j])
            j=pi[j-1];
        if(a[i]==a[j])pi[i]=j+1;
        else pi[i]=0;
    }
}

bool isSubstring(string &a, string &b){
    ///Check if 'a' is a substring of 'b'
    int alen=a.length(),blen=b.length();
    vector<int>pi;
    prefixFunction(a,pi);
    int j=0;
    for(int i=0; i<blen; i++){
        if(b[i]==a[j])j++;
        else{
            if(j>0)j=pi[j-1];
            while(j>0 && a[j]!=b[i])
                j=pi[j-1];
            if(a[j]==b[i])j++;
        }
        if(j==alen)return 1;
    }

    return 0;
}

int check(string &a, string &b){
    ///Check maximum length of suffix of 'a' that is also a prefix of 'b'
    vector<int>pi;
    prefixFunction(b,pi);
    int j=0;
    int alen = a.length(),blen=b.length();
    for(int i=0; i<alen; i++){
        if(a[i]==b[j])j++;
        else{
            if(j>0)j=pi[j-1];
            while(j>0 && a[i]!=b[j])
                j=pi[j-1];
            if(a[i]==b[j])j++;
        }
        if(j==blen && i!=alen-1)j=pi[j-1];
    }
    return j;
}

inline void Solve(int Case){
    string arr[3];
    for(int i=0; i<3; i++){
        cin>>arr[i];
    }
    sort(arr,arr+3,[&](string &a, string &b){return a.length()<b.length();});

    vector<int> prm;
    if(!isSubstring(arr[0],arr[1]) && !isSubstring(arr[0],arr[2]))prm.push_back(0);
    if(!isSubstring(arr[1],arr[2]))prm.push_back(1);
    prm.push_back(2);

    int totalLength = 0;
    for(int i:prm)totalLength+=(int)arr[i].length();
    int ans = totalLength;

    do{
        int matchCnt=0;
        for(int i=0,j,len=sz(prm); i<len-1; i++){
            matchCnt+=check(arr[prm[i]], arr[prm[i+1]]);
        }
        ans=min(ans,totalLength-matchCnt);

    }while(next_permutation(all(prm)));

    cout<<ans<<endl;
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  #define fastio
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
