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
const int N = 5e5+5;

const int _hashCnt=2;
const int mod1 = (1LL<<31)-1;
const int bases[_hashCnt] = {rand(11887,1<<21),rand(15661,1<<22)};

int P[_hashCnt][15];
int H[2][13];
inline int mod(ll x) {
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            H[ind][0]=0;
            for(int i=0;i<n; i++){
                H[ind][i+1] = mod((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]));
            }
        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - mod(1LL*H[ind][l-1] * P[ind][r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline ll getHash(int l, int r){return combineHash(singleHash(l,r,0), singleHash(l,r,1));}
};

vector<vector<int> >strings;
int hashCnt[550005]={0};
int ans[N]={0};

struct query{
    int ind,l,r,x,curHash;
    query(){}
    query(int ind, int l, int r, int x, int curHash):ind(ind),l(l),r(r),x(x),curHash(curHash){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return (x&1)?r<q.r:r>q.r;
    }
}queries[N];

inline void Add(int x){
    for(int i:strings[x])hashCnt[i]++;
}
inline void Remove(int x){
    for(int i:strings[x])hashCnt[i]--;
}

inline void Solve(int Case){
    char s[15];
    int n;
    sf("%d",&n);
    int Div = sqrt(n)+5;
    map<ll,int>mappedHash;
    int cnt=0;
    for(int i=0; i<n; i++){
        sf(" %s",&s);
        int len=strlen(s);
        Hash curHash(s,len);

        orderSet<ll>st;
        for(int j=1; j<=len; j++){
            for(int k=1; k+j-1<=len; k++)st.insert(curHash.getHash(k,k+j-1));
        }

        vector<int>substringHashes;
        for(ll h:st){
            if(!mappedHash.count(h)){
                mappedHash[h]=cnt++;
            }
            substringHashes.push_back(mappedHash[h]);
        }
        strings.push_back(substringHashes);
    }

    int m;
    sf("%d",&m);

    for(int i=0,l,r,len; i<m; i++){
        sf("%d%d %s",&l,&r,&s);
        len=strlen(s);
        int curH[2]={0};

        for(int ind=0; ind<_hashCnt; ind++){
            curH[ind]=0;
            for(int j=0; j<len; j++){
                curH[ind] = mod(1LL*curH[ind]*bases[ind] + (ll)s[j]);
            }
        }

        ll curHash = (ll(curH[0])<<32)^ll(curH[1]);
        if(mappedHash.count(curHash))curHash=mappedHash[curHash];
        else curHash=-1;
        queries[i]=query(i,l-1,r-1,l/Div,(int)curHash);
    }

    sort(queries,queries+m);
    int l=0,r=-1;

    for(int i=0; i<m; i++){
        //printf("%d %d %d\n",queries[i].l, queries[i].r, queries[i].curHash);
        if(queries[i].curHash==-1){
            ans[queries[i].ind]=0;
            continue;
        }
        while(l<queries[i].l)Remove(l++);
        while(l>queries[i].l)Add(--l);
        while(r<queries[i].r)Add(++r);
        while(r>queries[i].r)Remove(r--);
        ans[queries[i].ind]=hashCnt[queries[i].curHash];
    }

    for(int i=0; i<m; i++)printf("%d\n",ans[i]);


}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  //#define fastio
int main(){
    for(int i=0; i<_hashCnt; i++){
        P[i][0]=1;
        for(int j=1; j<=14; j++)P[i][j] = mod(1LL*P[i][j-1]*bases[i]);
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
