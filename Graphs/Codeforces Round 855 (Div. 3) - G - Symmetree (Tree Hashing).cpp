#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint32_t ui;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());

const int N = 2e5+5;

vector<int>graph[N];
bool symmetric[N];
unordered_map<ui, ui>mp;
ui _hash[N];

ui dfs(int u, int p){
	symmetric[u]=0;

	vector<ui>hashes;
	ui ret=0;
	for(int v:graph[u])
		if(v^p){
			hashes.push_back(dfs(v,u));
			ret += hashes.back();
		}

	sort(all(hashes));
	if(!mp.count(ret))mp[ret] = rng();
	_hash[u] = mp[ret];

	ui oddHash=-1;
	for(int i=0; i<sz(hashes); i++){
		int j = i;
		while(j+1<sz(hashes) && hashes[j+1]==hashes[j])j++;
		if((j-i+1)&1){
			if(oddHash==-1)oddHash = hashes[i];
			else return _hash[u];
		}
		i=j;
	}

	if(oddHash==-1){
		symmetric[u]=1;
		return _hash[u];
	}

	for(int v:graph[u]){
		if(v^p && _hash[v]==oddHash){
			symmetric[u] = symmetric[v];
			break;
		}
	}

	return _hash[u];
}


inline void solve(int caseNum){
	int n;
	cin>>n;
	for(int i=0; i<n-1; i++){
		int u,v;
		cin>>u>>v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	dfs(1,1);
	if(symmetric[1])cout<<"YES\n";
	else cout<<"NO\n";

	for(int i=0; i<=n; i++)graph[i].clear();
	mp.clear();
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