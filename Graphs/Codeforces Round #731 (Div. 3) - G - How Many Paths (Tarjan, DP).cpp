#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 4e5+5;


vector<int>graph[N],rgraph[N];
int discovery_time[N],parent[N];
int Time=0,scc=0;
stack<int>curTree;
bool inTree[N]={0};
bool selfloop[N]={0};
bool cmploop[N]={0};
int cnt[N]={0};
pii dp[N];

void resetAll(int n){
	while(!curTree.empty())curTree.pop();
	for(int i=0; i<=n; i++){
		discovery_time[i]=0;
		selfloop[i]=0;
		parent[i]=0;
		cnt[i]=0;
		cmploop[i]=0;
		graph[i].clear();
		rgraph[i].clear();
		dp[i]={-1,0};
	}
	Time=0;
	scc=1;
}


int tarjan_scc(int u){
    int low=discovery_time[u]=++Time;
    curTree.push(u);
    inTree[u]=1;

    for(int v:graph[u])
        if(!discovery_time[v])
            low=min(low,tarjan_scc(v));
        else if(inTree[v])
            low=min(low,discovery_time[v]);

    if(low==discovery_time[u]){
        int top;
        do{
            top=curTree.top();
			cnt[scc]++;			
            curTree.pop();
            inTree[top]=0;
            parent[top]=scc;
        }while(u!=top && !curTree.empty());
	
        scc++;
    }
    return low;
}



int target;

pii f(int u){
	if(u==target)return pii(1,cmploop[u] || cnt[u]>1);
	pii &ret = dp[u];
	if(ret.first!=-1)return ret;
	ret=pii(0,cmploop[u] || cnt[u]>1);
	for(int v:rgraph[u]){
		pii x = f(v);
		ret.first+=x.first;
		if(x.first>0)ret.second|=x.second;
		if(ret.first>=2)ret.first=2;
	}
	return ret;
}


void solve(int casenum){
	int n,m;
	sii(n,m);
	if(casenum==1)resetAll(n);
	for(int i=0,u,v; i<m; i++){
		sii(u,v);
		if(u==v)selfloop[u]=1;
		else{
			graph[u].push_back(v);
		}
	}
	
	for(int i=1; i<=n; i++)if(!discovery_time[i])tarjan_scc(i);

	for(int i=1; i<=n; i++){
		if(selfloop[i])cmploop[parent[i]]=1;
		for(int v:graph[i]){
			if(parent[i]!=parent[v]){
				//dag[parent[i]].push_back(parent[v]);
				rgraph[parent[v]].push_back(parent[i]);
			}
		}
	}
	target=parent[1];
	
	for(int i=1; i<=n; i++){
		int x = parent[i];
		//pf("zzfsd %d %d %d %d %d\n",i,parent[i],cnt[x],cnt2[x],cnt3[x]);
		pii p = f(x);
		if(p.first==0)pf("0 ");
		else {
			if(p.second || cmploop[x])pf("-1 ");
			else if(p.first>1)pf("2 ");
			else pf("1 ");
		}
	}
	nl;
	resetAll(n);
}

int main(){
	
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}