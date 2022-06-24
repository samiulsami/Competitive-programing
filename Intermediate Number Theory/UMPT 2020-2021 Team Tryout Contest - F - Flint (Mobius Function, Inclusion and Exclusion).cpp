#include<bits/stdc++.h>
using namespace std;
///https://codeforces.com/gym/102944/problem/F

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

const int N = 1e5+5;

uint32_t status[(N>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<int>primes;

void sieve(){
    uint32_t sq=sqrt(N)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<N; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<N; i+=2)if(!checkP(i))primes.push_back(i);
}

///mobius[1] = 1;
///mobius[x] = 0 if x is divisible by a^2 where 'a' is a prime
///mobius[x] = (-1)^k if 'x' is the product of 'k' distinct primes

int mobius(int x){
	if(x==1)return 1;
	int ret = 1;
	
	for(int p:primes){
		if(1LL*p*p>x)break;
		if(x%p==0){
			x/=p;
			ret = -ret;
			if(x%p==0)return 0;
		}
	}
	
	if(x>1)ret = - ret;
	return ret;
}

const int MOD = 1e9+7;

map<int,int>freq;
int _pow2[300];

void solve(int casenum){
	int n;
	si(n);
	for(int i=0,x; i<n; i++){
		si(x);
		
		for(int j=1; 1LL*j*j<=x; j++){
			if(x%j==0){
				freq[j]++;
				if(1LL*j*j!=x)freq[x/j]++;
			}
		}
	}
	
	int ans=0,mul;
	
	for(auto it:freq){
		mul = _pow2[it.second]-1;
		if(mul<0)mul += MOD;
		mul = (mobius(it.first)*mul);
		if(mul<0)mul += MOD;
		ans = (ans + mul)%MOD;
		if(ans<0)ans += MOD;
	}
	
	ans%=MOD;
	pf("%d\n",ans);
}

int main(){
	sieve();
	_pow2[0]=1;
	for(int i=1; i<200; i++)_pow2[i] = (1LL*_pow2[i-1]*2)%MOD;
	
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