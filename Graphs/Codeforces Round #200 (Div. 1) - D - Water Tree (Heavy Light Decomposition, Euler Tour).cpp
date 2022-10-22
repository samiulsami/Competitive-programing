#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl;
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
const int N = 5e5+5;

vector<int>graph[N];

namespace HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    int Tree[4*N];
    int Lazy[4*N];
    int dTime[N],eTime[N];

    int dfs(int u, int p);
    void hld(int u, int p, int chainParent);


    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
        for(int i=0; i<4*n; i++){
            Tree[i]=0;
            Lazy[i]=-1;
        }
    }

    void push_update(int node, int l, int r){
        if(Lazy[node]!=-1){
            Tree[node] = (r-l+1)*Lazy[node];
            if(l!=r){
                Lazy[node*2] = Lazy[node];
                Lazy[node*2+1] = Lazy[node];
            }
            Lazy[node]=-1;
        }
    }

    void update(int node, int l, int r, int posl, int posr, int val){
        push_update(node, l, r);
        if(l>r || r<posl || posr<l)return;
        if(l>=posl && r<=posr){
            Lazy[node]=val;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            update(node*2, l, mid, posl, posr, val);
            update(node*2+1, mid+1, r, posl, posr,val);
            Tree[node] = Tree[node*2] + Tree[node*2+1];
        }
    }

    void updateSubtree(int u){
        update(1,1,posCnt,dTime[u],eTime[u],1);
    }

    void updateParent(int u){
        while(chainRoot[1]!=chainRoot[u]){
            update(1,1,posCnt,posInChain[chainRoot[u]],posInChain[u],0);
            u=parent[chainRoot[u]];
        }
        update(1,1,posCnt,posInChain[1],posInChain[u],0);
    }

    int query(int node, int l, int r, int pos){
        push_update(node, l,r);
        if(l==pos && r==pos)return Tree[node];
        int mid = (l+r)>>1;
        if(pos<=mid)return query(node*2, l, mid, pos);
        return query(node*2+1, mid+1, r, pos);
    }

    int query1(int u){
        return query(1,1,posCnt,posInChain[u]);
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
        dTime[u]=++posCnt;
        posInChain[u]=posCnt;
        chainArr[posCnt]=u;

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
        eTime[u]=posCnt;
    }

}

void solve(int caseno){
    int n;
    si(n);
    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HLD::init(n,1);
    int q,c,v;
    si(q);
    while(q--){
        sii(c,v);
        if(c==1){
            HLD::updateSubtree(v);
        }
        else if(c==2){
            HLD::updateParent(v);
        }
        else{
            pf("%d\n",HLD::query1(v));
        }
    }
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
