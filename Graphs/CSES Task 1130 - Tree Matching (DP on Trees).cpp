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
int dp[N][2];

int dfs(int u, int p, int stat){
	int &ret = dp[u][stat];
	if(~ret)return ret;
	ret=0;
	
	
	int total=0;
	for(int v:g[u]){
		if(v^p)total += dfs(v,u,0);
	}
	
	ret = total;
	if(stat)return ret;
	
	for(int v:g[u]){
		if(v^p){
			int cur = total - dfs(v,u,0) + 1 + dfs(v,u,1);
			ret = max(ret, cur);
		}
	}
	
	return ret;
}

inline void solve(int caseNum){
		int n;
		cin>>n;
		
		for(int i=1,a,b; i<n; i++){
			cin>>a>>b;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		
		cout<<dfs(1,1,0)<<"\n";
}

int main(){
	memset(dp,-1,sizeof(dp));
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}