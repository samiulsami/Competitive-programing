#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;

ll dp[20][(1<<11)+2][12][2];
vector<int>num;
int k;

ll f(int i, int mask, bool b, bool zflag){
	if(i==-1)return zflag && __builtin_popcount(mask)<=k;
	ll &ret = dp[i][mask][k][zflag];
	if(ret!=-1 && !b)return ret;
	ll val=0;
	int upper_lim = b?num[i]:9;
	
	for(int j=0,newmask; j<=upper_lim; j++){
		newmask=mask;
		if(j || (j==0 && zflag))newmask|=(1<<j);
		val+=f(i-1,newmask,(j==num[i])?b:0,(zflag||(j>0)));
	}
	if(!b)ret=val;
	return val;
}

ll get(ll val){
    num.clear();
    while(val){
        num.push_back(val%10LL);
        val/=10LL;
    }
    return f(sz(num)-1,0,1,0);
}


void solve(int casenum){
	int n;
	sii(n,k);
	
	ll cur = get(n-1);

	ll ans=1e18;
	ll low=n,high=1e18,mid;
	while(low<=high){
		mid=(low+high)>>1;
		if(get(mid)-cur >0){
			ans=min(ans,mid);
			high=mid-1;
		}
		else low=mid+1;
	}
	pf("%lld\n",ans);
	
}

int main(){
	memset(dp,-1,sizeof(dp));
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}