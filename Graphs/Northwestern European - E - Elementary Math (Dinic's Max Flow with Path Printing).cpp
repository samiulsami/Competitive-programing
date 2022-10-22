#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pii;
const int N = 1e5+5;

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
                    if(v.cap<=v.flow | lvl[v.v]!=-1)continue;
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

map<ll, ll>mp,original;

pii arr[N];
int main(){
    int n;
    cin>>n;
    int source=n*30-5;
    int sink=source+1;
    Dinic dinic(n*30);
    vector<int>numedge;
    vector<array<int,3> >arredge(n+1);

    for(int i=1; i<=n; i++){
        cin>>arr[i].first>>arr[i].second;
        ll val1=arr[i].first-arr[i].second;
        ll val2=1LL*arr[i].first*arr[i].second;
        ll val3=arr[i].first+arr[i].second;
        if(!mp.count(val1))mp[val1] = 1+(int)mp.size();
        if(!mp.count(val2))mp[val2] = 1+(int)mp.size();
        if(!mp.count(val3))mp[val3] = 1+(int)mp.size();
        original[mp[val1]]=val1;
        original[mp[val2]]=val2;
        original[mp[val3]]=val3;
        dinic.addEdge(i,n+1+mp[val1],1);
        arredge[i][0]=dinic.edge_cnt-2;
        dinic.addEdge(i,n+1+mp[val2],1);
        arredge[i][1]=dinic.edge_cnt-2;
        dinic.addEdge(i,n+1+mp[val3],1);
        arredge[i][2]=dinic.edge_cnt-2;
        dinic.addEdge(source,i,1);
    }

    for(auto it:mp){
        dinic.addEdge(n+it.second+1,sink,1);
    }

    if(dinic.maxFlow(source,sink)<n){
        cout<<"impossible"<<endl;
        return 0;
    }

    char c[3] = {'-','*','+'};
    for(int i=1; i<=n; i++){
        int x;
        for(int j=0; j<3; j++){
            int id=arredge[i][j];
            if(dinic.edges[id].flow){
                x=j;
                break;
            }
        }
        ll cur;
        if(x==0)cur=arr[i].first-arr[i].second;
        else if(x==1)cur=arr[i].first*arr[i].second;
        else cur=arr[i].first+arr[i].second;

        cout<<arr[i].first<<" "<<c[x]<<" "<<arr[i].second<<" = "<<cur<<endl;
    }

return 0;
}