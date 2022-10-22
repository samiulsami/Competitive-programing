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

int dp[1000005]={0};
int spf[10000005]={0};

void solve(int casenum){
	spf[1]=1;
	for(int i=2; i<=1000000; i++){
		if(spf[i]==0){
			for(int j=i; j<=1000000; j+=i){
				if(spf[j]==0)spf[j]=i;
				else spf[j]=min(spf[j],i);
			}
		}
	}
	
	int n;
	si(n);
	ll ans=(1LL*n*(1LL*n-1LL))/2LL;
	
	for(int i=0,x; i<n; i++){
		si(x);
		vector<int>primes;
		while(x>1){
			int p = spf[x];
			primes.push_back(p);
			while(x%p==0)x/=p;
		}
		
		int primeCount=int(primes.size());
		for(int mask=1; mask<(1<<primeCount); mask++){
			int mult = 1;
			for(int j=0; j<primeCount; j++)
				if(bool(mask&(1<<j)))mult*=primes[j];
			
			if(__builtin_popcount(mask)&1)ans -= dp[mult];
			else ans += dp[mult];
			
			dp[mult]++;
		}
	}
	
	pf("%lld\n",ans);
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