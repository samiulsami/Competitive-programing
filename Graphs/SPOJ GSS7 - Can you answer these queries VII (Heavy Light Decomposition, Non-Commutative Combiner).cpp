#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5+5;
vector<int>graph[N];
ll cost[N];
const ll INF = 1e14;

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int Table[20][N];
    int n,posCnt,LOG;
    struct data{
        ll pref,suff,total,best;
        data(){}
        data(ll pref, ll suff, ll total, ll best):total(total),pref(pref),suff(suff),best(best){}
    }Tree[N<<2];
    ll Lazy[N<<2];

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);

    inline data Merge(data a, data b){
        if(a.pref==-INF)return b;
        if(b.pref==-INF)return a;
        data ret;
        ret.total = a.total+b.total;
        ret.pref = max(a.pref, a.total+b.pref);
        ret.suff = max(b.suff, b.total+a.suff);
        ret.best = max({a.best, b.best, a.suff+b.pref});

        return ret;
    }

    void build(int node, int l, int r){
        Lazy[node]=INF;
        if(l==r){
            ll x=cost[chainArr[l]];
            Tree[node] = data(x,x,x,max(0LL,x));
        }
        else{
            int mid = (l+r)>>1;
            build(node*2, l, mid);
            build(node*2+1, mid+1, r);
            Tree[node] = Merge(Tree[node*2], Tree[node*2+1]);
        }
    }

    inline void push_update(int node, int l, int r){
        if(Lazy[node]!=INF){
            ll x = 1LL*(r-l+1)*Lazy[node];
            ll val = Lazy[node];
            if(val<0)Tree[node] = data(val,val,x,0);
            else Tree[node] = data(x,x,x,x);
            if(l!=r){
                Lazy[node*2] = Lazy[node];
                Lazy[node*2+1] = Lazy[node];
            }
            Lazy[node]=INF;
        }
    }

    void update(int node, int l, int r, int posl, int posr, ll val){
        push_update(node, l, r);
        if(l>r || r<posl || l>posr)return;
        if(l>=posl && r<=posr){
            Lazy[node]=val;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            update(node*2, l, mid, posl, posr, val);
            update(node*2+1, mid+1, r, posl, posr, val);
            Tree[node] = Merge(Tree[node*2], Tree[node*2+1]);
        }
    }

    data query(int node, int l, int r, int posl, int posr){
        push_update(node, l, r);
        if(l>r || r<posl || l>posr)return data(-INF,-INF,-INF,0);
        if(l>=posl && r<=posr)return Tree[node];
        int mid = (l+r)>>1;
        return Merge(query(node*2, l,mid, posl, posr), query(node*2+1, mid+1, r, posl, posr));
    }

    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        build(1,1,posCnt);
        LOG = ceil(log2(n))+1;
        Table[0][root]=-1;
        for(int i=1; i<LOG; i++){
            for(int j=1; j<=n; j++){
                if(Table[i-1][j]!=-1)Table[i][j] = Table[i-1][Table[i-1][j]];
                else Table[i][j]=-1;
            }
        }
    }

    int lca(int u, int v){
        if(lvl[u]!=lvl[v]){
            if(lvl[v]<lvl[u])swap(u,v);
            for(int i=LOG-1; i>=0; i--){
                if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u]){
                    v=Table[i][v];
                }
            }
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

    ll Pathquery(int u, int v){///Query the path from node u to v
        data ret(-INF,-INF,-INF,0),ret2(-INF,-INF,-INF,0);

        /// u to L
        int L = lca(u,v);
        while(1){
            if(chainRoot[u]==chainRoot[L]){
                ret=Merge(query(1,1,posCnt,posInChain[L],posInChain[u]),ret);
                break;
            }
            ret=Merge(query(1,1,posCnt,posInChain[chainRoot[u]],posInChain[u]),ret);
            u=parent[chainRoot[u]];
        }

        ///v to L+1
        while(1){
            if(chainRoot[v]==chainRoot[L]){
                ret2=Merge(query(1,1,posCnt,posInChain[L]+1,posInChain[v]),ret2);
                break;
            }
            ret2=Merge(query(1,1,posCnt,posInChain[chainRoot[v]],posInChain[v]),ret2);
            v=parent[chainRoot[v]];
        }

        ll ans = max({ret.best,ret2.best, ret.pref+ret2.pref, ret.total+ret2.pref, ret2.total+ret.pref});
        return ans;

    }

    void pathUpdate(int u, int v, ll val){
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            update(1,1,posCnt,posInChain[chainRoot[u]],posInChain[u],val);
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        update(1,1,posCnt,u,v,val);
    }

    int dfs(int u, int p){
        parent[u]=p;
        int ret=1, mx=0,nxt=-1,subtreeSize;
        for(int v:graph[u]){
            if(v==p)continue;
            lvl[v]=lvl[u]+1;
            Table[0][v]=u;
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
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)scanf("%lld",&cost[i]);
    for(int i=1,u,v; i<n; i++){
        scanf("%d%d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HLD::init(n,1);
    int q;
    scanf("%d",&q);

    int qt,u,v;
    ll val;
    while(q--){
        scanf("%d",&qt);
        if(qt==1){
            scanf("%d%d",&u,&v);
            printf("%lld\n",HLD::Pathquery(u,v));
        }
        else{
            scanf("%d%d%lld",&u,&v,&val);
            HLD::pathUpdate(u,v,val);
        }
    }

return 0;
}
