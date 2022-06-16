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

inline ll ncr4(ll n){return (n*(n-1)*(n-2)*(n-3))/24LL;}

vector<int>divisors[10005];
ll arr[10005];

int main(){
	for(int i=1; i<10005; i++){
		for(int j=i; j<10005; j+=i)divisors[j].push_back(i);
	}
    
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0; i<=10000; i++)arr[i]=0;
		for(int i=0,x; i<n; i++){
			si(x);
			for(int j:divisors[x])arr[j]++;
		}
		
		for(int i=10000; i>=1; i--){
			arr[i] = ncr4(arr[i]);
			for(int j=i+i; j<=10000; j+=i)arr[i] -= arr[j];
		}
		
		pf("%lld\n",arr[1]);
	}
	
	
return 0;
}