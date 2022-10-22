#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;


vector<pii>graph[N];
int Table[19][N];
int Table1[19][N]={0};
int lvl[N]={0};

int dfs(int u, int p){
	int ret=0;
	for(pii v:graph[u]){
		if(v.second!=p){
			Table[0][v.second]=u;
			Table1[0][v.second]=v.first;
			lvl[v.second]=lvl[u]+1;
			ret+=dfs(v.second,u)+v.first;
		}
	}
	return ret;
}



void solve(int casenum){
	memset(Table,-1,sizeof(Table));
	int n;
	si(n);
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(pii(0,v));
		graph[v].push_back(pii(1,u));
	}
	
	int cost = dfs(1,1);
	vector<pii>ans;

	for(int i=1; i<19; i++){
		for(int j=1; j<=n; j++){
			if(Table[i-1][j]!=-1){
				Table[i][j] = Table[i-1][Table[i-1][j]];
				Table1[i][j] = Table1[i-1][j] + Table1[i-1][Table[i-1][j]];
			}
		}
	}
	
	for(int i=1,cur,k,add; i<=n; i++){
		//dbug(cost[i]);
		cur=0,k=i;
		for(int j=18; j>=0; j--){
			if(Table[j][k]!=-1){
				cur+=Table1[j][k];
				k=Table[j][k];
			}
		}
		add = (lvl[i]-cur);
		//cout<<cost[1]+add-cur<<endl;
		ans.push_back(pii(cost+add-cur,i));
	}
	sort(all(ans));
	pf("%d\n",ans[0].first);
	for(pii &p:ans){
		if(p.first==ans[0].first)pf("%d ",p.second);
		else break;
	}
	nl;
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}