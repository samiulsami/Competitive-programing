#include<bits/stdc++.h>
using namespace std;

const int N = 5e4+5;
vector<int>graph[N];

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    int Tree[N<<2]={0};
    int Lazy[N<<2]={0};

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);

    inline void push_update(int node, int l, int r){
        if(Lazy[node]!=0){
            Tree[node]+=Lazy[node];
            if(l!=r){
                Lazy[node*2]+=Lazy[node];
                Lazy[node*2+1]+=Lazy[node];
            }
            Lazy[node]=0;
        }
    }

    void update(int node, int l, int r, int posl, int posr){
        push_update(node, l, r);
        if(l>r || r<posl || l>posr)return;
        if(l>=posl && r<=posr){
            Lazy[node]++;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            update(node*2, l, mid, posl, posr);
            update(node*2+1, mid+1, r, posl, posr);
            Tree[node] = max(Tree[node*2], Tree[node*2+1]);
        }
    }

    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
    }


    void addPath(int u, int v){
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            update(1,1,posCnt,posInChain[chainRoot[u]], posInChain[u]);
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        update(1,1,posCnt,u,v);
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
        chainArr[posCnt]=u;

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
    }

}

int main(){
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);

    for(int i=1,u,v; i<n; i++){
        scanf("%d%d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HLD::init(n,1);
    for(int i=0,u,v; i<m; i++){
        scanf("%d%d",&u,&v);
        HLD::addPath(u,v);
    }

    printf("%d\n",HLD::Tree[1]);

return 0;
}
