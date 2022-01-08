#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;

vector<int>graph[N];

namespace CD{
    int parent[N],subtreeSize[N];
    bool vis[N];///Marks centroids
    int n,curSize;

    int dfs(int u, int p);
    int find_centroid(int u, int p);
    void centroid_decomposition(int u, int p);

    void init(int x, int root=1){///Call first
        n=x;
        for(int i=0; i<=n; i++)vis[i]=0;
        centroid_decomposition(root,-1);
    }

    int dfs(int u, int p){
        subtreeSize[u]=1;
        for(int v:graph[u])
            if(!vis[v] && v!=p)subtreeSize[u]+=dfs(v,u);
        return subtreeSize[u];
    }

    int find_centroid(int u, int p){
        for(int v:graph[u])
            if(!vis[v] && v!=p)
                if(subtreeSize[v]>curSize/2)return find_centroid(v,u);
        return u;
    }

    void centroid_decomposition(int u, int p){
        curSize=dfs(u,u);
        int centroid = find_centroid(u,u);
        vis[centroid]=1;
        parent[centroid]=p;
        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v,centroid);
    }
}

struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>discoveryTime,lvl,lgVal;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(int n, int root=1):n(n),discoveryTime(n+1),lvl(n+1),lgVal(1+n<<1){
        lvl[root]=0;
        Time=0;
        for(int i=2,lim=n+n; i<=lim; i++)lgVal[i]=lgVal[(i>>1)]+1;
        LOG = lgVal[n]+2;
        sparseTable.resize(LOG, vector<int>(1+n<<1));
        dfs(root,-1);

        for(int i=1; i<LOG; i++){
            for(int j=1; j+(1<<i)-1<=Time; j++){
                int left=sparseTable[i-1][j];
                int right=sparseTable[i-1][j+(1<<(i-1))];
                if(lvl[left]<lvl[right])sparseTable[i][j] = left;
                else sparseTable[i][j] = right;
            }
        }
    }

    void dfs(int u, int p){
        discoveryTime[u]=++Time;
        sparseTable[0][Time]=u;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
    }

    inline int lca(int u, int v){
        u=discoveryTime[u];
        v=discoveryTime[v];
        if(u>v)swap(u,v);
        int logVal = lgVal[v-u+1];
        int x=sparseTable[logVal][u];
        int y=sparseTable[logVal][v-(1<<logVal)+1];
        if(lvl[x]<lvl[y])return x;
        return y;
    }
};

int dist[N];

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,u,v; i<n; i++){
        scanf("%d%d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i=1; i<=n; i++)dist[i]=1e9;
    CD::init(n,1);
    //for(int i=1; i<=n; i++)printf("%d -> %d\n",i,CD::parent[i]);
    LCA L(n,1);

    auto pathDist = [&](int u, int v){return L.lvl[u] + L.lvl[v] - 2*L.lvl[L.lca(u,v)];};

    int tmp=1;
    while(tmp!=-1){
            dist[tmp] = min(dist[tmp], pathDist(1,tmp));
            tmp=CD::parent[tmp];
                //printf("here\n");
    }

    while(m--){
        int x,u;
        scanf("%d%d",&x,&u);
        if(x==1){
            int v=u;
            while(v!=-1){
                dist[v] = min(dist[v], pathDist(u,v));
                v=CD::parent[v];
                //printf("here\n");
            }
        }
        else{
            int ans=1e9;
            int v=u;
            while(v!=-1){
                //printf("%d -> %d: %d\n",u,v,pathDist(u,v));
                ans = min(ans, dist[v] + pathDist(u,v));
                //printf("%d -> %d\n",v,CD::parent[v]);
                v=CD::parent[v];
            }
            printf("%d\n",ans);
        }
    }
return 0;
}
