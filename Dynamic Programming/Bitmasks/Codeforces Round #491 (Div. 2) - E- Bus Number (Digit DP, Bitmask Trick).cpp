#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;
///digits can't occur more times than they occur in n
///each digit that occurs in n must occur at least once in the bus number

ll dp[20][(1<<18)+5][2];
int maxOcc[15]={0},csum[15]={0};

int setMask(int mask, int x){
	///add digit x to mask
	if(maxOcc[x]==0)return -1;
	int start = csum[x];
	int cnt=0;
	for(int i=start; i<=start+maxOcc[x]-1; i++)
		cnt+=int(bool(mask&(1<<i)));
	if(cnt==maxOcc[x])return -1;
	return (mask|(1<<(cnt+start)));
}

inline bool check(int mask){
	for(int i=0; i<=9; i++){
		if(maxOcc[i] && !bool(mask&(1<<csum[i])))return 0;		
	}
	return 1;
}

vector<int>xd;

ll f(int i, int mask, bool zflag){
	if(i==-1){
		// if(zflag && check(mask)){
		// 	for(int j:xd)cout<<j;
		// 		cout<<endl;
		// }
		return zflag && check(mask);
	}
	 ll &ret = dp[i][mask][zflag];
	 if(~ret)return ret;
	ret=0;

	for(int d=0; d<=9; d++){
		int newmask = mask;
		if(zflag || d>0)newmask = setMask(mask,d);
		if(newmask==-1)continue;
		//if(zflag || d>0)xd.push_back(d);
		ret += f(i-1,newmask,zflag||(d>0));
		//if(zflag || d>0)xd.pop_back();
	}
	return ret;
}

inline void solve(int caseNum){
	memset(dp,-1,sizeof(dp));

	ll n;
	cin>>n;

	ll tmp = n;
	int len=0;
	while(n){
		len++;
		maxOcc[n%10]++;
		n/=10;
	}

	csum[0] = 0;
	for(int i=1; i<=9; i++){
		csum[i] = maxOcc[i-1] + csum[i-1];			
	}
	// for(int i=0; i<=9; i++){
	// 	cout<<i<<" "<<csum[i]<<endl;
	// }

	cout<<f(19,0,0)<<"\n";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}