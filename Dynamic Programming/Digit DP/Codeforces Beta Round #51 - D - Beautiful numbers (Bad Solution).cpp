#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
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
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

ll dp[19][9][8][7][2][(1<<8)+1][2];
vi numL,numR;

inline int getmask(int &mask, int add){
	if(add<2)return mask;
	return mask|(1<<(add-2));
}

ll f(int i, int f9, int f8, int f7, bool f5, int mask, bool b1, bool b2, bool zflag){
	if(i==-1){
		if(chkbit(mask,7) && f9)return 0;
		if(chkbit(mask,6) && f8)return 0;
		if(chkbit(mask,5) && f7)return 0;
		if(chkbit(mask,4) && (f9%3 || f8%2))return 0;
		if(chkbit(mask,3) && !f5)return 0;
		if(chkbit(mask,2) && f8%4)return 0;
		if(chkbit(mask,1) && f9%3)return 0;
		if(chkbit(mask,0) && f8%2)return 0;
		return zflag;
	}
	
	ll &ret = dp[i][f9][f8][f7][f5][mask][zflag];
	if(~ret && !b1 && !b2)return ret;
	ll val=0;
	int upper_lim = b1?numR[i]:9;
	int lower_lim = b2?numL[i]:0;
	
	for(int j=lower_lim; j<=upper_lim; j++){
		val+=f(i-1, (f9*10 + j)%9, (f8*10 + j)%8, (f7*10 + j)%7, (j==0 || j==5), getmask(mask,j), (numR[i]==j)?b1:0, (numL[i]==j)?b2:0, zflag||(j>0));
	}
	
	if(!b1 && !b2)ret=val;
	return val;
}

ll calc(ll a, ll b){
	numL.clear();
	numR.clear();
	while(a){
		numL.push_back(a%10);
		a/=10;
	}
	while(b){
		numR.push_back(b%10);
		b/=10;
	}
	while(sz(numL)<sz(numR))numL.push_back(0);
	return f(sz(numL)-1, 0, 0, 0, 0, 0, 1, 1, 0);
}

void solve(int casenum){

	ll a,b;
	sll(a,b);
	pf("%lld\n",calc(a,b));
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