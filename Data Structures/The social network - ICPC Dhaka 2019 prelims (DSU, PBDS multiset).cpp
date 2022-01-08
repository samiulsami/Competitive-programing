#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define xx first
#define yy second

typedef tree<
    pair<int,int>,
    null_type,
    less<pair<int,int> >,
    rb_tree_tag,
    tree_order_statistics_node_update> Multiset;

int parent[100005];

int Find(int u){
    if(parent[u]==u)return u;
    return parent[u]=Find(parent[u]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt,n,q,cnt=0,ans;
    scanf("%d",&tt);
    for(int cas=1; cas<=tt; cas++){
        scanf("%d%d",&n,&q);
        Multiset ms[n+1];
        for(int i=0; i<=n; i++)parent[i]=i;
        int x,u,v,l,r,t;
        printf("Case %d:\n",cas);
        while(q--){
            scanf("%d",&x);
            if(x==0){
                scanf("%d%d",&u,&v);
                u=Find(u);
                v=Find(v);
                if(u==v)continue;
                if(ms[u].size()<ms[v].size())swap(u,v);
                for(Multiset::iterator it=ms[v].begin(); it!=ms[v].end(); it++)
                    ms[u].insert(*it);
                parent[v]=u;
            }
            else if(x==1){
                scanf("%d%d",&u,&t);
                u=Find(u);
                ms[u].insert({t,++cnt});
            }
            else {
                scanf("%d%d%d",&u,&l,&r);
                u=Find(u);
                ans=ms[u].order_of_key({r+1,0})-ms[u].order_of_key({l,0});
                printf("%d\n",ans);
            }
        }
    }
return 0;
}
