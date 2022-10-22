#include<bits/stdc++.h>
/*
    Problem: Codeforces round 284 C (div. 1)
    verdict: AC
*/

using namespace std;
typedef long long ll;

#define xx first
#define yy second
#define sf scanf
#define pf printf
#define dbug(x) cout<<"dbug: "<<x<<endl

struct node{
    int factor,power,key;
    node();
    node(int factor, int power, int key):factor(factor),power(power),key(key){}
};

const int MAX=7005;
int n,offset=3500,cnt=0,source,sink;
int arr[105];
bool vis[MAX];
vector<int>graph[MAX];
vector<node>factors[105];
//int matchR[MAX];

void factorize(int u){
    int uVal=arr[u];
    int sqt=sqrt(uVal)+5;
    for(int i=2; i*i<=sqt; i++){
        if(uVal%i==0){
            int pwr=0;
            while(uVal%i==0){
                uVal/=i;
                pwr++;
            }
            factors[u].emplace_back(i,pwr,cnt++);
        }
    }

    if(uVal>1)factors[u].emplace_back(node(uVal,1,cnt++));
}

namespace Dinic{

        struct edge{
            int u,v;
            int cap, flow;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };

        vector<edge>edges;
        vector<int> graph[MAX];
        int lvl[MAX],nxt[MAX];
        int n,edge_cnt,S,T;

        void init(int nn, int SS, int TT){
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
            memset(lvl,-1,n*sizeof(int));
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
            if(S==T)return 0;

            if(s!=-1 && t!=-1){
                S=s;
                T=t;
            }

            int flow=0,f=0;

            while(bfs()){
                memset(nxt, 0, n*sizeof(int));
                while(f=dfs(S,INT_MAX))flow+=f;
            }

            return flow;
        }
}

void addEdge(int u, int v){
    for(auto uf:factors[u]){
        for(auto vf:factors[v]){
            if(uf.factor==vf.factor){
                    if(!vis[uf.key])Dinic::addEdge(source,uf.key,uf.power);
                    if(!vis[vf.key])Dinic::addEdge(vf.key,sink,vf.power);
                    vis[uf.key]=1;
                    vis[vf.key]=1;
                    Dinic::addEdge(uf.key,vf.key,min(uf.power,vf.power));
            }
            else if(vf.factor>uf.factor)break;
        }
    }
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int m;
    cin>>n>>m;
    for(int i=0; i<n; i++){
            cin>>arr[i];
            factorize(i);
    }

    source=cnt++;
    sink=cnt++;
    Dinic::init(MAX,source,sink);

    for(int i=0,u,v; i<m; i++){
        cin>>u>>v;
        if(u&1)swap(u,v);
        u--,v--;
        addEdge(u,v);
    }

    cout<<Dinic::maxFlow(source,sink);

return 0;
}
