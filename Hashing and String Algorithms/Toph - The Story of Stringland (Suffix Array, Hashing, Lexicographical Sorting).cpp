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
const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
inline int readline(char *s, char d='\n'){int len=0;while((s[len]=getchar())!=d)len++;s[len]='\0';return len;}
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

const int N = 1e6+5;

const ull mod1 = (1ull<<61) - 1;
inline ull hashmodmul(ull a, ull b){
	ull l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	ull ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod1) + (ret>>61);
	ret = (ret & mod1) + (ret>>61);
	return ret-1;
}
inline ull hashAdd(ull a, ull b){a+=b;return a>=mod1?a-mod1:a;}
inline ull hashSub(ull a, ull b){a-=b;return a>=mod1?a+mod1:a;}
const ull base1 = (ull)rand(15661,1<<22);
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    vector<ull>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1),R(n+2){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
            R[j-1] = hashAdd(hashmodmul(R[j], base1), (ull)s[j-2]);
        }
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
    ull reverseHash(int l, int r){return hashSub(R[l], hashmodmul(R[r+1], P[r-l+1]));}
};

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=1e6+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    int Table[21][MAX_N];
    int lgval[MAX_N];
    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const char *s, int nn){
        int i,k,r;
        n=nn;
        for (i = 0; i < n; i++)RA[i] = s[i];
        for (i = 0; i < n; i++)SA[i] = i;
        for (k = 1; k < n; k <<= 1){
            countingSort(k);
            countingSort(0);
            invSA[SA[0]] = r = 0;
            for (i = 1; i < n; i++)invSA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
            for (i = 0; i < n; i++)RA[i] = invSA[i];
            if (RA[SA[n-1]] == n-1) break;
        }
        for(i=0; i<n; i++) invSA[SA[i]]=i;
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            int j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
            Table[0][invSA[i]]=k;
        }
        lgval[0]=lgval[1]=0;
        for(int i=2; i<MAX_N; i++)lgval[i]=lgval[i>>1]+1;
        for(int i=1; i<21; i++){
            for(int j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    inline int lcp(int l, int r){
        l=invSA[l];
        r=invSA[r];
        if(l>r)swap(l,r);
        l++;
        int lg=lgval[r-l+1];
        return min(Table[lg][l],Table[lg][r-(1<<lg)+1]);
    }
};

char s[N];

inline void Solve(int Case){
    sf("%s",&s);
    int n = strlen(s);
    Hash a(s,n);
    s[n]='$';
    SuffixArray::init(s,n+1);

    unordered_map<ull,int>stODD,stEVEN;
    stODD.max_load_factor(0.25);
    stEVEN.max_load_factor(0.25);
    vector<pii>indexes;
    int low,mid,high,mx;
    ull tmpHash;

    for(int i=1; i<=n; i++){
        low=1;
        high=min(i,n-i+1);
        mx=0;
        ///Odd length palindromes
        while(low<=high){
            mid=(low+high)/2;
            if(a.getHash(i-mid+1,i)==a.reverseHash(i,i+mid-1)){
                tmpHash = a.getHash(i-mid+1,i+mid-1);
                low=mid+1;
                mx = max(mx,mid);
            }
            else high=mid-1;
        }

        while(mx>0){
            tmpHash = a.getHash(i-mx+1,i+mx-1);
            if(!stODD.count(tmpHash)){
                stODD[tmpHash]=1;
                indexes.push_back({i-mx+1,i+mx-1});
            }
            else break;
            mx--;
        }

        ///Even length palindromes
        mx=0;
        low=1,high=min(i,n-i);
        while(low<=high){
            mid=(low+high)/2;
            if(a.getHash(i-mid+1,i)==a.reverseHash(i+1,i+mid)){
                tmpHash = a.getHash(i-mid+1,i+mid);
                low=mid+1;
                mx=max(mx,mid);
            }
            else high=mid-1;
        }

        while(mx>0){
            tmpHash = a.getHash(i-mx+1,i+mx);
            if(!stEVEN.count(tmpHash)){
                stEVEN[tmpHash]=1;
                indexes.push_back({i-mx+1,i+mx});
            }
            else break;
            mx--;
        }
    }

    {
        using namespace SuffixArray;
        sort(indexes.begin(),indexes.end(),[&](const pii &aa, const pii &bb)->bool{
            if(aa.ff==bb.ff)return aa<bb;
            int L = lcp(aa.first-1,bb.first-1);
            int sa=(aa.second-aa.first+1);
            int sb=(bb.second-bb.first+1);
            if(L>=min(sa,sb))return aa<bb;
            return s[aa.first-1+L]<s[bb.first-1+L];
        });
    }

    int q,k;
    si(q);
    while(q--){
        si(k);
        if(k>sz(indexes))pf("-1\n");
        else pf("%d %d\n",indexes[k-1].ff,indexes[k-1].ss);
    }
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  #define fastio
int main(){
    #ifdef fastio
        //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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
