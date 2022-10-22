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

int grid[35][35];
bool col[500]={0};
bool row[500]={0};

struct Dinic{
        struct edge{
            int u,v,cap,flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        vector<edge>edges;
        vector<vector<int> > graph;
        vector<int> lvl,nxt;
        int n,edge_cnt,S,T;

        Dinic(int n):n(n),graph(n),lvl(n),nxt(n){
            edge_cnt=0;
        }

        void addEdge(int u, int v, int cap){
            edges.emplace_back(u,v,cap);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0);
            graph[v].push_back(edge_cnt++);
        }

        bool bfs(){
            queue<int>q;
            q.push(S);
            fill(lvl.begin(),lvl.end(),-1);
            lvl[S]=0;
            while(!q.empty()){
                int u=q.front();
                if(u==T)break;
                q.pop();
                for(int edgeID : graph[u]){
                    edge &v = edges[edgeID];
                    if(v.cap<=v.flow || lvl[v.v]!=-1)continue;
                    lvl[v.v]=lvl[u]+1;
                    q.push(v.v);
                }
            }
            return lvl[T]!=-1;
        }

        int dfs(int u, int pathFlow){
            if(pathFlow==0 || u==T)return pathFlow;
            int ret=0;
            int id;
            for(int &edgeID=nxt[u]; edgeID<(int)graph[u].size(); edgeID++){
                id = graph[u][edgeID];
                edge &v = edges[id];
                if(lvl[v.v]!=lvl[u]+1 || v.cap<=v.flow)continue;
                if(ret=dfs(v.v, min(pathFlow, v.cap-v.flow))){
                    edges[id].flow+=ret;
                    edges[id^1].flow-=ret;
                    return ret;
                }
            }
            return 0;
        }

        int maxFlow(int s, int t){
            S=s;
            T=t;
            int flow=0,f=0;
            while(bfs()){
                fill(nxt.begin(),nxt.end(),0);
                while(f=dfs(S,INT_MAX))flow+=f;
            }
            return flow;
        }

};


inline void Solve(int Case){
    int n;
    si(n);
    FOR(i,n)FOR(j,n)si(grid[i][j]);

    if(n==1){
        pf("%d\n",grid[0][0]);
        return;
    }
    int source=n+n+2;
    int sink=source+1;
    int low=1,high=1e6,mid,ans=0;

    while(low<=high){
        mid = (low+high)>>1;
        Dinic dinic(n+n+10);

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j]>=mid){
                    dinic.addEdge(i,j+n,1);
                }
            }
        }
        for(int i=0; i<n; i++){
                dinic.addEdge(source,i,1);
                dinic.addEdge(i+n,sink,1);
        }

        int mxflow=dinic.maxFlow(source,sink);
        //dbug(mxflow);
        if(mxflow<n){
            high=mid-1;
        }
        else{
            ans=max(ans,mid);
            low=mid+1;
        }
    }

    pf("%d\n",ans);

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
