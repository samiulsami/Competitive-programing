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

const int _chars=26;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0;
        ll cnt=0;
        trienode(){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back();}

    void insert(const char *s, ll cnt){
        int id=0;
        for(int i=0; s[i]; i++){
            int c = s[i]-'a';
            if(!trie[id].next[c]){
                trie.emplace_back();
                trie[id].next[c]=(int)trie.size()-1;
            }
            id = trie[id].next[c];
        }
        trie[id].cnt+=cnt;
    }

    void build(){
        queue<int>q;
        q.push(0);
        while(!q.empty()){
            int id = q.front();
            q.pop();
            for(int c=0; c<_chars; c++){
                if(trie[id].next[c]){
                    trie[trie[id].next[c]].link = id ? trie[trie[id].link].next[c] : 0;
                    q.push(trie[id].next[c]);
                    trie[trie[id].next[c]].cnt+=trie[trie[trie[id].next[c]].link].cnt;
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'a'];
    }
};

const ll INF = 1e18;
template<typename T>
struct Matrix{
    vector<vector<T> >mat;
    int rows,cols;

    Matrix(){}
    Matrix(int rows, int cols):rows(rows),cols(cols),mat(rows, vector<T>(cols,-INF)){}
    Matrix(vector<vector<T> >val): mat(val), rows((int)val.size()), cols((int)val[0].size()){}

    Matrix operator*(const Matrix &mtrx)const{
        Matrix ret(rows,mtrx.cols);
        for(int i=0; i<rows; i++){
            for(int j=0; j<mtrx.cols; j++){
                    for(int k=0; k<cols; k++){
                        ret.mat[i][j] = max(ret.mat[i][j], (mat[i][k] + mtrx.mat[k][j]));
                    }
            }
        }
        return ret;
    }
};

template<typename T>
Matrix<T> fast_exponentiation(Matrix<T> m, long long p){
    Matrix<T> ret(m.rows,m.rows);
    for(int i=0; i<ret.rows; i++)ret.mat[i][i]=0;
    while(p){
        if(p&1)ret = ret*m;
        m = m*m;
        p>>=1;
    }
    return ret;
}

char s[250];

inline void Solve(int Case){
    int n,m;
    sii(n,m);
    AhoCorasick ac;
    for(int i=0; i<m; i++){
        int x;
        sf(" %s %d",&s,&x);
        ac.insert(s,x);
    }
    ac.build();
    int t=sz(ac.trie);
    Matrix<ll> mat(t,t);

    for(int i=0; i<t; i++){
        for(int j='a'; j<='z'; j++){
            mat.mat[i][ac.getnext(i,j)]=ac.trie[ac.getnext(i,j)].cnt;
        }
    }

    Matrix<ll> ans = fast_exponentiation(mat,n);
    ll mx=-INF;
    for(int i=0; i<t; i++)mx=max(mx,ans.mat[0][i]);
    pf("%lld\n",mx);
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
