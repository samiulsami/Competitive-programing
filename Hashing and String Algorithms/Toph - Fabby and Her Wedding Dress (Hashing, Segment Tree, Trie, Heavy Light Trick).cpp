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
const int base = rand(11887,1<<21);
const int N = 2e5+5;
const int K=100;
int maxN=2e5+2;
int P[N];

inline int mod(ll x) {
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}


struct segTree{
    int n;
    vector<int>Tree;
    segTree(){}
    segTree(int n):n(n),Tree(2*n){}

    void update(int ind, int c){///0-indexed
        Tree[ind+n] = mod(1LL*c*P[ind]);
        ind+=n;
        for(;ind>1; ind>>=1)Tree[ind>>1] = mod(1LL*Tree[ind] + 1LL*Tree[ind^1]);
    }

    int query(int l, int r){///1-indexed
        int tmpr=r;
        l+=n-1;
        r+=n;
        int ret=0;
        for(;l<r; l>>=1,r>>=1){
            if(l&1)ret=mod(1LL*ret+1LL*Tree[l++]);
            if(r&1)ret=mod(1LL*ret+1LL*Tree[--r]);
        }
        ret = mod(1LL*ret*P[maxN-tmpr]);
        return ret;
    }
};

int getHash(string &s){
    int len=s.length();
    int ret=0;
    for(int i=0; i<len; i++){
        ret = mod(1LL*ret + 1LL*s[i]*P[i]);
    }
    ret = mod(1LL*ret*P[maxN-len]);
    return ret;
}

const int _charCnt=26;
struct trienode{
    trienode *nxt[_charCnt];
    int cnt=0;
};
stack<trienode*> nodeStack;

void trie_insert(trienode *root, string &s){
    trienode *cur=root;
    int len=min(K,sz(s));
    for(int i=0; i<len; i++){
        int ind=s[i]-'a';
        if(cur->nxt[ind]==NULL){
            if(nodeStack.empty())nodeStack.push(new trienode());
            cur->nxt[ind] = nodeStack.top();
            nodeStack.pop();
        }
        cur=cur->nxt[ind];
        cur->cnt++;
    }
}

int trie_count(trienode *root, string &s){
    trienode *cur=root;
    int len=min(K,sz(s));
    for(int i=0; i<len; i++){
        int ind=s[i]-'a';
        if(cur->nxt[ind])cur=cur->nxt[ind];
        else return 0;
    }
    return cur->cnt;
}

void trie_del(trienode *root, string &s){
    trienode *cur=root;
    int len=min(K,sz(s));

    for(int i=0; i<len; i++){
        int ind=s[i]-'a';
        trienode *prev=cur;
        cur=cur->nxt[ind];
        cur->cnt--;
        if(cur->cnt==0){
            prev->nxt[ind]=NULL;
            nodeStack.push(cur);
        }
    }

}

inline void Solve(int Case){

    int n;
    cin>>n;
    P[0]=1;
    for(int i=1; i<=maxN+2; i++)P[i]=mod(1LL*P[i-1]*base);

    vector<string>strings(n+1);
    vector<int>id(n+1);
    vector<segTree>heavy;
    trienode *lightRoot = new trienode();

    for(int i=1; i<=n; i++){
        cin>>strings[i];
        if(sz(strings[i])<K){
            trie_insert(lightRoot,strings[i]);
            id[i]=i;
        }
        else{
            int len=sz(strings[i]);
            trie_insert(lightRoot,strings[i]);
            id[i]=sz(heavy);
            segTree tmp(len);
            for(int j=0; j<len; j++)tmp.update(j,strings[i][j]);
            heavy.emplace_back(tmp);
        }
    }

    int queries,qt,i,j;
    char c;
    string tmp;
    cin>>queries;
    while(queries--){
        cin>>qt;
        if(qt==1){
            cin>>i>>j>>c;
            if(sz(strings[i])<K){
                trie_del(lightRoot,strings[i]);
                strings[i][j-1]=c;
                trie_insert(lightRoot,strings[i]);
            }
            else{
                int heavyID=id[i];
                trie_del(lightRoot,strings[i]);
                strings[i][j-1]=c;
                trie_insert(lightRoot,strings[i]);
                heavy[heavyID].update(j-1,c);
            }
        }
        else{
            cin>>tmp;
            if(sz(tmp)<K){
                    int ans=trie_count(lightRoot,tmp);
                    cout<<ans<<endl;
            }
            else{
                int Hash=getHash(tmp);
                int ans=0;
                for(segTree &st:heavy){
                    if(st.n>=sz(tmp)){
                        if(st.query(1,sz(tmp)) == Hash)ans++;
                    }
                }

                cout<<ans<<endl;
            }
        }
    }

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
