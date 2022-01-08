#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
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
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

int color[N];
int colorCnt[N]={0};
int cntSum[N]={0};
ll colorSum[N]={0};

struct dsuOnTree{
	vector<int>graph[N];
	int dTime[N],eTime[N],euler[N];
	int maxSubtree[N];
	ll ans[N];
	int Time=0;
	int maxfreq=0;

	void init(int root){
		dfs1(root,root);
		dfs(root,root,0);
	}
	
	void addEdge(int u, int v){
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	int dfs1(int u, int p){
		dTime[u]=++Time;
		euler[Time]=u;
		int ret=1,mxSubtree=-1,curmx=-1,tmp;
		for(int &v:graph[u])
			if(v^p){
				tmp=dfs1(v,u);
				ret+=tmp;
				if(tmp>curmx){
					mxSubtree=v;
					curmx=tmp;
				}
			}
		maxSubtree[u]=mxSubtree;
		eTime[u]=Time;
		return ret;
	}

	void dfs(int u, int p, bool keep){
		int heavyChild = maxSubtree[u];
		for(int &v:graph[u])
			if(v^p && v^heavyChild)dfs(v,u,0);
		if(heavyChild!=-1)dfs(heavyChild,u,1);
		for(int &v:graph[u])
			if(v^p && v^heavyChild)
				for(int x=dTime[v]; x<=eTime[v]; x++)add(euler[x]);
		add(u);
		calc(u);
		if(!keep)for(int x=dTime[u]; x<=eTime[u]; x++)
				remove(euler[x]);
	}
	
	inline void add(int u){
		colorSum[colorCnt[color[u]]]-=color[u];
		cntSum[colorCnt[color[u]]]--;
		colorCnt[color[u]]++;
		cntSum[colorCnt[color[u]]]++;
		colorSum[colorCnt[color[u]]]+=color[u];
		if(cntSum[maxfreq+1])maxfreq++;
	}
	
	inline void remove(int u){
		colorSum[colorCnt[color[u]]]-=color[u];
		cntSum[colorCnt[color[u]]]--;
		colorCnt[color[u]]--;
		cntSum[colorCnt[color[u]]]++;
		colorSum[colorCnt[color[u]]]+=color[u];
		if(cntSum[maxfreq]==0)maxfreq--;
	}
	
	inline int calc(int u){
		ans[u]=colorSum[maxfreq];
	}
	
}dot;


void solve(int casenum){
	int n;
	si(n);
	for(int i=1; i<=n; i++)si(color[i]);
	
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		dot.addEdge(u,v);
	}
	dot.init(1);
	for(int i=1; i<=n; i++)pf("%lld ",dot.ans[i]);
	nl;
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