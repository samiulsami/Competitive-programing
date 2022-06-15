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

vector<int>primes;

///log(a^b * c^d) = log(a^b) + log(c^d) = b*log(a) + d*log(c)
pair<ll, bool> dp[30][1005];
bool vis[30][1005]={0};
int n;

pair<ll, bool> f(int i, int divisors){
	if(divisors>n)return {0,0};
	if(divisors==n){
		return {1,1};
	}
	if(i>=sz(primes))return {0,0};
	auto &ret = dp[i][divisors];
	if(vis[i][divisors])return ret;
	vis[i][divisors]=1;
	
	ret.first = 2e18;
	ret.second = 0;
	
	ll curP=1LL;
	for(int j=0; j<=60; j++){
		auto tmp = f(i+1, divisors*(j+1));
		tmp.first*=curP;
		if(tmp.second && tmp.first>0 && tmp.first<=1e18){
			if(tmp.first<ret.first)ret = tmp;
		}
		curP = 1LL*curP*primes[i];
		if(curP>=(ll)1e18)break;
	}
	
	return ret;
}

ll prnt(int i, int divisors){
	if(divisors==n)return 1LL;
	pair<ll, bool>cur;
	cur.first=2e18;
	cur.second=0;
	int nxt=0;
	ll mul=1;
	
	ll curP=1LL;
	for(int j=0; j<=60; j++){
		auto tmp = f(i+1, divisors*(j+1));
		tmp.first*=curP;
		
		if(tmp.second && tmp.first>0 && tmp.first<=1e18){
			if(tmp.first<cur.first){
				cur = tmp;
				nxt=j;
				mul=curP;
			}
		}
		
		curP = 1LL*curP*primes[i];
		if(curP>=(ll)1e18)break;
	}
	//pf("%d %d\n",primes[i],nxt);
	return mul*prnt(i+1,divisors*(nxt+1));
}

void solve(int casenum){
	si(n);
	pf("%lld\n",prnt(0,1));
}

int main(){
	for(int i=2; sz(primes)<25; i++){
		bool isPrime=1;
		for(int j=2; j*j<=i; j++){
			if(i%j==0){
				isPrime=0;
				break;
			}
		}
		if(isPrime)primes.push_back(i);
	}
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