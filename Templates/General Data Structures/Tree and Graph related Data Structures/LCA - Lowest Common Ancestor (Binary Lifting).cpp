#include<bits/stdc++.h>
using namespace std;
///SPOJ LCA - Lowest Common Ancestor

const int N=1005;
vector<int>graph[N];

struct LCA{
    ///LCA with Binary Lifting, O(nlogn) preprocessing, O(logn) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>lvl;
    vector<vector<int > >Table;
    int LOG,n;

    LCA(int n, int root=1):n(n),lvl(n+1),LOG(ceil(log2(n))+1){
        Table.assign(LOG, vector<int>(n+1,-1));
        dfs(root,-1);
        for(int i=1; i<LOG; i++)
            for(int j=1; j<=n; j++)
                if(Table[i-1][j]!=-1)
                    Table[i][j] = Table[i-1][Table[i-1][j]];
    }

    void dfs(int u, int p){
        Table[0][u]=p;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
            }
    }

    int lca(int u, int v){
        if(lvl[u]!=lvl[v]){
                if(lvl[u]>lvl[v])swap(u,v);
                for(int i=LOG-1; i>=0; i--)
                    if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u])
                        v=Table[i][v];
        }
        if(u==v)return u;
        for(int i=LOG-1; i>=0; i--){
            if(Table[i][u]!=Table[i][v]){
                u=Table[i][u];
                v=Table[i][v];
            }
        }
        return Table[0][u];
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
