#include<bits/stdc++.h>
/// https://www.hackerrank.com/contests/ab-yeh-kar-ke-dikhao/challenges/jitu-and-strings/problem
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
(uint64_t) __builtin_ia32_rdtsc()};
mt19937 rng(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}
template<typename T>inline bool MAX(T &a, T b){return b>a?a=b,1:0;}
template<typename T>inline bool MIN(T &a, T b){return b<a?a=b,1:0;}
inline bool checkBit(int n, int pos){return bool(n&(1<<pos));}
inline int setBit(int n, int pos){return n|(1<<pos);}
inline int toggleBit(int n, int pos){return n^(1<<pos);}
const double PI = 2*acos(0.0);
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const int N = 2e5+5;
int n;
char S[N],T[N];
int P[2][N];
const int MOD = (1LL<<31)-1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};
int H[2][N];

inline int mod(ll x) {
        x+=MOD;
        x=(x>>31)+(x&MOD);
        return int((x>>31)+(x&MOD));
}

pii Tree[N*4];

inline pii combine(pii a, pii b){
    return pii(mod(1LL*a.first+1LL*b.first), mod(1LL*a.second+1LL*b.second));
}
void build(int node, int l, int r){
    if(l==r){
            Tree[node].first = mod(1LL*S[l-1]*P[0][l-1]);
            Tree[node].second = mod(1LL*S[l-1]*P[1][l-1]);
    }
    else{
        int mid = (l+r)/2;
        build(node*2, l, mid);
        build(node*2+1, mid+1,r);
        Tree[node] = combine(Tree[node*2], Tree[node*2+1]);
    }
}

void update(int node, int l, int r, int pos, char val){
    if(l>r || l>pos || r<pos)return;
    if(l==pos && r==pos){
            Tree[node].first = mod(1LL*val*P[0][l-1]);
            Tree[node].second = mod(1LL*val*P[1][l-1]);
    }
    else{
        int mid = (l+r)/2;
        if(pos<=mid)update(node*2, l, mid, pos, val);
        else update(node*2+1, mid+1, r, pos, val);
        Tree[node] = combine(Tree[node*2], Tree[node*2+1]);
    }
}

pii query(int node, int l, int r, int posl, int posr){
    if(l>r || r<posl || l>posr)return {0,0};
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)/2;
    return combine(query(node*2,l,mid,posl,posr), query(node*2+1,mid+1,r,posl,posr));
}

void makeHashT(){
    for(int ind=0; ind<2; ind++){
        H[ind][0]=0;
        for(int i=0; i<n; i++)
            H[ind][i+1] = mod(1LL*H[ind][i]+(1LL*P[ind][i]*T[i]));
    }
}

inline ll getHashT(int l, int r){
    int h1 = H[0][r]-H[0][l-1];
    if(h1<0)h1+=MOD;
    int h2 = H[1][r]-H[1][l-1];
    if(h2<0)h2+=MOD;
    h1 = mod(1LL*h1*P[0][n-l]);
    h2 = mod(1LL*h2*P[1][n-l]);
    return ((ll)h1<<32)^(ll)h2;
}

inline ll getHashS(int l, int r){
    pii q = query(1,1,n,l,r);
    q.first = mod(1LL*q.first*P[0][n-l]);
    q.second = mod(1LL*q.second*P[1][n-l]);
    return ((ll)q.first<<32)^(ll)q.second;
}


inline void Solve(int Case){
    si(n);
    sf(" %s %s",&S,&T);
    build(1,1,n);
    makeHashT();

    int firstMismatch=-1;
    for(int i=0; i<n; i++){
            if(S[i]!=T[i]){
                firstMismatch=i;
                break;
            }
    }

    if(firstMismatch==-1){
        printf("%d\n",n);
        return;
    }

    char requiredChar = T[firstMismatch];
    vector<int>charPos;
    for(int i=firstMismatch+1; i<n; i++)
        if(S[i]==requiredChar)charPos.push_back(i);

    int maxlen = firstMismatch;
    int low,high,mid;

    for(int newpos:charPos){
        update(1,1,n,newpos+1,S[firstMismatch]);
        update(1,1,n,firstMismatch+1,S[newpos]);

        low=firstMismatch+1;
        high=n;
        while(low<=high){
            mid=(low+high)/2;
            if(getHashS(1,mid)==getHashT(1,mid)){
                maxlen=max(maxlen,mid);
                low=mid+1;
            }
            else high=mid-1;
        }

        update(1,1,n,newpos+1,S[newpos]);
        update(1,1,n,firstMismatch+1,S[firstMismatch]);
    }

    pf("%d\n",maxlen);

}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  //#define fastio
int main(){
    for(int i=0; i<2; i++){
        P[i][0]=1;
        for(int j=1; j<N; j++)P[i][j] = mod(1LL*P[i][j-1]*bases[i]);
    }
    Solve(0);

return 0;
}
