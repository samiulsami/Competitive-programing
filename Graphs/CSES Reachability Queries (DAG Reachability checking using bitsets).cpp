#include<bits/stdc++.h>
using namespace std;

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

const int N = 5e4+5;

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
	
}scc;
bitset<N>bs[N];

vector<int>toposort;

bool vis[N]={0};
void dfs(int u){
	vis[u]=1;
	for(int v:scc.dag[u]){
		if(!vis[v])dfs(v);
	}
	toposort.push_back(u);
}

void solve(int casenum){
	int n,m,q;
	siii(n,m,q);
	scc.reset(n);
	
	for(int i=0,u,v; i<m; i++){
		sii(u,v);
		scc.addEdge(u,v);
	}
	scc.run();
	scc.makedag();
	
	for(int i=1; i<=n; i++){
		if(!vis[scc.parent[i]])dfs(scc.parent[i]);
	}
	
	for(int &u:toposort){
		bs[u][u]=1;
		for(int &v:scc.dag[u])bs[u]|=bs[v]; 
	}
	
	for(int i=0,u,v; i<q; i++){
		sii(u,v);
		u=scc.parent[u];
		v=scc.parent[v];
		if(bs[u][v])pf("YES\n");
		else pf("NO\n");
	}
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}