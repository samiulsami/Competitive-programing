#include<bits/stdc++.h>
using namespace std;
#define xx first
#define yy second
typedef pair<int,int> pii;
struct ftc{
    int u,v,cst;
    ftc(){}
    ftc(int a,int b,int c){u=a;v=b;cst=c;}
};

int prims(vector<pii>graph[], int v){
    priority_queue<pii,vector<pii>,greater<pii> >pq;
    pq.push({0,1});
    bool vis[v+1]={0};
    int v_counter=0;
    int cost=0;
    while(!pq.empty()){
        int weight=pq.top().xx;
        int v = pq.top().yy;
        pq.pop();
        if(!vis[v]){
            v_counter++;
            vis[v]=1;
            cost+=weight;
        }
        else continue;
        for(int i=0; i<(int)graph[v].size(); i++){
            if(vis[graph[v][i].yy])continue;
            pq.push(graph[v][i]);
        }
    }
    if(v_counter<v)return -1;
    return cost;
}
class cmp{
public:
    bool operator()(ftc &a, ftc &b){return a.cst>b.cst;}
};
int main(){
    //freopen("output.txt","w",stdout);
    int t,v,e;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>v>>e;
        vector<pii>graph[v+1];
        ftc mst_edges[v];
        for(int i=0,u,c,v; i<e; i++){
            cin>>u>>v>>c;
            graph[u].push_back({c,v});
            graph[v].push_back({c,u});
        }
        cout<<"Case #"<<cas<<" : ";
        int lowest_cost=0,min_cost=-1;
        priority_queue<ftc,vector<ftc>,cmp>pq;
        pq.push(ftc(1,1,0));
        bool vis[v+1]={0};
        int v_counter=0;
        int edges_counter=0;
        while(!pq.empty()){
            int fr=pq.top().u;
            int to=pq.top().v;
            int weight=pq.top().cst;
            pq.pop();
            if(!vis[to]){
                v_counter++;
                vis[to]=1;
                lowest_cost+=weight;
                if(fr!=to)mst_edges[edges_counter++]=ftc(fr,to,weight);
            }
            else continue;
            for(int i=0; i<graph[to].size(); i++){
                if(vis[graph[to][i].yy])continue;
                pq.push(ftc(to,graph[to][i].yy,graph[to][i].xx));
            }
        }
        if(v_counter<v){
            cout<<"No way"<<endl;
            continue;
        }
        for(int i=0; i<v-1; i++){
            int tmp_cost;
            int u=mst_edges[i].u;
            int vv=mst_edges[i].v;
            int cst=mst_edges[i].cst;
            for(int j=0; j<(int)graph[u].size(); j++){
                if(graph[u][j].xx==cst && graph[u][j].yy==vv){
                    graph[u].erase(graph[u].begin()+j);
                    break;
                }
            }
            for(int j=0; j<(int)graph[vv].size(); j++){
                if(graph[vv][j].xx==cst && graph[vv][j].yy==u){
                    graph[vv].erase(graph[vv].begin()+j);
                    break;
                }
            }
            tmp_cost=prims(graph,v);
            graph[u].push_back({cst,vv});
            graph[vv].push_back({cst,u});
            if(min_cost==-1)min_cost=tmp_cost;
            else if(tmp_cost!=-1)min_cost=min(min_cost,tmp_cost);
        }
        if(min_cost==-1)cout<<"No second way"<<endl;
        else cout<<min_cost<<endl;
    }
return 0;
}
