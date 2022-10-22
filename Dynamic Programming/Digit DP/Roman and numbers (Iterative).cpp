#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;
string n;
int m;

ll dp[(1<<18)][100];

inline void solve(int caseNum){
	cin>>n>>m;
	sort(all(n));

	dp[(1<<n.length())-1][0]=1;
	for(int mask = (1<<n.length())-2; mask>=0; mask--){
		for(int i=0,j; i<n.length(); i++){
			if(mask&(1<<i))continue;
			j=i;
			while(j+1<n.length() && n[i]==n[j+1])j++;
			for(int rem=0; rem<m; rem++)
				dp[mask][rem] += dp[mask|(1<<i)][(rem*10 + (n[i]-'0'))%m];
			i=j;
		}
	}

	ll ans=0;
	for(int i=0; i<n.length(); i++){
		if(n[i]=='0')continue;
		int j=i;
		while(j+1<n.length() && n[i]==n[j+1])j++;
		ans += dp[(1<<i)][(n[i]-'0')%m];
		i=j;
	}

	cout<<ans;
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