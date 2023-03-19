#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;
const int K = 300;

vector<int>graph[N];
int arr[N];
ll val[N];
int lvl[N];
int dTime[N+N],eTime[N+N];
int euler[N+N];
int Time=0;

struct LCA{
	///Credits:
	///lrvideckis
	///https://codeforces.com/blog/entry/74847 
	
	int jump[N],parent[N];
	int root=-1;
	
	void init(int r=1){
		root=r;
		jump[root]=root;
		parent[root]=root;
		val[1] = 1LL*arr[1]*arr[1];
		lvl[0]=0;
		dfs(1,0);
	}
	
	void dfs(int u, int p){
		int par2 = jump[p];
		lvl[u] = lvl[p] + 1;
		jump[u] = (lvl[p] - lvl[par2] == lvl[par2] - lvl[jump[par2]]) ? jump[par2] : p;
		parent[u] = p;
		dTime[u] = ++Time;
		euler[Time]=u;
		for(int &v:graph[u])
			if(v^p){
				val[v] = val[u] + 1LL*arr[v]*arr[v];
				dfs(v,u);
			}
		eTime[u] = ++Time;
		euler[Time]=u;
	}
	
	int kthParent(int u, int k){
		while(k>0 && u!=root){
			if(lvl[u] - k <= lvl[jump[u]]){
				k -= lvl[u] - lvl[jump[u]];
				u = jump[u];
			}
			else{
				k--;
				u = parent[u];
			}
		}
		return u;
	}
	
	int lca(int u, int v){
		if(lvl[u]<lvl[v])swap(u,v);
		u = kthParent(u, lvl[u] - lvl[v]);
		if(u==v)return v;
		
		while(u!=v){
			if(jump[u] == jump[v]){
				u = parent[u];
				v = parent[v];
			}
			else{
				u = jump[u];
				v = jump[v];
			}
		}
		
		return u;		
	}
	
	inline int dist(int u, int v){
		return lvl[u] + lvl[v] - 2*lvl[lca(u,v)];
	}
}lca;

struct query{
	int i,l,r,x;
	bool operator<(const query &q)const{
		if(x^q.x)return x<q.x;
		return (x&1)?r<q.r:r>q.r;
	}
}queries[N];

ll ans[N];
int L=1,R=0;
int vis[N]={0};
ll curans = 0;
int counter[N]={0};
int track[N][2]={0};

inline void Add(int u){
	int x = lvl[u];
	if(++counter[x] == 2){
		curans += 1LL*arr[u]*arr[track[x][0]];
		track[x][1] = u;
	}
	else  track[x][0] = u;
}

inline void Rem(int u){
	int x = lvl[u];
	if(--counter[x] == 1){
		if(track[x][0]==u)swap(track[x][0],track[x][1]);
		curans -= 1LL*arr[u]*arr[track[x][0]];
	}
}

inline void hehe(int x){
	x = euler[x];
	if(!vis[x])Add(x);
	else Rem(x);
	vis[x]^=1;
}

inline void solve(int caseNum){
	int n,q;
	cin>>n>>q;
	for(int i=1; i<=n; i++)cin>>arr[i];

	for(int i=2,p; i<=n; i++){
		cin>>p;
		graph[p].push_back(i);
	}

	lca.init(1);

	for(int i=0,u,v; i<q; i++){
		cin>>u>>v;
		ans[i] = val[lca.lca(u,v)];
		if(dTime[u]>dTime[v])swap(u,v);
		if(u==v){
			queries[i] = {-1,-1,-1,-1};
			continue;
		}
		u = eTime[u];
		v = dTime[v];
		queries[i] = {i,u,v,u/K};
	}

	sort(queries,queries+q);

	for(int i=0; i<q; i++){
		if(queries[i].i==-1)continue;
		while(R<queries[i].r)hehe(++R);
		while(L>queries[i].l)hehe(--L);
		while(R>queries[i].r)hehe(R--);
		while(L<queries[i].l)hehe(L++);
		ans[queries[i].i] += curans;
	}

	for(int i=0; i<q; i++)
		cout<<ans[i]<<"\n";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}