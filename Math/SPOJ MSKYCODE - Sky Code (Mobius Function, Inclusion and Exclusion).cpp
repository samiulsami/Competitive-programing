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

const int N = 10005;

inline ll ncr4(ll n){return (n*(n-1)*(n-2)*(n-3))/24LL;}

ll arr[N];

int mu[N];
inline void mobius(){
	///mu[1] = 1;
	///mu[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mu[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=0; i<N; i++)mu[i]=2;
	mu[1]=1;
	for(int i=2; i<N; i++){
		if(mu[i]==2){
			mu[i]=-1;
			if(i<=N/i){
				int x=i*i;
				for(int j=x; j<N; j+=x)mu[j]=0;
			}
			for(int j=i+i; j<N; j+=i){
				if(mu[j]==2)mu[j]=-1;
				else mu[j]*=-1;
			}
		}
	}
}

int main(){
	mobius();
    
	int n;
	while(scanf("%d",&n)!=EOF){
		memset(arr,0,sizeof(arr));
		for(int i=0,x; i<n; i++){
			si(x);
			arr[x]++;
		}
		
		ll ans=ncr4(n);
		for(int i=2; i<N; i++){
			int cnt=0;
			for(int j=i; j<N; j+=i)cnt+=arr[j];
			ans += 1LL*ncr4(cnt)*mu[i];
		}
		
		pf("%lld\n",ans);
	}
	
	
return 0;
}