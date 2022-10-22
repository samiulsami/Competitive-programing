#include<bits/stdc++.h>
using namespace std;
///https://codeforces.com/gym/103463/problem/M
typedef int64_t ll;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define nl printf("\n");
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
#define si(x) scanf("%d",&x);
#define sii(x,y) scanf("%d%d",&x,&y);
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z);
#define sl(x) scanf("%lld",&x);
#define sll(x,y) scanf("%lld%lld",&x,&y);
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define FOR(i,j,n) for(int i=j; i<=n; i++)
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
 
const int N = 1e5+5;
 
const int MAGIC = 55005;
bitset<MAGIC>bs[MAGIC];

struct tarjanSCC{
	vector<int>graph[N],dag[N];
	int discovery_time[N],parent[N];
	int Time=0,scc=0,n;
	stack<int>curTree;
	bool inTree[N];
 
	void reset(int n){///CALL FIRST
		this->n=n;
		Time=0;
		scc=0;
		while(!curTree.empty())curTree.pop();
		for(int i=0; i<=n; i++){
			discovery_time[i]=0;
			parent[i]=0;
			graph[i].clear();
			inTree[i]=0;
			dag[i].clear();
		}
	}
 
	void addEdge(int u, int v){graph[u].push_back(v);}
	void run(){for(int i=1; i<=n; i++)if(!discovery_time[i])dfs(i);}
	
	void makedag(){
		for(int i=1; i<=n; i++){
			for(int v:graph[i]){
				if(parent[i]!=parent[v])
					dag[parent[i]].push_back(parent[v]);
			}
		}
	}
	int dfs(int u){
		int low=discovery_time[u]=++Time;
		curTree.push(u);
		inTree[u]=1;
 
		for(int v:graph[u]){
			if(!discovery_time[v])low=min(low,dfs(v));
			else if(inTree[v])low=min(low,discovery_time[v]);
		}
		
		if(low==discovery_time[u]){
			int top;
			scc++;
			do{
				top=curTree.top();
				curTree.pop();
				inTree[top]=0;
				parent[top]=scc;
			}while(u!=top);
		}
		return low;
	}
	
	bool idk(int u, int v){
		if(u==v)return 1;
		for(int x:dag[u])
			if(idk(x,v))return 1;
		return 0;
	}
	
}scc;


 
vector<int>toposort;
 
bool vis[N]={0};
void dfs(int u){
	vis[u]=1;
	for(int v:scc.dag[u]){
		if(!vis[v])dfs(v);
	}
	toposort.push_back(u);
}

namespace genspace{
	unsigned long long k1,k2;
	int n,m, _u[N], _v[N];


	unsigned long long xorShift128Plus(){
		unsigned long long k3 = k1, k4 = k2;
		k1 = k4;
		k3 ^= k3<<23;
		k2 = k3^k4^(k3>>17)^(k4>>26);
		return k2 + k4;
	}

	int wnext(int l, int r, int t){
		int ret = xorShift128Plus()%(r-l+1) + l;
		for(int i=1; i<t; i++){
			ret = max(ret, int(xorShift128Plus() % (r-l+1)+l));
		}
		return ret;
	}

	void gen(int _n, int _m, unsigned long long _k1, unsigned long long _k2){
		n = _n, m = _m;
		k1 = _k1, k2 = _k2;
		int S = min(1000,n);
		for(int i=1; i<=m; i++){
			_u[i] = wnext(1, min(n, ((i%S) + 1) * S), 50);
			_v[i] = wnext(1, min(n, ((i%S) + 1) * S), 50);
		}
	}
}
 
 
map<int,int>mp[N];

void solve(int casenum){
	unsigned long long n,m,q,k1,k2;
	cin>>n>>m>>q>>k1>>k2;
	scc.reset(n);
	genspace::n=n;
	genspace::m=m;
	genspace::k1=k1;
	genspace::k2=k2;
	genspace::gen(n,m,k1,k2);
	
	
	for(int i=1,u,v; i<=m; i++){
		u = genspace::_u[i];
		v = genspace::_v[i];
		if(u==v)continue;
		if(mp[u].count(v))continue;
		mp[u][v]=1;
		scc.addEdge(u,v);
	}
	scc.run();
	scc.makedag();
	
	vector<int>per(n);
	for(int i=1; i<=n; i++)per[i-1]=i;
	shuffle(all(per),rng);
	
	for(int i:per){
		if(!vis[scc.parent[i]])dfs(scc.parent[i]);
	}
	
	for(int u:toposort){
		if(u>=MAGIC)continue;
		bs[u][u]=1;
		for(int &v:scc.dag[u]){
			if(v<MAGIC)bs[u]|=bs[v]; 
		}
	}
	
	map<array<int,2>,int>records;
	
	for(int i=0,u,v; i<q; i++){
		cin>>u>>v;
		u=scc.parent[u];
		v=scc.parent[v];
		int possible=-1;
		
		array<int,2>tmp;
		tmp[0]=u;
		tmp[1]=v;
		
		if(records.count(tmp))possible=records[tmp];
		else{
			if(u<MAGIC && v<MAGIC){
				if(bs[u][v])possible=1;
			}
			else if(scc.idk(u,v))possible=1;
		}
		
		if(possible==1)cout<<"Yes\n";
		else cout<<"No\n";
		
		records[tmp]=possible;
		
		cout.flush();
	}
}
 
int main(){
   // ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}