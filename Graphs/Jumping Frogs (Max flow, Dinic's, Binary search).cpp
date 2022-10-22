#include<bits/stdc++.h>
/*
    Problem: LightOJ 1156 - Jumping Frogs
    Verdict: AC
*/
using namespace std;
typedef long long ll;

#define xx first
#define yy second
#define si(x) scanf("%d",&x)
#define sl(x) scanf("%d",&x)
#define FOR(n) for(int i=0; i<n; i++)
#define FORR(startVal,n) for(int i=startVal; i<n; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl


namespace Dinic{

        struct edge{
            int u,v;
            int cap, flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
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

        void addEdge(int u, int v, int cap, bool bidirectional = false){
            edges.emplace_back(u,v,cap);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,(bidirectional?cap:0));
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

        #define Multiple_Test_Cases
int arr[105];
bool typ[105];
void init(int rn){
    for(int i=0; i<=rn; i++){
        arr[i]=0;
        typ[i]=0;
    }
}

inline void Solve(int Case){
    int n,D;
    scanf("%d%d",&n,&D);
    init(n);

    char type,c;
    int val;
    arr[0]=0;
    typ[0]=1;
    for(int i=1; i<=n; i++){
        scanf(" %c%c%d",&type,&c,&val);
        if(type=='S')typ[i]=0;
        else typ[i]=1;
        arr[i]=val;
    }
    arr[n+1]=D;
    typ[n+1]=1;
    int source=0;
    int sink=2*n+4;

    int low=0,mid,high=D;
    int ans=D;

    while(low<=high){
        mid=(low+high)/2;

        Dinic::init(2*n+10,source,sink);
        if(D<=mid)Dinic::addEdge(source,sink,2);
        for(int i=0; i<=n; i++){
            Dinic::addEdge(i,i+n+1,(typ[i]?2:1));
            for(int j=i+1; j<=n; j++){
                if(arr[j]-arr[i]<=mid){
                        Dinic::addEdge(i+n+1,j,2);
                        //cout<<arr[i]<<" - "<<arr[j]<<endl;
                }
                else break;
            }
            if(D-arr[i]<=mid)Dinic::addEdge(i+n+1,sink,(typ[i]?2:1));
        }
        if(Dinic::maxFlow(source,sink)>=2){
            ans=min(ans,mid);
            high=mid-1;
        }
        else low=mid+1;
    }

    printf("Case %d: %d\n",Case,ans);

}

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
