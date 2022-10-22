#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;

vector<int>g[N];
int Table[20][N];
int lvl[N];

int dfs(int u, int p){
	Table[0][u]=p;
	for(int v:g[u]){
		if(v^p){
			lvl[v] = lvl[u]+1;
			dfs(v,u);
		}
	}
}

int lca(int u, int v){
	if(lvl[u]!=lvl[v]){
		if(lvl[u]<lvl[v])swap(u,v);
		for(int i=18; i>=0; i--){
			if(Table[i][u]!=-1 && lvl[Table[i][u]]>=lvl[v])
				u = Table[i][u];
		}
	}
	if(u==v)return u;
	for(int i=18; i>=0; i--){
		if(Table[i][u]!=Table[i][v]){
			u = Table[i][u];
			v = Table[i][v];
		}
	}
	return Table[0][u];
}

inline void solve(int caseNum){
	int n,q;
	cin>>n>>q;
	for(int i=2,x; i<=n; i++){
		cin>>x;
		g[x].push_back(i);
	}
	
	lvl[1]=0;
	dfs(1,-1);
	
	for(int i=1; i<=18; i++){
		for(int u=1; u<=n; u++){
			if(Table[i-1][u]!=-1)Table[i][u] = Table[i-1][Table[i-1][u]];
			else Table[i][u]=-1;
		}
	}
	
	while(q--){
		int a,b;
		cin>>a>>b;
		cout<<lca(a,b)<<"\n";
	}
}

int main(){
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}