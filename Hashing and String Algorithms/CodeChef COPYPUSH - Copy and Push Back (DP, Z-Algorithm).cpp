#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e6+5;

string s;
int n;
int dp[2][N];
int vis[2][N]={0};
int color=1;

int f(int i, bool b, vector<int>&z){
	if(i==n)return 1;
	int &ret = dp[b][i];
	if(vis[b][i]==color)return ret;
	vis[b][i]=color;
	ret=0;
	if(i==0)ret = f(i+1,1,z);
	else{
		if(!b)ret = f(i+1,1,z);
		if(z[i]>=i && i+i<=n) ret |= f(i+i,0,z);
	}
	return ret;
}

vector<int> Z_Algo(){
	vector<int>Z(n);
	for(int i=1,l=0,r=0; i<n; i++){
		if(i<=r)Z[i]=min(r-i+1,Z[i-l]);
		while(i+Z[i]<n && s[Z[i]]==s[i+Z[i]])Z[i]++;
		if(i+Z[i]-1>r)l=i,r=i+Z[i]-1;
	}
	return Z;
}

inline void solve(int caseNum){
	cin>>n>>s;
	color++;
	vector<int> z = Z_Algo();
	
	if(f(0,0,z))cout<<"YES\n";
	else cout<<"NO\n";
	
}

int main(){
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}