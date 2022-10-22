#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;

vector<int>graph[N];
int a[N],l[N],r[N];
ll dp[2][N];
int vis[2][N]={0};
int color=1;

ll dfs(int u, int p, bool flag){
	ll &ret = dp[flag][u];
	if(vis[flag][u]==color)return ret;
	vis[flag][u]=color;
	ret=0;
	
	if(!flag){
		for(int v:graph[u]){
			if(v^p){
				ret += min(dfs(v,u,0) + (ll)abs(a[u]-a[v]), dfs(v,u,1));
			}
		}
	}
	else{
		vector<ll>tmp;
		for(int v:graph[u]){
			tmp.push_back(a[v]);
			if(v^p){
				ret += dfs(v,u,0);
			}
		}
		
		ll ans=1e18;
		ll low=l[u],high=r[u],mid1,mid2;
		
		auto f = [&](ll xd)->ll{
			ll fret=0;
			for(ll x:tmp)fret+= ll(abs(x-xd));
			return fret;
		};
		while(high-low>2){
			mid1 = low+(high-low)/3;
			mid2 = high-(high-low)/3;
			ll a = f(mid1);
			ll b = f(mid2);
			ans = min({ans,a,b});
			if(a<b)high=mid2;
			else low=mid1;
		}
		
		for(;low<=high;low++)ans = min(ans,f(low));
		ret += ans;
	}
	return ret;
}

inline void solve(int caseNum){
	int n;
	cin>>n;
	color++;
	for(int i=1; i<=n; i++){
		cin>>l[i]>>a[i]>>r[i];
	}
	
	for(int i=1,u,v; i<n; i++){
		cin>>u>>v;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	cout<<min(dfs(1,-1,0),dfs(1,-1,1))<<"\n";
	
	for(int i=0; i<=n;i++)graph[i].clear();
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