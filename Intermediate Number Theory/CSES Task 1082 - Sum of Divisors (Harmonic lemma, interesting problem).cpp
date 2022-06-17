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

const int N = 1e6+5;
const int MOD = 1e9+7;

inline ll sum(ll x){
	x%=MOD;
	return (((x*(x+1LL))%MOD)*500000004)%MOD;
}

inline ll sum(ll l, ll r){
	return (sum(r) - sum(l-1) + MOD)%MOD;
}

void solve(int casenum){
	ll n;
	sl(n);
	
	ll ans=0;
	ll l=1,r,x;
	
	while(l<=n){
		x = n/l;
		r = n/x;
		x%=MOD;

		ans += (sum(l,r)*x)%MOD;
		ans %= MOD;
		ans = (ans+MOD)%MOD;
		l=r+1;
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