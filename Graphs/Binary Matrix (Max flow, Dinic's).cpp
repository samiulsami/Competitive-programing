#include<bits/stdc++.h>
/*
    Problem: LightOJ 1330 - Binary Matrix
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
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
#define FOR(i,n) for(int i=0; i<=n; i++)
#define FORR(i,l,r) for(int i=l; i<=r; i++)
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define eikhane cerr<<"Eikhane"<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e5+5;

struct edge{
    int u,v,cap,flow;
    edge(){}
    edge(int u, int v, int cap):u(u),v(v),cap(cap){
        flow=0;
    }
};

struct Dinic{

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

int n,m;
int rowsum[52],colsum[52];
int source,sink;
vector<int> cellEdgeIndex,rowEdgeIndex,colEdgeIndex;

inline void Solve(int Case){
    sii(n,m);
    int r=0;
    int c=0;
    FOR(i,n-1){
        si(rowsum[i]);
        r+=rowsum[i];
    }
    FOR(i,m-1){
        si(colsum[i]);
        c+=colsum[i];
    }

    if(r!=c){
        pf("Case %d: impossible\n",Case);
        return;
    }
    Dinic dinic(n+m+3);
    cellEdgeIndex.clear();
    rowEdgeIndex.clear();
    colEdgeIndex.clear();
    source = n+m+1;
    sink = source+1;

    ///rowsum[0,n-1], colsum[n,m-1]

    FOR(i,n-1){
        rowEdgeIndex.push_back(dinic.edge_cnt);
        dinic.addEdge(source,i,rowsum[i]);
    }
    FOR(i,m-1){
        colEdgeIndex.push_back(dinic.edge_cnt);
        dinic.addEdge(i+n,sink,colsum[i]);
    }

    FOR(i,n-1){
        FOR(j,m-1){
            cellEdgeIndex.push_back(dinic.edge_cnt);
            dinic.addEdge(i,j+n,1);
        }
    }

    if(dinic.maxFlow(source,sink)!=r){
        pf("Case %d: impossible\n",Case);
        return;
    }

    pf("Case %d:\n",Case);
    int cnt=0;
    FOR(i,n-1)
        FOR(j,m-1){
            int ind = cellEdgeIndex[cnt++];
            int val = dinic.edges[ind].flow;
            dinic.edges[ind].cap=0;
            if(val){
                dinic.edges[rowEdgeIndex[i]].cap++;
                dinic.edges[colEdgeIndex[j]].cap++;
                if(dinic.maxFlow(source,sink)>0)val=0;
                else {
                    //dinic.edges[ind].cap=1;
                    dinic.edges[rowEdgeIndex[i]].cap--;
                    dinic.edges[colEdgeIndex[j]].cap--;
                }
            }

            pf("%d",val);
            if(j==m-1)nl;
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
