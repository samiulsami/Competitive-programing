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


const int primesN=1e4+5;
int mobius[primesN];
uint32_t status[(primesN>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<int>primes;

void sieve(){
    uint32_t sq=sqrt(primesN)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<primesN; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<primesN; i+=2)if(!checkP(i))primes.push_back(i);
}

void mobius_init(){
	///mobius[1] = 1;
	///mobius[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mobius[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=1; i<primesN; i++)mobius[i]=1;
	for(int p:primes){
		if(1LL*p*p>=primesN)break;
		int x = p*p;
		for(int j=x; j<primesN; j+=x)mobius[j]=0;
	}
	for(int p:primes)
		for(int j=p; j<primesN; j+=p)mobius[j] *= -1;
}



int freq[primesN]={0};
inline ll ncr4(ll n){
	return (n*(n-1)*(n-2)*(n-3))/24LL;
}

void solve(int casenum){
	int n;
	si(n);
	memset(freq,0,sizeof(freq));
	for(int i=0,x; i<n; i++){
		si(x);
		freq[x]++;
	}
	
	ll ans =0;
	for(int i=1; i<=10000; i++){
		ll cnt=0;
		for(int j=i; j<=10000; j+=i)cnt+=freq[j];
		
		//dbug(cnt);
		ans += 1LL*mobius[i]*ncr4(cnt);
	}
	
	pf("Case %d: %lld\n",casenum,ans);
}

int main(){
	sieve();
	mobius_init();
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