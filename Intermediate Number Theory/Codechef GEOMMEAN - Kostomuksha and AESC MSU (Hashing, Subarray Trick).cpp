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
const int MOD[2] = {998244353, 1000000007};

int bigMod(int a, int b, bool x=0){
    if(a==0)return 0;
    int ret=1;
    a%=MOD[x];
    while(b>0){
        if(b&1)ret=(1LL*ret*a)%MOD[x];
        b>>=1;
        a=(1LL*a*a)%MOD[x];
    }
    return ret%MOD[x];
}


inline int modMul(int a, int b, bool x=0){
	return (1LL*a*b)%MOD[x];
}

int X[2][N];
int a[N];

void solve(int casenum){
	int n,x;
	sii(n,x);
	X[0][0]=1;
	X[1][0]=1;
	
	FOR(i,1,n){
		si(a[i]);
		X[0][i] = (1LL*X[0][i-1]*x)%MOD[0];
		X[1][i] = (1LL*X[1][i-1]*x)%MOD[1];
	}
	
	X[0][n+1] = (1LL*X[0][n]*x)%MOD[0];
	X[1][n+1] = (1LL*X[1][n]*x)%MOD[1];
	
	map<pii, int>mp;
	array<int,2>prod{1,1};
	ll ans=0;
	
	for(int i=1; i<=n; i++){
		array<int,2>p{0,0},q{0,0};
		
		for(int j=0; j<=1; j++){
			prod[j] = (1LL*prod[j]*a[i])%MOD[j];
			p[j] = (1LL*X[j][i+1]*bigMod(prod[j],MOD[j]-2,j))%MOD[j];
			q[j] = (1LL*X[j][i]*bigMod(prod[j],MOD[j]-2,j))%MOD[j];
		}
		
		if(prod[0]==X[0][i] && prod[1]==X[1][i])ans++;
		ans+=mp[p];
		mp[p]++;
	}
	
	//pf("ans: ");
	pf("%lld\n",ans);
}

int main(){
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