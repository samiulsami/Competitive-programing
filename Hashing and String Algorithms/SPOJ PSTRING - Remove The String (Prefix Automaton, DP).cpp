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


const int N = 1e3+5;


int dp[10001][1001];

const int _chars=26;
int nxt[1005][_chars];

inline int charMap(char c){
	if(c>='a' && c<='z')return c-'a';
	if(c>='A' && c<='Z')return c-'A'+26;
	return c-'0'+52;
}

void prefixautomaton(const string &s){
	int n = (int)s.size();
	vector<int>pi(n);
	for(int i=1,j=0; i<n; i++){
		j=pi[i-1];
		while(j && s[i]!=s[j])j=pi[j-1];
		if(s[i]==s[j])pi[i]=j+1;
		else pi[i]=0;
	}
	for(int i=0; i<_chars; i++){
		if(charMap(s[0])==i)nxt[0][i]=1;
		else nxt[0][i]=0;
	}
	for(int i=1; i<=n; i++){
		for(int c=0; c<_chars; c++){
			if(i==n || charMap(s[i])!=c)nxt[i][c]=nxt[pi[i-1]][c];
			else nxt[i][c]=i+1;
		}
	}
}

string x,y;

// int f(int i, int j){
	// if(i==x.length())return 0;
	// int &ret = dp[i][j];
	// if(vis[i][j]==color)return ret;
	// vis[i][j]=color;
	
	// ret = 1+f(i+1,j);
	// if(nxt[j][charMap(x[i])]!=y.length()){
		// ret=min(ret, f(i+1, nxt[j][charMap(x[i])]));
	// }
	// return ret;
// }

void solve(int casenum){
	int n,m;
	while(cin>>x>>y){
		prefixautomaton(y);
		n=sz(x);
		m=sz(y);
		int ans=1e9;
		
		for(int i=0; i<=n; i++){
			for(int j=0; j<=m; j++){
				if(i==n){
					if(j==m)dp[i][j]=1e5;
					else dp[i][j]=0;
				}
				else dp[i][j]=1e5;
			}
		}
		for(int i=n-1; i>=0; i--){
			for(int j=0; j<m; j++){
				dp[i][j] = min(dp[i][j], dp[i+1][nxt[j][charMap(x[i])]]);
				dp[i][j] = min(dp[i][j], 1+dp[i+1][j]);
				if(i==0)ans=min(ans,dp[0][j]);
			}
		}
		cout<<ans<<"\n";
	}
	
}

int main(){
   // ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}