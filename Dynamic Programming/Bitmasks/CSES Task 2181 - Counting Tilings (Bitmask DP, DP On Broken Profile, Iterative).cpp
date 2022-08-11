#include<bits/stdc++.h>
using namespace std;
 
typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}
 
const int N = 2e5+5;
const int MOD = 1e9+7;
 
int n,m;
int dp[11][1001][(1<<10)+1];
inline bool chk(int msk, int i){return msk&(1<<i);}
 
 
inline void solve(int caseNum){
	cin>>n>>m;
 	
 	for(int i=0; i<=n; i++){
 		for(int j=0; j<=m; j++){
 			for(int mask=0,x=(1<<n); mask<x; mask++)
 				dp[i][j][mask] = (j==m && mask==0);
 		}
 	}

 	for(int j=m-1; j>=0; j--){
 		for(int i=n-1; i>=0; i--){
 			for(int mask=0,x=(1<<n); mask<x; mask++){
 				int &ret = dp[i][j][mask];
 				if(i==n-1)ret = dp[0][j+1][mask^(1<<i)];
 				else if(chk(mask,i))ret = dp[i+1][j][mask^(1<<i)];
 				else{
 					ret = dp[i+1][j][mask|(1<<i)];
 					if(ret>=MOD)ret-=MOD;
 					if(!chk(mask,i+1)){
 						int _nxti = i+2;
 						int _nxtj = j;
 						if(i+2==n){
 							_nxti = 0;
 							_nxtj = j+1;
 						}
 						ret += dp[_nxti][_nxtj][mask];
 						if(ret>=MOD)ret-=MOD;
 					}
 				}
 				if(ret>=MOD)ret-=MOD;
 			}
 		}
 	}

 	cout<<dp[0][0][0]<<"\n";
}
 
int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}