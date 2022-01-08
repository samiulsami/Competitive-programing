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
const int N = 2e5+5;

int dTime[N],eTime[N],euler[N],Time=0;
vector<int>graph[N];
ll ans[N];

void dfs(int u, int p){
    dTime[u]=++Time;
    euler[Time]=u;
    for(int v:graph[u]){
            if(v!=p)dfs(v,u);
    }
    eTime[u]=Time;
}

struct query{
    int i,l,r,x;
    query(){}
    query(int i, int l, int r, int x):i(i),l(l),r(r),x(x){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return (x&1)?r<q.r:r>q.r;
    }
}queries[N];
int color[N];
int colorCnt[N]={0};
int cntSum[N]={0};
ll colorSum[N]={0};
int cur=0;
ll curans=0;

inline void Add(int x){
    x=euler[x];
    colorSum[colorCnt[color[x]]]-=color[x];
    cntSum[colorCnt[color[x]]]--;
    colorCnt[color[x]]++;
    cntSum[colorCnt[color[x]]]++;
    colorSum[colorCnt[color[x]]]+=color[x];
    if(cntSum[cur+1]>0)cur++;
}

inline void Remove(int x){
    x=euler[x];
    colorSum[colorCnt[color[x]]]-=color[x];
    cntSum[colorCnt[color[x]]]--;
    colorCnt[color[x]]--;
    cntSum[colorCnt[color[x]]]++;
    colorSum[colorCnt[color[x]]]+=color[x];
    if(cntSum[cur]==0)cur--;
}

void solve(int caseno){
    int n;
    si(n);
    for(int i=1; i<=n; i++)si(color[i]);
    for(int i=1,u,v; i<n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,1);
    for(int i=1; i<=n; i++){
        queries[i] = query(i,dTime[i],eTime[i],dTime[i]/320);
    }
    sort(queries+1,queries+n+1);
    int l=1,r=0;
    for(int i=1; i<=n; i++){
        while(r<queries[i].r)Add(++r);
        while(l>queries[i].l)Add(--l);
        while(r>queries[i].r)Remove(r--);
        while(l<queries[i].l)Remove(l++);
        ans[queries[i].i]=colorSum[cur];
    }

    for(int i=1; i<=n; i++)pf("%lld ",ans[i]);

}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
