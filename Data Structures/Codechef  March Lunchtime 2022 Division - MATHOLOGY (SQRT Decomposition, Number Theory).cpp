#include<bits/stdc++.h>
using namespace std;
 #pragma GCC target ("avx2")
 #pragma GCC optimization ("O3")
 #pragma GCC optimization ("unroll-loops")
 #pragma GCC optimize("Ofast")
 #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
typedef int64_t ll;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define nl printf("\n");
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
#define si(x) scanf("%d",&x);
#define sii(x,y) scanf("%d%d",&x,&y);
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z);
#define sl(x) scanf("%lld",&x);
#define sll(x,y) scanf("%lld%lld",&x,&y);
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define FOR(i,j,n) for(int i=j; i<=n; i++)
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 100005;
const int K = 320;
int arr[N];
int divisors[N];
vector<pii>queries[N];
int ans[N];
int mn,mx;
int n;
int vis[N]={0};
int color=1;
int Block[K+5];
int P[N];

inline void update(int pos, int ind){
	if(vis[pos]!=color && vis[pos]!=(-color)){
		vis[pos]=color;
		P[pos]=ind;
	}
	else{
		Block[pos/K] = max(Block[pos/K], P[pos]);
		divisors[pos] = P[pos];
		P[pos]=ind;
		vis[pos]=-color;
	}
}

int Find(){
	int i=K;
	for(;i>=0;i--){
		if(Block[i]>=mn)break;
	}
	if(i==-1)return -1;
	i*=K;
	for(int x=i,lim=min(i+K-1,mx); x<=lim; x++){
		if(divisors[x]>=mn && vis[x]==-color)i=x;
	}
	
	return i;
}

void solve(int casenum){
	int q;
	sii(n,q);
	mx=0;
	FOR(i,0,n-1){
		si(arr[i]);
		mx=max(mx,arr[i]);
	}
	for(int i=0; i<=K+2; i++)Block[i]=-1;
	color++;
	
	int l,r;
	for(int i=0; i<q; i++){
		sii(l,r);
		queries[r-1].push_back({l-1,i});
	}
	
	for(int i=0,cur; i<n; i++){
		for(int j=1,x; j*j<=arr[i]; j++){
			if(arr[i]%j==0){
				update(j, i);
				if(j*j!=arr[i])update(arr[i]/j, i);
			}
		}
		
		for(auto &p:queries[i]){
			mn=p[0];
			cur=Find();
			if(cur==-1)cur=1;
			ans[p[1]]=cur;
		}
	}
	
	for(int i=0; i<q; i++)pf("%d ",ans[i]);
	for(int i=0; i<n; i++)queries[i].clear();
	nl;
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}