#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

vector<int>graph[N];
int arr[N];

set<int> dp[N][2];
int ans[N];

void dfs(int u, int p, bool used, int G){
	if(dp[u][used].count(G))return;
	dp[u][used].insert(G);
	ans[u] = max(ans[u], __gcd(arr[u],G));
	if(!used)ans[u] = max(ans[u],G);
	int newG = __gcd(G,arr[u]);

	for(int v:graph[u]){
		if(v==p)continue;
		dfs(v,u,used,newG);
		if(!used)dfs(v,u,1,G);
	}
}

inline void solve(int caseNum){
	int n;
	cin>>n;
	for(int i=1; i<=n; i++)cin>>arr[i];
	for(int i=1,a,b; i<n; i++){
		cin>>a>>b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	dfs(1,1,0,0);
	ans[1]=arr[1];
	for(int i=1; i<=n; i++)cout<<ans[i]<<" ";
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