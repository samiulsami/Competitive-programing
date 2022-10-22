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

const int N = 1e7+5;
int phi[N];
ll phiSum[N];


void solve(int casenum){
	ll n,p;
	sll(n,p);
	
	ll ans=-1,low=1,high=n,mid;
	while(low<=high){
		mid = (low+high)>>1;
		if(phiSum[mid]>=p){
			ans=mid;
			high=mid-1;
		}
		else low=mid+1;
	}
	
	if(ans!=-1)ans = n/ans;
	pf("Case %d: %lld\n",casenum,ans);
}

int main(){
	for(int i=1; i<N; i++)phi[i]=i;
	for(int i=2; i<N; i++){
		if(phi[i]==i){
			for(int j=i; j<N; j+=i){
				phi[j] -= phi[j]/i;
			}
		}
	}
	phiSum[0]=0;
	for(int i=1; i<N; i++)phiSum[i] = phiSum[i-1] + phi[i];
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