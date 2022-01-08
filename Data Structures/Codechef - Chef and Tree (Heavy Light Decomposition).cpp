#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5+5;

vector<int>graph[N];
ll cost[N];
ll A,B;

const ll INF = 1e16;

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    pair<ll,int>TreeMax[N<<2]; ///maxval, maxval index
    ll Lazy[N<<2];
    int TreeCnt[N<<2];

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);

    inline pair<ll,int> Merge(pair<ll,int> a, pair<ll,int>b){
        if(a.first>b.first)return a;
        return b;
    }

    void build(int node, int l, int r){
        Lazy[node]=0;
        if(l==r){
            ll val = (cost[chainArr[l]]*A) + B;
            if(val>=0){
                TreeCnt[node]=1;
                TreeMax[node].first=-INF;
                TreeMax[node].second=l;
            }
            else {
                TreeCnt[node]=0;
                TreeMax[node].first=val;
                TreeMax[node].second=l;
            }
        }
        else{
            int mid = (l+r)>>1;
            build(node*2, l, mid);
            build(node*2+1, mid+1, r);
            TreeCnt[node] = TreeCnt[node*2] + TreeCnt[node*2+1];
            TreeMax[node] = Merge(TreeMax[node*2], TreeMax[node*2+1]);
        }
    }

    inline void push_update(int node, int l, int r){
        if(Lazy[node]!=0){
            TreeMax[node].first += Lazy[node];
            if(l!=r){
                Lazy[node*2] += Lazy[node];
                Lazy[node*2+1] += Lazy[node];
            }
            Lazy[node]=0;
        }
    }

    void update2(int node, int l, int r, int posl, int posr, ll val){
        push_update(node,l,r);
        if(l>r || r<posl || l>posr)return;
        if(l>=posl && r<=posr){
            Lazy[node]+=val;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            update2(node*2, l, mid, posl, posr, val);
            update2(node*2+1, mid+1, r, posl, posr,val);
            TreeMax[node] = Merge(TreeMax[node*2], TreeMax[node*2+1]);
        }
    }

    pair<ll,int> query2(int node, int l, int r, int posl, int posr){
        push_update(node,l,r);
        if(l>r || r<posl || l>posr)return {-INF,0};
        if(l>=posl && r<=posr)return TreeMax[node];
        int mid = (l+r)>>1;
        return Merge(query2(node*2, l, mid, posl, posr), query2(node*2+1, mid+1, r, posl, posr));
    }

    void update1(int node, int l, int r, int pos, int val){
        if(l>r || r<pos || l>pos)return;
        if(l==pos && r==pos)TreeCnt[node]=val;
        else{
            int mid = (l+r)>>1;
            if(pos<=mid)update1(node*2, l, mid, pos, val);
            else update1(node*2+1, mid+1, r, pos, val);
            TreeCnt[node] = TreeCnt[node*2] + TreeCnt[node*2+1];
        }
    }

    int query1(int node, int l, int r, int posl, int posr){
        if(l>r || r<posl || l>posr)return 0;
        if(l>=posl && r<=posr)return TreeCnt[node];
        int mid = (l+r)>>1;
        return query1(node*2, l, mid, posl, posr) + query1(node*2+1, mid+1, r, posl, posr);
    }

    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        build(1,1,posCnt);
    }

    int query(int u, int v){///Query the path from node u to v
        int ret=0;
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            ret+=query1(1,1,posCnt, posInChain[chainRoot[u]], posInChain[u]);
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        ret += query1(1,1,posCnt,u,v);
        return ret;
    }

    void updatePath(int u, int v, ll val){///Add val to all nodes from u to v
        while(chainRoot[u]!=chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            update2(1,1, posCnt, posInChain[chainRoot[u]], posInChain[u], A*val);
            auto tmp = query2(1,1,posCnt, posInChain[chainRoot[u]], posInChain[u]);

            while(tmp.first>=0){
                update1(1,1,posCnt,tmp.second,1);
                update2(1,1,posCnt,tmp.second,tmp.second,-INF);
                tmp=query2(1,1,posCnt,posInChain[chainRoot[u]], posInChain[u]);
            }
            u = parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        update2(1,1,posCnt,u,v,A*val);
        auto tmp = query2(1,1,posCnt, u, v);
        while(tmp.first>=0){
            update1(1,1,posCnt,tmp.second,1);
            update2(1,1,posCnt,tmp.second,tmp.second,-INF);
            tmp=query2(1,1,posCnt,u,v);
            //printf("update: %lld %d %d %d\n",tmp.first, tmp.second, u, v);
        }

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
    int t;
    scanf("%d",&t);
    while(t--){

        int n,q;
        scanf("%d%d%lld%lld",&n,&q,&A,&B);
        for(int i=1; i<=n; i++)
            scanf("%lld",&cost[i]);
        for(int i=1,u,v; i<n; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        HLD::init(n,1);
        int qt,x,y,z;

        while(q--){
            scanf("%d",&qt);
            if(qt==1){
                scanf("%d%d%d",&x,&y,&z);
                HLD::updatePath(x,y,(ll)z);
            }
            else{
                scanf("%d%d",&x,&y);
                printf("%d\n",HLD::query(x,y));
            }
        }

        for(int i=0; i<=n+2; i++)graph[i].clear();
    }

return 0;
}
