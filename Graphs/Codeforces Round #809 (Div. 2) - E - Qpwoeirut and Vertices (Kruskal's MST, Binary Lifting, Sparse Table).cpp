#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;
const int K = 17;
vector<array<int,2> >mst[N];
int Table[K][N];
int TableMX[K][N];
int TableANS[K][N];
int parent[N];
int lvl[N];

int Find(int u){
	if(parent[u]==u)return u;
	return parent[u] = Find(parent[u]);
}

void dfs(int u, int p){
	Table[0][u]=p;
	for(auto &e:mst[u]){
		int v = e[1];
		if(v!=p){
			lvl[v] = lvl[u]+1;
			TableMX[0][v] = e[0];
			dfs(v,u);
		}
	}
}


inline void solve(int caseNum){
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=0; i<=n; i++)parent[i]=i;
	for(int i=1,u,v; i<=m; i++){
		cin>>u>>v;
		if(Find(u)!=Find(v)){
			parent[Find(u)] = Find(v);
			mst[u].push_back({i,v});
			mst[v].push_back({i,u});
		}
	}
	
	TableMX[0][1]=-1;
	lvl[1]=0;
	dfs(1,-1);
	
	for(int k=1; k<K; k++){
		for(int i=1; i<=n; i++){
			if(Table[k-1][i]==-1)Table[k][i]=-1;
			else {
				Table[k][i] = Table[k-1][Table[k-1][i]];
				TableMX[k][i] = max(TableMX[k-1][i], TableMX[k-1][Table[k-1][i]]);
			}
		}
	}
	
	
	for(int i=1; i<n; i++){
		int a=i,b=i+1;
		int mx=-1;
		
		if(lvl[a]!=lvl[b]){
			if(lvl[a]<lvl[b])swap(a,b);
			for(int k=K-1,x; k>=0; k--){
				x  = Table[k][a];
				if(x!=-1 && lvl[x]>=lvl[b]){
					mx = max(mx,TableMX[k][a]);
					a = x;
				}
			}
		}
		
		if(a!=b){
			for(int k=K-1; k>=0; k--){
				if(Table[k][a]!=Table[k][b]){
					mx = max(mx,TableMX[k][a]);
					a = Table[k][a];
					mx = max(mx,TableMX[k][b]);
					b = Table[k][b];
				}
			}
			mx = max({mx, TableMX[0][a], TableMX[0][b]});
		}
		
		TableANS[0][i] = mx;
	}
	
	for(int k=1; k<K; k++)
		for(int i=1; i+(1<<k)-1<=n; i++)
			TableANS[k][i] = max(TableANS[k-1][i], TableANS[k-1][i+(1<<(k-1))]);
	
	int l,r;
	while(q--){
		cin>>l>>r;
		if(l==r)cout<<"0\n";
		else{
			r--;
			int lg = __lg(r-l+1);
			cout<<max(TableANS[lg][l], TableANS[lg][r-(1<<lg)+1])<<"\n";
		}
	}
	//dbug("end\n");
	for(int i=1; i<=n; i++)mst[i].clear();
}

int main(){
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}