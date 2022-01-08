#include<bits/stdc++.h>
/*
    Problem: LightOJ 1262 - Diagonal Sum
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
#define sl(x) scanf("%d",&x)
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

const double PI = 2*acos(0.0);

namespace Dinic{

        struct edge{
            int u,v;
            int cap, flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        const int MAX=400;

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

        void addEdge(int u, int v, int cap){
            edges.emplace_back(u,v,cap);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0);
            graph[v].push_back(edge_cnt++);
        }

        bool bfs(){
            queue<int>q;
            q.push(S);
            for(int i=0; i<n; i++)lvl[i]=-1;
            lvl[S]=0;

            while(!q.empty()){
                int u=q.front();
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

        int maxFlow(int s=-1, int t=-1){
            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }
            if(S==T)return 0;

            int flow=0,f=0;

            while(bfs()){
                for(int i=0; i<n; i++)nxt[i]=0;
                while(f=dfs(S,INT_MAX))flow+=f;
            }
            return flow;
        }
}

int L[102],R[102];
int gridL[55][55],gridR[55][55];
int cntL[102],cntR[102];
int ans[55][55];


inline void Solve(int Case){
    memset(cntL,0,sizeof(cntL));
    memset(cntR,0,sizeof(cntR));
    int n,m;
    sii(n,m);
    for(int i=0; i<n+m-1; i++)si(L[i]);
    for(int i=0; i<n+m-1; i++)si(R[i]);

    ///Each cell in gridL represents the Left diagonal it belongs to
    int lftDiagonal=0;
    for(int i=0; i<n; i++){
        for(int j=0,k=i; j<m && k>=0; j++,k--){
            gridL[k][j]=lftDiagonal;
            cntL[lftDiagonal]++;
        }
        lftDiagonal++;
    }

    for(int j=1; j<m; j++){
        for(int i=n-1, k=j; i>=0 && k<m; i--,k++){
            gridL[i][k]=lftDiagonal;
            cntL[lftDiagonal]++;
        }
        lftDiagonal++;
    }


    int rgtDiagonal=lftDiagonal;

    ///Each cell in gridR represents the Right diagonal it belongs to
    for(int i=0; i<n; i++){
        for(int j=m-1,k=i; j>=0 && k>=0; j--,k--){
            gridR[k][j]=rgtDiagonal;
            cntR[rgtDiagonal-lftDiagonal]++;
        }
        rgtDiagonal++;
    }

    for(int j=m-2; j>=0; j--){
        for(int i=n-1, k=j; i>=0 && k>=0; i--,k--){
            gridR[i][k]=rgtDiagonal;
            cntR[rgtDiagonal-lftDiagonal]++;
        }
        rgtDiagonal++;
    }

    int source = rgtDiagonal+2;
    int sink = source+1;

    Dinic::init(rgtDiagonal+10,source,sink);
    vector<int>relevantEdges;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            Dinic::addEdge(gridL[i][j], gridR[i][j], 99);
            relevantEdges.pb(Dinic::edge_cnt-2);
        }
    }

    for(int i=0; i<lftDiagonal; i++)
            Dinic::addEdge(source, i, L[i] - cntL[i]);

    for(int i=lftDiagonal; i<rgtDiagonal; i++)
        Dinic::addEdge(i, sink, R[i-lftDiagonal] - cntR[i-lftDiagonal]);

    Dinic::maxFlow(source,sink);
    int ind=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int flow = Dinic::edges[relevantEdges[ind++]].flow + 1;
            ans[i][j] = flow;
        }
    }

    printf("Case %d:\n",Case);
    for(int i=0; i<n; i++){
        printf("%d",ans[i][0]);
        for(int j=1; j<m; j++)pf(" %d",ans[i][j]);
        nl;
    }

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
