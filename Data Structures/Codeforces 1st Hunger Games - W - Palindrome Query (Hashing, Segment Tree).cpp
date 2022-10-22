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
const int MOD = (1LL<<31)-1;
const int N = 1e5+5;

inline int mod(ll x) {
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}

const int _hashCnt=1;
int P[_hashCnt][N];
const int bases[2] = {rand(1321,1<<22), rand(1325, 1<<22)};

struct Hash{
    int h[_hashCnt];
    int cnt;
    bool isReverse;

    Hash(bool isReverse){
        for(int i=0; i<_hashCnt; i++)h[i]=0;
        cnt=0;
        this->isReverse=isReverse;
    }
    void update(int c, int cnt){
        for(int i=0; i<_hashCnt; i++)h[i]=c;
        this->cnt=cnt;
    }
    Hash operator+(const Hash &H)const{
        Hash ret(isReverse);
        ret.cnt = cnt+H.cnt;
        for(int i=0; i<_hashCnt; i++){
                if(isReverse)ret.h[i] = mod(1LL*h[i] + mod(1LL*H.h[i]*P[i][cnt]));
                else ret.h[i] = mod(1LL*H.h[i] + mod(1LL*h[i]*P[i][H.cnt]));
        }
        return ret;
    }
};

struct segTree{
    vector<Hash>Tree;
    int n;
    bool ReverseFlag;
    segTree(){}
    segTree(int n, bool ReverseFlag=0):n(n),ReverseFlag(ReverseFlag),Tree(4*n,ReverseFlag){}

    void update(int node, int l, int r, int pos, int c, int val){
        if(l>r || l>pos || r<pos)return;
        if(l==pos && r==pos)Tree[node].update(c,val);
        else{
            int mid = (l+r)>>1;
            if(pos<=mid)update(node*2, l, mid, pos, c, val);
            else update(node*2+1, mid+1, r, pos, c, val);
            Tree[node] = Tree[node*2] + Tree[node*2+1];
        }
    }

    Hash query(int node, int l, int r, int posl, int posr){
        if(l>r || l>posr || r<posl)return Hash(ReverseFlag);
        if(l>=posl && r<=posr)return Tree[node];
        int mid = (l+r)>>1;
        return query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr);
    }

    inline int getHash(int l, int r){
        Hash H = query(1,1,n,l,r);
        return H.h[0];
    }
};

char s[N];

inline void Solve(int Case){
    int n,q;
    sf("%s",&s);
    n=strlen(s);

    for(int i=0; i<_hashCnt; i++){
        P[i][0]=1;
        for(int j=1; j<=n+1; j++){
                P[i][j] = mod(1LL*P[i][j-1] * bases[i]);
                //dbug(P[i][j]);
                //pf("base: %d\n",bases[i]);
        }
    }

    segTree F(n,0),R(n,1);

    for(int i=0; i<n; i++){
        //dbug(P[1][i]);
        F.update(1,1,n,i+1,s[i],1);
        R.update(1,1,n,i+1,s[i],1);
    }

    si(q);
    int qt,p;
    char x;

    while(q--){
       // int l,r;
       // sii(l,r);
       // dbug(F.getHash(l,r));
       // dbug(R.getHash(l,r));
        si(qt);
        if(qt==1){
            sf("%d %c",&p,&x);
            F.update(1,1,n,p,x,1);
            R.update(1,1,n,p,x,1);
        }
        else if(qt==2){
            sf("%d",&p);
            int mx=-1,low=1,high=min(p,n-p+1);
            int mid;
            while(low<=high){
                mid=(low+high)>>1;
                //pf("%d - %d\n",p-mid+1, p+mid-1);
                //dbug(F.getHash(p-mid+1,p));
                //dbug(R.getHash(p,p+mid-1));
                //pf("2-------\n");
                if(F.getHash(p-mid+1,p) == R.getHash(p,p+mid-1)){
                    mx=max(mx,mid);
                    low=mid+1;
                }
                else high=mid-1;
            }
            pf("%d\n",mx+mx-1);
        }
        else if(qt==3){
            sf("%d",&p);
            int mx=-1,low=1,high=min(p,n-p);
            int mid;
            while(low<=high){
                mid=(low+high)>>1;
                //pf("%d - %d\n",p-mid+1, p+1+mid-1);
                //dbug(F.getHash(p-mid+1,p));
                //dbug(R.getHash(p+1,p+mid));
                //pf("3-------\n");
                if(F.getHash(p-mid+1,p) == R.getHash(p+1,p+mid)){
                    mx=max(mx,mid);
                    low=mid+1;
                }
                else high=mid-1;
            }
            if(mx==-1)pf("-1\n");
            else pf("%d\n",mx+mx);
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
