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

const int N = 1e5+5;
const int MOD = 1e9+7;

int dTime[N]={0},curTree[N]={0},cost[N],Time=0;
int scc=0;
stack<int>curPath;
vi graph[N];
ll total=0;
ll ways=1;

int tarjan(int u){
	int low=dTime[u]=++Time;
	curTree[u]=1;
	curPath.push(u);
	for(int v:graph[u]){
		if(!dTime[v])low=min(low,tarjan(v));
		else if(curTree[v])low=min(low,dTime[v]);
	}
	
	if(low==dTime[u]){
		int top;
		vector<int>tmp;
		do{
			top=curPath.top();
			curPath.pop();
			tmp.push_back(cost[top]);
			curTree[top]=0;
		}while(top!=u);
		
		sort(all(tmp));
		tmp.erase(upper_bound(all(tmp),tmp[0]),tmp.end());
		total+=tmp[0];
		ways = (ways*ll(tmp.size()))%MOD;
	}
	return low;
}


void solve(int casenum){
	int n,m;
	si(n);
	for(int i=1; i<=n; i++)si(cost[i]);
	si(m);
	for(int i=0,u,v; i<m; i++){
		sii(u,v);
		graph[u].push_back(v);
	}
	for(int i=1; i<=n; i++)if(!dTime[i])tarjan(i);
	
	pf("%lld %lld\n",total,ways);
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}