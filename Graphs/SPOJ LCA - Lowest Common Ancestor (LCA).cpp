#include<bits/stdc++.h>
using namespace std;
///SPOJ LCA - Lowest Common Ancestor

const int N=1005;
vector<int>graph[N];

struct LCA{
    ///LCA with Sparse Table, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>euler,discoveryTime,lvl,lgVal;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(int n, int root=1):n(n),euler(n+n+1),discoveryTime(n+1),lvl(n+1),lgVal(n+n+1){
        lvl[root]=0;
        Time=0;
        dfs(root,-1);
        for(int i=2; i<=Time; i++)lgVal[i]=lgVal[(i>>1)]+1;
        LOG = ceil(log2(n))+1;
        sparseTable.resize(LOG, vector<int>(Time+1));

        for(int i=1; i<=Time; i++)sparseTable[0][i]=euler[i];
        for(int i=1; i<=LOG; i++){
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
        euler[Time]=u;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                euler[++Time]=u;
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

int main(){
    int t;
    scanf("%d",&t);
    for(int Cas=1; Cas<=t; Cas++){
        int n,m;
        scanf("%d",&n);
        for(int i=0; i<=n; i++)graph[i].clear();
        for(int i=1; i<=n; i++){
            scanf("%d",&m);
            for(int j=0,v; j<m; j++){
                scanf("%d",&v);
                graph[i].push_back(v);
                graph[v].push_back(i);
            }
        }
        LCA L(n,1);

        int q,x,y;
        scanf("%d",&q);;
        printf("Case %d:\n",Cas);
        while(q--){
            scanf("%d%d",&x,&y);
            printf("%d\n",L.lca(x,y));
        }
    }

return 0;
}
