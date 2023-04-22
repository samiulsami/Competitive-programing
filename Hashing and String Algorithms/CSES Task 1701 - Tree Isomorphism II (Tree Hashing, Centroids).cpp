#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

inline void solve(int caseNum){
	int n;
	cin>>n;

	vector<vector<int> >g1(n);
	for(int i=0,u,v; i<n-1; i++){
		cin>>u>>v;
		u--,v--;
		g1[u].push_back(v);
		g1[v].push_back(u);
	}

	vector<vector<int> >g2(n);
	for(int i=0,u,v; i<n-1; i++){
		cin>>u>>v;
		u--,v--;
		g2[u].push_back(v);
		g2[v].push_back(u);
	}

	auto centroids = [&](const vector<vector<int> > &graph)->vector<int>{
		int x = int(graph.size());
		vector<int>_sz(x,0);
		vector<int>ret;

		auto dfs = [&](int u, int p, auto &self)->void{
			_sz[u]=1;
			bool centroid = 1;
			for(int v:graph[u]){
				if(v==p)continue;
				self(v,u,self);
				_sz[u] += _sz[v];
				if(_sz[v]>x/2)centroid = 0;
			}
			if((x-_sz[u]) > n/2)centroid=0;
			if(centroid)ret.push_back(u);
		};

		dfs(0,0,dfs);
		return ret;
	};

	map<vector<int>, int>mp;
	auto getHash = [&](int root, const vector<vector<int> >&graph)->int{
		auto dfs = [&](int u, int p, auto &self)->int{
			vector<int>hashes;
			for(int v:graph[u])
				if(v^p)hashes.push_back(self(v,u,self));
			sort(hashes.begin(), hashes.end());
			if(!mp.count(hashes))mp[hashes] = int(mp.size());
			return mp[hashes];
		};
		return dfs(root,root,dfs);
	};

	for(int a:centroids(g1))
		for(int b:centroids(g2))
			if(getHash(a,g1) == getHash(b,g2)){
				cout<<"YES\n";
				return;
			}

	cout<<"NO\n";
	return;
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}