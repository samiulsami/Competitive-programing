#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int K = 22;
const int N = 1e6+5;

int dp[(1<<K)];
int arr[N];

inline void solve(int caseNum){
	memset(dp,-1,sizeof(dp));
	int n;
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>arr[i];
		dp[arr[i]]=arr[i];
	}
	
	for(int i=0; i<K; i++){
		for(int mask=0,mx=(1<<K); mask<mx; mask++){
			if(bool(mask&(1<<i)) && dp[mask^(1<<i)]!=-1)
				dp[mask] = dp[mask^(1<<i)];
		}
	}
	
	for(int i=0; i<n; i++)cout<<dp[(~arr[i])&((1<<K)-1)]<<" ";
	cout<<"\n";
	
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