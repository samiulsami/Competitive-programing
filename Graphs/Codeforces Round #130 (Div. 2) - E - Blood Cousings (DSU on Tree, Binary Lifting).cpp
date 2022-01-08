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
const int K = __lg(N)+2;
int Table[K][N];
int lvl[N]={0};

vector<pii>queries[N];


struct dsuOnTree{
	vector<int>graph[N];
	int dTime[N],eTime[N],euler[N];
	int maxSubtree[N];
	int ans[N];
	int cnt[N]={0};
	int Time=0;

	void addEdge(int u, int v){
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	int dfs1(int u, int p){
		Table[0][u]=p;
		dTime[u]=++Time;
		euler[Time]=u;
		int ret=1,mxSubtree=-1,curmx=-1,tmp;
		for(int &v:graph[u])
			if(v^p){
				lvl[v]=lvl[u]+1;
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
		cnt[lvl[u]]++;
	}
	
	inline void remove(int u){
		cnt[lvl[u]]--;
	}
	
	inline int calc(int u){
		for(auto &q:queries[u]){
			ans[q.first] = max(0,cnt[q.second]-1);
		}
	}
	
	int kth(int u, int x){
		for(int i=K-1,j; i>=0; i--){
			j=(1<<i);
			if(j<=x && Table[i][u]!=-1){
				x-=j;
				u=Table[i][u];
			}
		}
		if(x>0 || u==0)return -1;
		return u;
	}
	
}dot;

void solve(int casenum){
	int n;
	si(n);
	for(int i=1,u; i<=n; i++){
		si(u);
		dot.addEdge(u,i);
	}
	lvl[0]=0;
	dot.dfs1(0,-1);
	for(int k=1; k<K; k++){
		for(int i=0; i<=n; i++){
			if(Table[k-1][i]!=-1){
				Table[k][i]=Table[k-1][Table[k-1][i]];
			}
		}
	}
	
	int m,a,b;
	si(m);
	for(int i=0; i<m; i++){
		sii(a,b);
		int kth = dot.kth(a,b);
		if(kth==-1){
			dot.ans[i]=0;
			continue;
		}
		queries[kth].emplace_back(i,lvl[a]);
	}
	dot.dfs(0,0,0);
	for(int i=0; i<m; i++)pf("%d ",dot.ans[i]);
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