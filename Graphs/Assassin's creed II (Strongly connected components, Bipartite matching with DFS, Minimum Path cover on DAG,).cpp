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
bool inPath[MAX],vis[2*MAX];
vector<int>graph[MAX],dag[MAX];
stack<int>curPath,reachable;
int scc=0;
int parent[MAX];
vector<int>bpGraph[2*MAX];
int matchR[2*MAX];

void resetALL(int n){

    for(int i=0; i<=n+1; i++){
        graph[i].clear();
        dag[i].clear();
        dTime[i]=0;
        parent[i]=-1;
        inPath[i]=vis[i]=0;
    }
    for(int i=0; i<=2*n; i++){
        bpGraph[i].clear();
        matchR[i]=-1;
    }

    Time=0;
    scc=0;
}


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


bool match(int lft){
    if(vis[lft])return 0;
    vis[lft]=1;

    for(int r:bpGraph[lft]){
        if(matchR[r]==-1 && !vis[r]){
            matchR[r]=lft;
            return 1;
        }
    }

    for(int r:bpGraph[lft]){
        if(match(matchR[r])){
            matchR[r]=lft;
            return 1;
        }
    }

    return 0;
}

int bpm(){
    int ans=0;
    for(int i=0; i<scc; i++){
         memset(vis,0,sizeof(vis));
         if(match(i))ans++;
    }
    return ans;
}

void dfs(int u,int belong){
    vis[u]=1;
    for(int v:dag[u]){
        if(!vis[v]){
            dfs(v,belong);
            bpGraph[belong].push_back(v+scc+1);
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


    for(int i=1; i<=n; i++){
        for(int v:graph[i]){
            if(parent[v]!=parent[i]){
                dag[parent[i]].push_back(parent[v]);
            }
        }
    }

    int offset=scc;

    for(int u=0; u<scc; u++){
        memset(vis,0,sizeof(vis));
        dfs(u,u);
    }

    int ans = scc-bpm();

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
