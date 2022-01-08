#include<bits/stdc++.h>

using namespace std;

/*
    problem: LightOJ 1429 - Assassin`s Creed (II)
    verdict: AC
*/

typedef long long ll;

const int MAX   = 1e3+5;


int dTime[MAX];
int Time=0;
bool inPath[MAX],vis[MAX];
vector<int>graph[MAX],dag[MAX];
stack<int>curPath,reachable;
int scc=0;
int parent[MAX];

void resetALL(int n){

    for(int i=0; i<=n+1; i++){
        graph[i].clear();
        dag[i].clear();
        dTime[i]=0;
        parent[i]=-1;
        inPath[i]=vis[i]=0;
    }

    Time=0;
    scc=0;
}

const int INF = 2000000000;


struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};



struct Dinic {

  int N;
  vector<vector<Edge> > G;
  vector<Edge *> dad;
  vector<int> Q;

  Dinic(int N) : N(N), G(N), dad(N), Q(N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].emplace_back(from, to, cap, 0, G[to].size());
    if (from == to) G[from].back().index++;
    G[to].emplace_back(to, from, 0, 0, G[from].size() - 1);
  }

  int BlockingFlow(int s, int t) {
    fill(dad.begin(), dad.end(), (Edge *) NULL);
    dad[s] = &G[0][0] - 1;

    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < G[x].size(); i++) {
        Edge &e = G[x][i];
        if (!dad[e.to] && e.cap - e.flow > 0) {
          dad[e.to] = &G[x][i];
          Q[tail++] = e.to;
        }
      }
    }
    if (!dad[t]) return 0;

    int totflow = 0;
    for (int i = 0; i < G[t].size(); i++) {
      Edge *start = &G[G[t][i].to][G[t][i].index];
      int amt = INF;
      for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
        if (!e) { amt = 0; break; }
        amt = min(amt, e->cap - e->flow);
      }
      if (amt == 0) continue;
      for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
        e->flow += amt;
        G[e->to][e->index].flow -= amt;
      }
      totflow += amt;
    }
    return totflow;
  }

  int GetMaxFlow(int s, int t) {
    int totflow = 0;
    while (int flow = BlockingFlow(s, t))
      totflow += flow;
    return totflow;
  }
};

int tarjan_scc(int u){

    int low=dTime[u]=++Time;
    inPath[u]=1;
    curPath.push(u);

    for(int v:graph[u]){
        if(!dTime[v])
            low=min(low,tarjan_scc(v));
        else if(inPath[v])
            low=min(low,dTime[v]);
    }

    if(low==dTime[u]){
        int top;

        do{
            top=curPath.top();
            curPath.pop();
            parent[top]=scc;
            inPath[top]=0;
        }while(top!=u && !curPath.empty());

        scc++;
    }

    return low;
}

void dfs(int u){
    vis[u]=1;
    for(int v:dag[u]){
        if(!vis[v]){
            dfs(v);
            reachable.push(v);
        }
    }
}

void solve(int cases){
    int n,m,u,v;

    scanf("%d%d",&n,&m);
    resetALL(n);

    for(int i=0; i<m; i++){
        scanf("%d%d",&u,&v);
        graph[u].push_back(v);
    }

    for(int i=1; i<=n; i++)
        if(!dTime[i])tarjan_scc(i);

    int source=scc++;
    int sink=scc++;

    Dinic dinic(4+(scc-2)*2);

    for(int i=1; i<=n; i++){
        for(int v:graph[i]){
            if(parent[v]!=parent[i]){
                dag[parent[i]].push_back(parent[v]);
            }
        }
    }

    int offset=scc+2;

    for(int u=0; u<scc-2; u++){
        dinic.AddEdge(source,u,1);
        dinic.AddEdge(u+offset,sink,1);

        memset(vis,0,sizeof(vis));
        dfs(u);
        while(!reachable.empty()){
            int v=reachable.top();
            reachable.pop();
            dinic.AddEdge(u,v+offset,1);
        }
    }
    int mxflow=dinic.GetMaxFlow(source,sink);
    int ans = scc-mxflow-2;

    printf("Case %d: %d\n",cases,ans);
}


int main(){

        //READ;
        //freopen("output.txt","w",stdout);

        int T;
        scanf("%d",&T);
        for (int cases = 1; cases <= T; cases++) {
            solve(cases);
        }

return 0;
}
