#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1308 - Ant Network
    verdict: AC
*/

typedef unsigned long long ull;

int discovery_time[10005];
vector<int>graph[10005];
bool vis[10005];
int visColor[10005];
int color;
bool cutVertex[10005];
int Time=0;
int NodesInComponent=0;
unsigned long long ans=0;
const ull MOD = ULLONG_MAX;

int dfs(int src, int parent){
    int low=discovery_time[src]=++Time;
    int children=0;

    for(int v:graph[src]){
        if(v==parent)continue;
        if(discovery_time[v])
            low=min(low,discovery_time[v]);
        else{
            children++;
            int subtree_min=dfs(v,src);
            low=min(low,subtree_min);
            if(discovery_time[src]<=subtree_min)
                cutVertex[src]=1;
        }
    }

    if(src==parent)cutVertex[src]=children>1;
    return low;
}

int dfs2(int src){
    NodesInComponent++;
    vis[src]=1;
    int ret=0;

    for(int v:graph[src]){
        if(cutVertex[v] && visColor[v]!=color){
            visColor[v]=color;
            ret++;
            continue;
        }
        if(vis[v] || cutVertex[v])continue;
        vis[v]=1;
        ret+=dfs2(v);
    }

    return ret;
}

ull modMul(ull a, ull b){

    ull mul=b;
    ull ret=0;

    while(mul>0){

        if(mul%2ULL){
            if(ret+a<=ret)ret = ret-1ULL-MOD;//since MOD = ULLMAX =(2^64)-1
            ret+=a;
        }

        if(MOD-a>=a-1ULL)a = a-(MOD-a+1ULL);
        else a*=2ULL;

        mul/=2ULL;
    }

    return ret%MOD;
}

ull gcd(ull a, ull b){
    if(b==0ULL)return a;
    return gcd(b,a%b);
}

ull nCr(ull n, ull r){
    ull p=1,k=1,m;
    if(n-r<r)r=n-r;

    if(r!=0){
        while(r){
            p=modMul(p,n);
            k=modMul(k,r);
            m=gcd(p,k);
            p/=m;
            k/=m;
            n--;
            r--;
        }
    }
    else p=1;

    return p;
}

int main(){
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t,n,m;
    scanf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);
        for(int i=0; i<=n; i++){
            discovery_time[i]=0;
            vis[i]=cutVertex[i]=0;
            graph[i].clear();
            visColor[i]=0;
        }
        color=0;
        Time=0;

        for(int i=0,u,v; i<m; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        dfs(0,0);

        ans=1;
        int components=0;
        for(int i=0; i<n; i++){
            if(!vis[i] && !cutVertex[i]){
                NodesInComponent=0;
                vis[i]=1;
                color++;
                if(dfs2(i)<2){
                   components++;
                   ans=modMul(ans,(ull)NodesInComponent);
                }
            }
        }

        if(components==1){
            components++;
            ans=nCr(ans,2ULL);
        }

        printf("Case %d: %d %llu\n",cas,components,ans);
    }
return 0;
}
