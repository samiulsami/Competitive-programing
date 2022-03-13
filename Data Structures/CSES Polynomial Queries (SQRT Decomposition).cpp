#include<bits/stdc++.h>
using namespace std;

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

const int N = 2e5+5;
const int K = 450;

ll BlockSum[K+1]={0};
ll arr[N];
ll Lazy[K+1]={0};
ll LazyCount[K+1]={0};
int n,q;

inline ll getSum(ll x){
	if(x<=0)return 0;
	return (x*(x+1))/2LL;
}

inline ll getSum(ll l, ll r){return getSum(r) - getSum(l-1);}

inline void push_lazy(int i){
	if(!Lazy[i])return;
	for(int j = (i*K), ed = min(n,j+K); j<ed; j++){
		arr[j]+=Lazy[i];
		Lazy[i]+=LazyCount[i];
	}
	Lazy[i]=0;
	LazyCount[i]=0;
}

inline void update(int l, int r){
	int L=l/K,R=r/K;
	if(L==R){
		push_lazy(L);
		ll add=1;
		for(;l<=r; l++){
			arr[l]+=add;
			BlockSum[L]+=add;
			add++;
		}
		return;
	}
	
	push_lazy(L);
	push_lazy(R);
	ll add=1;
	for(int i=l,x=(L+1)*K; i<x; i++){
		arr[i]+=add;
		BlockSum[L]+=add;
		add++;
	}
	
	for(int i=L+1,ed=R-1; i<=ed; i++){
		Lazy[i]+=add;
		LazyCount[i]++;
		BlockSum[i]+=getSum(add,add+K-1);
		add+=K;
	}
	
	for(int i=(R*K); i<=r; i++){
		arr[i]+=add;
		BlockSum[R]+=add;
		add++;
	}
	
}

inline ll query(int l, int r){
	int L=l/K,R=r/K;
	if(L==R){
		push_lazy(L);
		ll ret=0;
		for(;l<=r; l++)ret+=arr[l];
		return ret;
	}
	
	push_lazy(L);
	push_lazy(R);
	ll ret=0;
	for(int i=l, x = (L+1)*K; i<x; i++)ret+=arr[i];
	for(int i=(R*K); i<=r; i++)ret+=arr[i];
	
	for(int i=L+1,ed=R-1; i<=ed; i++)
		ret+=BlockSum[i];
	
	return ret;
}

void solve(int casenum){

	sii(n,q);
	FOR(i,0,n-1){
		sl(arr[i]);
		BlockSum[i/K]+=arr[i];
	}
	
	int t,l,r;
	while(q--){
		siii(t,l,r);
		l--,r--;
		if(t==1)update(l,r);
		else pf("%lld\n",query(l,r));
	}
	
	
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}