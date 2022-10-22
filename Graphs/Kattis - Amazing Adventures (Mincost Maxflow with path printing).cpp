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

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int m,n;

char dir(int a, int b){/// a to b
    int i1=a/m, j1 = a%m;
    int i2=b/m, j2 = b%m;
    if(i1<i2)return 'U';
    if(i1>i2)return 'D';
    if(j1<j2)return 'R';
    if(j1>j2)return 'L';
    return '#';
}

namespace mcmf{

        struct edge{
            int u,v;
            ll cap, flow, cost;
            bool flag=0;
            edge(){}
            edge(int u, int v, ll cap, ll cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        const int MAX = 1e5+5;
        const ll INF = 1e18;

        vector<edge>edges;
        vector<int>graph[MAX];
        int parent[MAX];
        ll dist[MAX];
        bool inQueue[MAX];
        int n,edge_cnt,S,T;
        queue<int>q;

        void init(int nn, int SS=0, int TT=0){
            n=nn;
            S=SS;
            T=TT;
            edges.clear();
            for(int i=0; i<n; i++)graph[i].clear();
            edge_cnt=0;
        }

        void addEdge(int u, int v, ll cap, ll cost){
            edges.emplace_back(u,v,cap,cost);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0,-cost);
            graph[v].push_back(edge_cnt++);
            edges.back().flag=1;
        }

        bool spfa(){
            for(int i=0; i<n; i++){
                    parent[i]=-1;
                    dist[i]=INF;
                    inQueue[i]=0;
            }

            dist[S]=0;
            q.push(S);

            while(!q.empty()){
                int u = q.front();
                ll cost = dist[u];
                inQueue[u]=0;
                q.pop();

                for(int id:graph[u]){
                    edge &v = edges[id];
                    if(v.cap<=v.flow)continue;
                    if(cost+v.cost<dist[v.v]){
                        dist[v.v]=cost+v.cost;
                        parent[v.v]=id;
                        if(!inQueue[v.v]){
                                q.push(v.v);
                                inQueue[v.v]=1;
                        }
                    }
                }
            }

            return (dist[T]!=INF);
        }

        pair<ll,ll> MincostMaxflow(int s=-1, int t=-1){
            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }
            if(S==T)return {0,0};

            ll flow=0,cost=0;

            while(spfa()){
                ll min_flow=LLONG_MAX;
                int cur,id;

                cur=T;
                do{
                    id=parent[cur];
                    edge &edgeID = edges[id];
                    min_flow=min(min_flow,(ll)(edgeID.cap-edgeID.flow));
                    cur = edgeID.u;
                }while(cur!=S);

                cur=T;
                do{
                    id=parent[cur];
                    edges[id].flow+=min_flow;
                    edges[id^1].flow-=min_flow;
                    cur=edges[id].u;
                }while(cur!=S);

                flow+=min_flow;
                cost+=dist[T]*min_flow;///If cost is for 1 unit of flow
            }

            return {cost,flow};
        }

        void print(int from1, int from2, int to, int offset){
            string ans,tmp;
            while(1){
                if(from1==to)break;
                for(int id:graph[from1]){
                    edge &e = edges[id];
                    if(!e.flag && (e.cap-e.flow)==0){
                        e.flag=1;
                        if(e.cost>0)ans+=dir(from1-offset,e.v);
                        from1=e.v;
                        break;
                    }
                }
            }

            while(1){
                if(from2==to)break;
                for(int id:graph[from2]){
                    edge &e = edges[id];
                    if(!e.flag && (e.cap-e.flow)==0){
                        e.flag=1;
                        if(e.cost>0)tmp+=dir(e.v,from2-offset);
                        from2=e.v;
                        break;
                    }
                }
            }

            reverse(all(tmp));
            cout<<ans<<tmp<<endl;

        }
}

int get(int x, int y){
    if(x>=0 && x<n && y>=0 && y<m)return y+x*m;
    return -1;
}

inline void Solve(int Case){
    sii(n,m);
    if(m==0 && n==0)exit(0);
    int offset=n*m;
    mcmf::init(2*n*m+10);
    int source=offset+offset+2;
    int sink=source+1;

    int rb,cb,rg,cg,rc,cc,ru,cu;
    sii(rb,cb);
    sii(rc,cc);
    sii(rg,cg);
    sii(ru,cu);
    rb--,cb--;
    rg--,cg--;
    rc--,cc--;
    ru--,cu--;
    mcmf::addEdge(source,get(rb,cb),1,0);
    mcmf::addEdge(source,get(rg,cg),1,0);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i==ru && j==cu)continue;
            if(i==rc && j==cc){
                mcmf::addEdge(get(i,j)+offset,sink,2,0);
                mcmf::addEdge(get(i,j),get(i,j)+offset,2,0);
            }
            else mcmf::addEdge(get(i,j),get(i,j)+offset,1,0);

            for(int k=0; k<4; k++){

                int newi=i+dx[k];
                int newj=j+dy[k];
                if(newi==ru && newj==cu)continue;
                int val = get(newi,newj);
                if(val>=0)
                    mcmf::addEdge(get(i,j)+offset, val, 1,1);
            }
        }
    }

    if(mcmf::MincostMaxflow(source,sink).second<2)pf("NO\n");
    else{
        pf("YES\n");
        mcmf::print(get(rb,cb),get(rg,cg),get(rc,cc), offset);
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
        while(1)Solve(0);
    #endif

return 0;
}
