#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

vector<int>graph[N];
int cost[N];

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    int Tree[N<<1];

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);
    void tree_update(int ind, int val);
    int tree_query(int l, int r);

    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        for(int i=0,lim=n<<1; i<lim; i++)Tree[i]=0;
        for(int i=1; i<=posCnt; i++)tree_update(i,chainArr[i]);
    }

    inline int Merge(int x, int y){///Segtree Combiner
        return x^y;
    }

    void update(int u, int val){///Update node u
        tree_update(posInChain[u],val);
    }

    int query(int u, int v){///Query the path from node u to v
        int ret=0;
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            ret = Merge(ret, tree_query(posInChain[chainRoot[u]], posInChain[u]));
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        ret = Merge(ret,tree_query(u,v));
        return ret;
    }

    int dfs(int u, int p){
        parent[u]=p;
        int ret=1, mx=0,nxt=-1,subtreeSize;
        for(int v:graph[u]){
            if(v==p)continue;
            lvl[v]=lvl[u]+1;
            subtreeSize=dfs(v,u);
            ret+=subtreeSize;
            if(subtreeSize>mx){
                mx=subtreeSize;
                nxt=v;
            }
        }
        maxSubtree[u]=nxt;
        return ret;
    }

    void hld(int u, int p, int chainParent){
        chainRoot[u]=chainParent;
        posInChain[u]=++posCnt;
        chainArr[posCnt]=cost[u];

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
    }

    void tree_update(int ind, int val){
        ind+=n-1;
        Tree[ind]=val;
        for(;ind>1; ind>>=1)Tree[ind>>1] = Merge(Tree[ind],Tree[ind^1]);
    }

    int tree_query(int l, int r){
        if(l>r)return 0;
        l+=n-1;
        r+=n;
        int ret=0;
        for(;l<r; l>>=1,r>>=1){
            if(l&1)ret=Merge(ret,Tree[l++]);
            if(r&1)ret=Merge(ret,Tree[--r]);
        }
        return ret;
    }
}

int main(){
    freopen("cowland.in","r",stdin);
    freopen("cowland.out","w",stdout);
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1; i<=n; i++)scanf("%d",&cost[i]);
    for(int i=1,u,v; i<n; i++){
        scanf("%d%d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    HLD::init(n,1);

    int x,i,j;
    while(q--){
        scanf("%d%d%d",&x,&i,&j);
        if(x==1)HLD::update(i,j);
        else printf("%d\n",HLD::query(i,j));
    }
return 0;
}
