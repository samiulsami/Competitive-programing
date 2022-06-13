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

const int N = 3e6+5;
uint64_t phi[N];
uint64_t pre[N];
/*
	LCM(1,n) + LCM(2,n) + ... + LCM(n,n) = (n/2)*[summation i:0 to k](phi[d[i]] * d[i]) + n/2 
	https://forthright48.com/spoj-lcmsum-lcm-sum
*/

void solve(int casenum){
	int n;
	si(n);
	
	pf("Case %d: %llu\n",casenum,pre[n]);
}

int main(){
	for(int i=1; i<N; i++)phi[i]=i;
	for(int i=2; i<N; i++)
		if(phi[i]==i)
			for(int j=i; j<N; j+=i)
				phi[j] -= phi[j]/i;
			
	for(int i=1; i<N; i++)
		for(int j=i; j<N; j+=i)
			pre[j] += (uint64_t)i*phi[i];
		
	pre[0]=0;
	for(uint64_t i=1; i<N; i++){
		uint64_t cur = pre[i];
		cur/=uint64_t(2);
		cur*=i;
		pre[i] = pre[i-1] + cur;
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