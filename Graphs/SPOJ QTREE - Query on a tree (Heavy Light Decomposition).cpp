#include<bits/stdc++.h>
///SPOJ QTREE
using namespace std;
typedef pair<int,int> pii;
const int N = 1e4+5;

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
        return max(x,y);
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
        ret = Merge(ret,tree_query(u+1,v));///Ignore the cost of LCA
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



struct edge{
    int u,v,c,id;
    edge(){}
    edge(int u, int v, int c, int id):u(u),v(v),c(c),id(id){}
};
int edgeToNode[N];
vector<edge>graph1[N];

void dfs1(int u, int p){
    for(edge e:graph1[u]){
        if(e.v!=p){
            cost[e.v]=e.c;
            edgeToNode[e.id]=e.v;
            dfs1(e.v,u);
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=0; i<=n+5; i++){
            graph[i].clear();
            graph1[i].clear();
            cost[i]=0;
        }

        for(int i=0,a,b,c; i<n-1; i++){
            scanf("%d%d%d",&a,&b,&c);
            graph1[a].push_back(edge(a,b,c,i+1));
            graph1[b].push_back(edge(b,a,c,i+1));
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        dfs1(1,1);
        HLD::init(n,1);
        char s[15];
        bool done=0;
        int x,y;

        while(!done){

            scanf("%s",&s);
            if(s[0]=='D')break;
            else if(s[0]=='Q'){
                scanf("%d%d",&x,&y);
                if(x==y)printf("0\n");
                else printf("%d\n",HLD::query(x,y));
            }
            else if(s[0]=='C'){
                scanf("%d%d",&x,&y);
                HLD::update(edgeToNode[x],y);
            }

        }
    }

return 0;
}
/**
100
17
1 2 4
1 8 2
8 12 1
8 9 2
9 10 4
10 11 200
12 17 7
12 13 10
13 15 19
15 16 14
13 14 20
2 3 5
3 6 7
6 7 2
3 4 6
4 5 3
*/
