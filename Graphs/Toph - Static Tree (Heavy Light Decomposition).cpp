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
const int N = 2e5+5;

char s[N],inp[N];
vector<int>graph[N];

struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>discoveryTime,lvl,lgVal;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(){}
    LCA(int n, int root=1):n(n),discoveryTime(n+1),lvl(n+1),lgVal(1+n<<1){
        lvl[root]=0;
        Time=0;
        for(int i=2,lim=n+n; i<=lim; i++)lgVal[i]=lgVal[(i>>1)]+1;
        LOG = lgVal[n]+2;
        sparseTable.resize(LOG, vector<int>(1+n<<1));
        dfs(root,-1);

        for(int i=1; i<LOG; i++){
            for(int j=1; j+(1<<i)-1<=Time; j++){
                int left=sparseTable[i-1][j];
                int right=sparseTable[i-1][j+(1<<(i-1))];
                if(lvl[left]<lvl[right])sparseTable[i][j] = left;
                else sparseTable[i][j] = right;
            }
        }
    }

    void dfs(int u, int p){
        discoveryTime[u]=++Time;
        sparseTable[0][Time]=u;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
    }

    inline int lca(int u, int v){
        u=discoveryTime[u];
        v=discoveryTime[v];
        if(u>v)swap(u,v);
        int logVal = lgVal[v-u+1];
        int x=sparseTable[logVal][u];
        int y=sparseTable[logVal][v-(1<<logVal)+1];
        if(lvl[x]<lvl[y])return x;
        return y;
    }
}lca;


namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);

    struct data{
        int mx,mn;
        data(){mx=-1,mn=INT_MAX;}
        data(int mx, int mn):mx(mx),mn(mn){}
    }Tree[27][2*N];

    inline data Merge(data a, data b){
        return data(max(a.mx,b.mx),min(a.mn,b.mn));
    }

    void tree_update(int pos, int c, bool b){
        int ind=pos;
        pos+=posCnt-1;
        if(b)Tree[c][pos]=data(ind,ind);
        else Tree[c][pos]=data(-1,INT_MAX);
        for(;pos>1; pos>>=1)Tree[c][pos>>1] = Merge(Tree[c][pos],Tree[c][pos^1]);
    }

    data tree_query(int l, int r, int c){
        if(l>r)return data(-1,INT_MAX);
        l+=posCnt-1;
        r+=posCnt;
        data ret(-1,INT_MAX);
        for(;l<r; l>>=1,r>>=1){
            if(l&1)ret=Merge(ret,Tree[c][l++]);
            if(r&1)ret=Merge(ret,Tree[c][--r]);
        }
        return ret;
    }

    inline void addChar(int pos, int c){tree_update(pos,c,1);}
    inline void removeChar(int pos, int c){tree_update(pos,c,0);}
    inline void changeChar(int pos, int c){
        removeChar(posInChain[pos],s[pos]-'a');
        s[pos]=c;
        addChar(posInChain[pos],s[pos]-'a');
    }

    inline int getnextMin(int l, int r, int c){return tree_query(l,r,c).mn;}
    inline int getnextMax(int l, int r, int c){return tree_query(l,r,c).mx;}

    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        for(int i=1; i<=posCnt; i++)addChar(i,s[chainArr[i]]-'a');
    }

    bool query(int u, int v, int inplen){
        int L = lca.lca(u,v);
        int curlen=1;

        ///u to L
        while(curlen<=inplen){
            if(chainRoot[u]==chainRoot[L]){
                int nxt = getnextMax(posInChain[L],posInChain[u],inp[curlen]-'a');
                while(curlen<=inplen && nxt!=-1){
                    curlen++;
                    if(curlen>inplen)return 1;
                    nxt = getnextMax(posInChain[L],nxt-1,inp[curlen]-'a');
                }
                break;
            }

            int nxt = getnextMax(posInChain[chainRoot[u]],posInChain[u], inp[curlen]-'a');
            while(curlen<=inplen && nxt!=-1){
                curlen++;
                if(curlen>inplen)return 1;
                nxt = getnextMax(posInChain[chainRoot[u]], nxt-1, inp[curlen]-'a');
            }
            u=parent[chainRoot[u]];
        }
        //dbug(curlen);
        if(curlen>inplen)return 1;

        ///L+1 to v
        vector<pii>chains;
        while(1){
            if(chainRoot[v]==chainRoot[L]){
                chains.emplace_back(pii(L,v));
                break;
            }
            chains.emplace_back(pii(chainRoot[v],v));
            v=parent[chainRoot[v]];
        }
        reverse(all(chains));

        for(pii &cur:chains){
            if(curlen>inplen)return 1;
            int a=cur.ff;
            int b=cur.ss;
            if(a==L){
                int nxt = getnextMin(posInChain[a]+1, posInChain[b],inp[curlen]-'a');
                while(nxt!=INT_MAX && curlen<=inplen){
                    curlen++;
                    if(curlen>inplen)return 1;
                    nxt = getnextMin(nxt+1, posInChain[b], inp[curlen]-'a');
                }
            }
            else{

                int nxt = getnextMin(posInChain[a], posInChain[b], inp[curlen]-'a');
                while(nxt!=INT_MAX && curlen<=inplen){
                    curlen++;
                    if(curlen>inplen)return 1;
                    nxt = getnextMin(nxt+1, posInChain[b], inp[curlen]-'a');
                }
            }

        }

        if(curlen>inplen)return 1;
        return 0;
    }

    int dfs(int u, int p){
        parent[u]=p;
        int ret=1, mx=0,nxt=-1,subtreeSize;
        for(int v:graph[u]){
            if(v==p)continue;
            lvl[v]=lvl[u]+1;
            subtreeSize=dfs(v,u);
            ret+=subtreeSize;
            if(subtreeSize>mx){
                mx=subtreeSize;
                nxt=v;
            }
        }
        maxSubtree[u]=nxt;
        return ret;
    }

    void hld(int u, int p, int chainParent){
        chainRoot[u]=chainParent;
        posInChain[u]=++posCnt;
        chainArr[posCnt]=u;

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
    }

}

inline void Solve(int Case){
    int n,m;
    sii(n,m);
    sf(" %s",s+1);
    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }


    HLD::init(n,1);
    lca = LCA(n,1);
    int t,x,u,v;
    char c;

    while(m--){
       // si(t);
       // if(t==1){
      //      sf("%d %c",&x,&c);
      //      HLD::changeChar(x,c);
      //  }
       // else{
            sf("%d %d %s",&u,&v,inp+1);
            if(HLD::query(u,v,strlen(inp+1)))pf("Yes\n");
            else pf("No\n");
       // }
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
