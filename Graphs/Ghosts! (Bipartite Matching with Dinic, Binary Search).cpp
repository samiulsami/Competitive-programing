#include<bits/stdc++.h>
/*
    Problem: LightOJ 1150 - Ghosts!
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(n) for(int i=0; i<=n; i++)
#define FORR(l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace Dinic{

        struct edge{
            int u,v;
            int cap, flow, cost;
            edge(){}
            edge(int u, int v, int cap, int cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        const int MAX=1e4+5;

        vector<edge>edges;
        vector<int> graph[MAX];
        int lvl[MAX],nxt[MAX];
        int n,edge_cnt,S,T;

        void init(int nn, int SS=0, int TT=0){
            n=nn;
            S=SS;
            T=TT;
            edges.clear();
            for(int i=0; i<n; i++)graph[i].clear();
            edge_cnt=0;
        }

        void addEdge(int u, int v, int cap, int cost){
            edges.emplace_back(u,v,cap,cost);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0,cost);
            graph[v].push_back(edge_cnt++);
        }

        bool bfs(int lim){
            queue<int>q;
            q.push(S);
            for(int i=0; i<n; i++)lvl[i]=-1;
            lvl[S]=0;

            while(!q.empty()){
                int u=q.front();
                q.pop();

                for(int edgeID : graph[u]){
                    edge &v = edges[edgeID];
                    if(v.cap<=v.flow || lvl[v.v]!=-1 || v.cost>lim)continue;
                    lvl[v.v]=lvl[u]+1;
                    q.push(v.v);
                }
            }

            return lvl[T]!=-1;
        }

        int dfs(int u, int pathFlow, int lim){
            if(pathFlow==0 || u==T)return pathFlow;

            int ret=0;
            int id;

            for(int &edgeID=nxt[u]; edgeID<(int)graph[u].size(); edgeID++){

                id = graph[u][edgeID];
                edge &v = edges[id];
                if(lvl[v.v]!=lvl[u]+1 || v.cap<=v.flow || v.cost>lim)continue;

                if(ret=dfs(v.v, min(pathFlow, v.cap-v.flow), lim)){
                    edges[id].flow+=ret;
                    edges[id^1].flow-=ret;
                    return ret;
                }
            }

            return 0;
        }

        int maxFlow(int s=-1, int t=-1, int lim=999){
            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }
            if(S==T)return 0;

            int flow=0,f=0;

            while(bfs(lim)){
                for(int i=0; i<n; i++)nxt[i]=0;
                while(f=dfs(S,INT_MAX, lim))flow+=f;
            }
            return flow;
        }
}

char grid[30][30];
int human[30][30];
int ghost[30][30];
int dx[5] = {1,0,-1,0};
int dy[5] = {0,1,0,-1};
bool vis[30][30];
int lvl[30][30];


void find_humans(int gx, int gy, int n){
    queue<pii>q;
    for(int i=0; i<=n; i++)for(int j=0; j<=n; j++){
            vis[i][j]=0;
            lvl[i][j]=0;
    }

    q.push({gx,gy});

    while(!q.empty()){
        pii top=q.front();
        int x = top.xx;
        int y = top.yy;
        q.pop();
        vis[x][y]=1;
        if(grid[x][y]=='H'){
            int Time = lvl[x][y];
            Time*=2;
            Time+=2;
            Dinic::addEdge(ghost[gx][gy], human[x][y], 1, Time);
            //pf("Edge: (%d,%d) - (%d,%d), Time = %d\n",gx,gy,x,y, Time);
        }

        for(int i=0; i<4; i++){
            int newx = x+dx[i];
            int newy = y+dy[i];
            if(!(newx<n && newx>=0 && newy<n && newy>=0) || vis[newx][newy] || grid[newx][newy]=='#')continue;
            vis[newx][newy]=1;
            lvl[newx][newy] = lvl[x][y]+1;
            q.push({newx,newy});
        }
    }

}

inline void Solve(int Case){
    int n,source,sink;
    si(n);

    source=2*n*n+5;
    sink=source+1;
    memset(human,0,sizeof(human));
    memset(ghost,0,sizeof(ghost));
    int ghostCount=0;
    int humanCount=0;
    int offset=n*n;
    Dinic::init(2*n*n+10,source, sink);

    for(int i=0; i<n; i++)
        sf("%s",&grid[i]);

    vector<int>humans;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='H'){
                human[i][j]=offset+humanCount++;
                Dinic::addEdge(human[i][j],sink,1,0);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='G'){
                ghost[i][j]=ghostCount++;
                find_humans(i,j,n);
                Dinic::addEdge(source,ghost[i][j],1,0);
            }
        }
    }


    int low=0,mid,high=n*n*2;
    int ans=INT_MAX;
    while(low<=high){
        mid=(low+high)/2;
        for(int i=0; i<Dinic::edge_cnt; i++)Dinic::edges[i].flow=0;
        int flow = Dinic::maxFlow(source,sink,mid);
        //pf("flow: %d\n",flow);
        if(flow==humanCount){
            ans=min(mid,ans);
            high=mid-1;
        }
        else low=mid+1;
    }
    pf("Case %d: ",Case);
    if(ans==INT_MAX)pf("Vuter Dol Kupokat\n");
    else pf("%d\n",ans);

}

  #define Multiple_Test_Cases
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
