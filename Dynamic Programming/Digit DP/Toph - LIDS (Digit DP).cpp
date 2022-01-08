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

pii dp[10][11][2];
vector<int>numL, numR;

pii f(int i, int last, bool b1, bool b2, bool zflag){
	if(i==-1)return pii(0,1);
	pii &ret = dp[i][last][zflag];
	if(ret.first!=-1 && !b1 && !b2)return ret;
	pii val(0,0);
	pii tmp(0,0);
	
	int upper_lim = b2?numR[i]:9;
	int lower_lim = b1?numL[i]:0;

	for(int j=lower_lim; j<=upper_lim; j++){
		tmp = f(i-1, last, (j==numL[i]?b1:0), (j==numR[i]?b2:0), zflag||(j>0));
		if(val.first<tmp.first)val=tmp;
		else if(val.first==tmp.first)val.second += tmp.second;
		
		if((zflag || j>0) && (j>=last)){
			tmp = f(i-1, j+1, (j==numL[i]?b1:0), (j==numR[i]?b2:0), zflag||(j>0));
			tmp.first++;
			if(val.first<tmp.first)val=tmp;
			else if(val.first==tmp.first)val.second += tmp.second;
		
		}
	}
	
	if(!b1 && !b2)ret=val;
	return val;
}

pii get(int x, int y){
	numL.clear();
	numR.clear();
	while(x){
		numL.push_back(x%10);
		x/=10;
	}
	while(y){
		numR.push_back(y%10);
		y/=10;
	}
	while(sz(numL)<sz(numR))numL.push_back(0);
	return f(sz(numL)-1, 0, 1, 1, 0);
}

void solve(int casenum){
	int x,y;
	sii(x,y);
	pii ans = get(x,y);
	pf("Case %d: %d %d\n",casenum, ans.first, ans.second);
	
}

int main(){
	for(int i=0; i<10; i++)
		for(int j=0; j<=10; j++)
			for(int l=0; l<2; l++)
					dp[i][j][l].first = -1;
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