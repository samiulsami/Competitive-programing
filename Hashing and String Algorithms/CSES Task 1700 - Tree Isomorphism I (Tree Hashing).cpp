#include<bits/stdc++.h>
using namespace std;
 
typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
 
const int N = 1e5+5;
 
vector<int>graph[N];
map<vector<int>, int> mp;
 
int dfs(int u, int p){
	vector<int>hashes;
	for(int v:graph[u])
		if(v^p)hashes.push_back(dfs(v,u));
 
	sort(hashes.begin(), hashes.end());
	if(!mp.count(hashes))mp[hashes]=mp.size();
	return mp[hashes];
}
 
inline void solve(int caseNum){
	int n;
	cin>>n;
	for(int i=1,u,v; i<n; i++){
		cin>>u>>v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}	
 	
	int A = dfs(1,1);
 	for(int i=0; i<=n; i++)graph[i].clear();
 		
	for(int i=1,u,v; i<n; i++){
		cin>>u>>v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
 	
 
	int B = dfs(1,1);
	mp.clear();
	for(int i=0; i<=n; i++)graph[i].clear();

	if(A==B)cout<<"YES\n";
	else cout<<"NO\n";
 
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