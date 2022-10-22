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

const int primesN=1e6+6;
uint32_t status[(primesN>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<int>primes;
 
void sieve(){
    uint32_t sq=sqrt(primesN)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<=primesN; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<=primesN; i+=2)if(!checkP(i))primes.push_back(i);
}

ll phi(ll x){
	ll ret = x;
	for(int p:primes){
		if(1LL*p*p>x)break;
		if(x%p==0){
			ret-=(ret/p);
			while(x%p==0)x/=p;
		}
	}
	if(x>1)ret-=(ret/x);
	return ret;
}


void solve(int casenum){
	ll n;
	int q;
	sf("%lld %d",&n,&q);
	
	vector<array<ll,2> >arr;
	for(ll i=1; i*i<=n; i++){
		if(n%i==0){
			arr.push_back({i,phi(n/i)});
			if(i*i!=n)arr.push_back({n/i,phi(i)});
		}
	}
	sort(all(arr));
	for(int i=1; i<sz(arr); i++)arr[i][1] += arr[i-1][1];
	
	ll x;
	int low,high,mid;
	ll ans=0;
	pf("Case %d\n",casenum);
	while(q--){
		sl(x);
		if(x>=n){
			pf("%lld\n",n);
			continue;
		}
		low=0,high=int(arr.size())-1;
		ans=0;
		while(low<=high){
			mid = (low+high)>>1;
			if(arr[mid][0]<=x){
				ans = arr[mid][1];
				low=mid+1;
			}
			else high=mid-1;
		}
		
		pf("%lld\n",ans);
	}
}

int main(){
	sieve();
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