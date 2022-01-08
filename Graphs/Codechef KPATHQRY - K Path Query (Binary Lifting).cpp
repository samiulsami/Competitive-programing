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

const int N = 1e5+5;

vector<int>graph[N];
int Table[20][N];
int arr[N],lvl[N];
int cnt[N]={0};

int lca(int u, int v){
	if(lvl[u]^lvl[v]){
		if(lvl[u]>lvl[v])swap(u,v);
		for(int i=19; i>=0; i--)if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u])v=Table[i][v];
	}
	if(u==v)return u;
	for(int i=19; i>=0; i--){
		if(Table[i][v]!=Table[i][u]){
			u=Table[i][u];
			v=Table[i][v];
		}
	}
	return Table[0][u];
}

void dfs(int u, int p){
	Table[0][u]=p;
	for(int v:graph[u]){
		if(v^p){
			lvl[v]=lvl[u]+1;
			dfs(v,u);
		}
	}
}



void solve(int casenum){
	int n;
	si(n);

	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	lvl[1]=0;
	dfs(1,-1);
	
	for(int i=1; i<20; i++){
		for(int j=1; j<=n; j++){
			if(Table[i-1][j]==-1)Table[i][j]=-1;
			else Table[i][j] = Table[i-1][Table[i-1][j]];
		}
	}
	
	int q,k;
	si(q);
	while(q--){
		si(k);
		if(k==1){
			si(arr[0]);
			pf("YES\n");
			continue;
		}
		int L=-1,x;
		for(int i=0; i<k; i++){
			si(arr[i]);
			if(L==-1)L=arr[i];
			else L=lca(L,arr[i]);
		}

		sort(arr,arr+k,[&](int &a, int &b)->bool{return lvl[a]>lvl[b];});
		
		auto calc = [&](){
			for(int j=0,tmp; j<k; j++){
				tmp=x;
				for(int i=19; arr[j]!=x && i>=0; i--){
					if(Table[i][x]!=-1 && lvl[Table[i][x]]>=lvl[arr[j]]){
						x=Table[i][x];
					}
				}
				if(x==arr[j])cnt[arr[j]]++;
				x=tmp;
			}
		};
		
		x=arr[0];
		calc();
		
		x=-1;
		for(int i=0; i<k; i++){
			if(!cnt[arr[i]]){
				x=arr[i];
				break;
			}
		}
		
		bool b=1;
		if(x!=-1){
			if(lca(x,arr[0])!=L)b=0;
			else calc();
		}
		
		for(int i=0; i<k; i++){
			if((arr[i]!=L && cnt[arr[i]]>=2) || cnt[arr[i]]==0)b=0;
			cnt[arr[i]]=0;
		}
		
		if(b)pf("YES\n");
		else pf("NO\n");
	}
	
	for(int i=0; i<=n; i++)graph[i].clear();
}
/*

1
12
1 11
1 2
2 7
2 3
3 5
3 4
3 6
5 10
5 8
4 9
6 12
100
4 10 5 3 4
*/
//5 1 2 3 8 10 11
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}