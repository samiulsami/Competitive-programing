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

typedef uint32_t ui;
const int primesN=1e8+5;
uint32_t status[(primesN>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<ui>primes;
ui mul[60000000];

void sieve(){
    uint32_t sq=sqrt(primesN)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<=primesN; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<=primesN; i+=2)if(!checkP(i))primes.push_back(i);
}
 

void solve(int casenum){
	int n;
	si(n);
	
	int ind,low=0,high=sz(primes)-1,mid;
	while(low<=high){
		mid = (low+high)>>1;
		if(primes[mid]>n)high=mid-1;
		else {
			ind=mid;
			low=mid+1;
		}
	}
	
	ui ans = mul[ind];
	for(ui p:primes){
		if(1LL*p*p>n)break;
		ui tmpn=n;
		int cnt=0;
		
		while(tmpn/p>0){
			cnt++;
			tmpn/=p;
		}
		
		cnt--;
		while(cnt--)ans*=p;
	}
	
	pf("Case %d: %u\n",casenum,ans);
}

int main(){
	primes.reserve(5e7+5);
	sieve();
	
	for(int i=0; i<sz(primes); i++){
		if(i==0)mul[i]=primes[i];
		else mul[i] = primes[i]*mul[i-1];
	}
	
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