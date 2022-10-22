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
const int lcmval = 2*3*5*7;
///len, mask, 2 mod, 3 mod, 5mod, 7mod
ll dp[19][(1<<5)][lcmval][2];
vector<int>num;


ll f(int i, int mask, int mod, bool b, bool zflag){
	if(i==-1){
		if(bool(mask&16))return 1;
		if(bool(mask&1) && mod%2==0)return 1;//2
		if(bool(mask&2) && mod%3==0)return 1;//3
		if(bool(mask&4) && mod%5==0)return 1;//5
		if(bool(mask&8) && mod%7==0)return 1;//7
		return 0;
	}
	
	ll &ret = dp[i][mask][mod][zflag];
	if(~ret && !b)return ret;
	ll val=0;
	
	int upper_lim = b?num[i]:9;
	for(int j=0,newmask; j<=upper_lim; j++){
		newmask=mask;
		if(j){
			if(j%2==0)newmask |= 1;
			if(j%3==0)newmask |= 2;
			if(j==5)newmask |= 4;
			if(j==7)newmask |= 8;
		}
		else if(j==0 && zflag){
			newmask |= 16;
		}
		
		val += f(i-1, newmask, (mod*10 + j)%lcmval, (j==num[i]?b:0), zflag||(j>0));
	}
	
	if(!b)ret = val;
	return val;
}

ll get(ll val){
    num.clear();
    while(val){
        num.push_back(val%10LL);
        val/=10LL;
    }
    return f(sz(num)-1,0,0,1,0);
}

bool isPleasure(ll x){
	ll prod=1;
	ll tmp = x;
	while(x){
		prod *= (x%10);
		x/=10;
	}
	return __gcd(prod,tmp)>1;
}

ll brute(ll a, ll b){
	ll ret=0;
	for(;a<=b;a++)ret += (ll)isPleasure(a);
	return ret;
}

void solve(int casenum){
	//dbug((20*17*4*5*7*9));
	ll a,b;
	sll(a,b);
	if(a>b)swap(a,b);

	ll ans = (get(b)-get(a-1));
	//pf("%lld %lld\n",brute(a,b),ans);
	pf("%lld\n",ans);
}

int main(){
	memset(dp,-1,sizeof(dp));
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