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

int add[101][2];
int dp[101],p;
vi L,R;

int f(int i, bool lLim, bool rLim){
	if(i==p){
		if(lLim || rLim)return 1e6;
		return 0;
	}
	int &ret = dp[i];
	if(~ret && !lLim && !rLim)return ret;
	
	int cur=1e6;
	int lower_lim = lLim?L[i]:0;
	int upper_lim = rLim?R[i]:1;
	
	for(int j=lower_lim; j<=upper_lim; j++){
		cur = min(cur, f(i+1, (j==L[i]?lLim:0), (j==R[i]?rLim:0)) + add[i][j]);
	}
	
	if(!lLim && !rLim)ret=cur;
	return cur;
}

int get(string l, string r, bool zero1=1, bool zero2=1){
	L.clear();
	R.clear();
	for(char i:l)L.push_back(i-'0');
	for(char i:r)R.push_back(i-'0');
	return f(0,zero1,zero2);
}

void solve(int casenum){
	int n,m;
	siii(n,m,p);
	static char in[102];
	memset(dp,-1,sizeof(dp));
	for(int i=0; i<p; i++)add[i][0]=add[i][1]=0;
	for(int i=0; i<n; i++){
		sf(" %s",&in);
		for(int j=0; j<p; j++){
			if(in[j]=='0')add[j][1]++;
			else add[j][0]++;
		}
	}
	
	vector<string>lim;
	string tmp(p,'0');
	int ans = 1e9;
	for(int i=0; i<m; i++){
		sf(" %s",&in);
		lim.push_back(string(in));
	}
	
	sort(all(lim));
	if(tmp!=lim[0])ans = get(tmp,lim[0],0,1);
	for(int i=1; i<m; i++)
		ans = min(ans, get(lim[i-1], lim[i]));

	tmp.clear();
	tmp = string(p,'1');
	if(lim.back()!=tmp)
		ans = min(ans, get(lim.back(),tmp,1,0));
	
	pf("Case #%d: %d\n",casenum,ans);
}

int main(){
   // ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}