#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;
const int K = 24;
int dp[(1<<K)]={0};

inline void solve(int caseNum){
	int n;
	cin>>n;
	string s;
	int x;
	for(int i=0; i<n; i++){
		cin>>s;
		x=0;
		for(char c:s)x|=(1<<(c-'a'));
		for(int y=x; y>0; y = (y-1)&x){
			if(__builtin_popcount(y)&1)dp[y]++;
			else dp[y]--;
		}
	}
	
	for(int i=0; i<K; i++)
		for(int mask=0,mx=(1<<K); mask<mx; mask++)
			if(mask&(1<<i))dp[mask] += dp[mask^(1<<i)];
		
	ll ans=0;
	for(int mask=0,mx=(1<<K); mask<mx; mask++){
		ans ^= (1LL*dp[mask]*dp[mask]);
	}
	cout<<ans<<"\n";
}

int main(){
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}