#include<bits/stdc++.h>
using namespace std;
// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O2")
// #pragma GCC optimization ("unroll-loops")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

const int N = 1e6+5;

int phi[N];
ll gcdSum[N]={0};

int main(){
	for(int i=1; i<N; i++)phi[i]=i;
	for(int i=2; i<N; i++){
		if(phi[i]==i)
			for(int j=i; j<N; j+=i)
				phi[j]-=phi[j]/i;
		for(int j=i; j<N; j+=i)
			gcdSum[j] += 1LL*(j/i)*phi[i];
		gcdSum[i] += gcdSum[i-1];
	}
	
	int n;
	while(scanf("%d",&n)){
		if(n==0)break;
		pf("%lld\n",gcdSum[n]);
	}
   
return 0;
}