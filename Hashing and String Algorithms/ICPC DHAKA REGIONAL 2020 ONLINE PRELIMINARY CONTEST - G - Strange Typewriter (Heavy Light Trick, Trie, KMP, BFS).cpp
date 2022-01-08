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

struct node{
    int nxt[26]={0};
    bool terminal=0;
    node(){}
};

vector<node>Trie;

void add(const char *s){
    int id=0;
    for(int i=0; s[i]; i++){
        int c=s[i]-'a';
        if(!Trie[id].nxt[c]){
            Trie.emplace_back();
            Trie[id].nxt[c]=sz(Trie)-1;
        }
        id = Trie[id].nxt[c];
    }
    Trie[id].terminal=1;
}

int len;
vector<int>graph[100005];
char s[100005];
int lvl[100005];

int bfs(){
    for(int i=0; i<=len; i++)lvl[i]=-1;
    lvl[0]=0;
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int top=q.front();
        q.pop();
        if(top==len)return lvl[len];
        for(int v:graph[top]){
            v++;
            if(lvl[v]==-1){
                lvl[v]=lvl[top]+1;
                q.push(v);
            }
        }
    }
    return -1;
}

vector<int> getheavy(string t){
    vector<int>pi(sz(t));
    for(int i=1,j; i<sz(t); i++){
        j=pi[i-1];
        while(j>0 && t[i]!=t[j])j=pi[j-1];
        if(t[i]==t[j])pi[i]=j+1;
        else pi[i]=0;
    }
    return pi;
}

inline void Solve(int Case){
    int n;
    sf("%d",&n);

    Trie.clear();
    Trie.emplace_back();
    vector<pair<vector<int>,string> >heavy;
    for(int i=0; i<n; i++){
        sf(" %s",&s);
        len=strlen(s);
        if(len<=1000)add(s);
        else{
            string tmp(s);
            heavy.emplace_back(pair<vector<int>, string>(getheavy(tmp),tmp));
        }
    }

    sf(" %s",&s);
    len=strlen(s);
    for(auto &x:heavy){
        int m=sz(x.second);
        string &tmp=x.second;
        if(m>len)continue;
        vi &pi = x.first;
        int j=0;
        for(int i=0; i<len; i++){
            if(s[i]==tmp[j])j++;
            else{
                while(j>0 && s[i]!=tmp[j])j=pi[j-1];
                if(s[i]==tmp[j])j++;
            }
            if(j==m){
                graph[i-m+1].push_back(i);
                j=pi[j-1];
            }
        }
    }

    for(int i=0; i<len; i++){
        int x=0,j=i;
        while(j<len && Trie[x].nxt[s[j]-'a']){
            x=Trie[x].nxt[s[j]-'a'];
            if(Trie[x].terminal)graph[i].push_back(j);
            j++;
        }
        if(!graph[i].empty())graph[i].erase(unique(all(graph[i])),graph[i].end());
    }

    int ans=bfs();
    pf("Case %d: ",Case);
    if(ans==-1)pf("impossible\n");
    else pf("%d\n",ans);
    for(int i=0; i<=len; i++)graph[i].clear();
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
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
