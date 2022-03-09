#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef long double ld;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<"\n"
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;


void solve(int casenum){
	int n,d;
	sf("%d%d",&n,&d);
	vector<int>arr(n+1,0);
	multiset<int>ms;
	
	for(int i=1; i<=n; i++){
		sf("%d",&arr[i]);
		ms.insert(arr[i]-arr[i-1]-1);
	}


	int ans=*ms.begin();
	for(int i=1; i<=n; i++){
		bool added=0;
		
		ms.erase(ms.find(arr[i]-arr[i-1]-1));
		if(i+1<=n){
			ms.erase(ms.find(arr[i+1]-arr[i]-1));
			added=1;
			ms.insert(arr[i+1]-arr[i-1]-1);
		}
		
		int curmax;
		if(i==n)curmax=d-arr[n-1]-1;
		else curmax=d-arr[n]-1;
		curmax = max(curmax, (*ms.rbegin() - 1)/2);
		
		ans=max(ans, min(*ms.begin(), curmax));
		
		if(added){
			ms.erase(ms.find(arr[i+1]-arr[i-1]-1));
			ms.insert(arr[i+1]-arr[i]-1);
		}
		ms.insert(arr[i]-arr[i-1]-1);
	}
	
	pf("%d\n",ans);
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}