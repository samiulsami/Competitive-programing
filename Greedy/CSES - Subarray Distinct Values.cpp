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
int arr[200005];
 
void solve(int casenum){
	int n,k;
	sf("%d%d",&n,&k);
	for(int i=0; i<n; i++){
		sf("%d",&arr[i]);
	}
	
	map<int,int>mp;
	int distinct=0;
	
	auto add = [&](int x)->void{
		if(++mp[x]==1)distinct++;
	};
	
	auto rem = [&](int x)->void{
		if(--mp[x]==0)distinct--;
	};
	
	ll ans=0;
	int l=0,r=0;
	while(r<n){
		while(distinct<=k && r<n){
			add(arr[r++]);
		}
		
		if(distinct<=k){///r == n
			ll tmp = r-l;
			ans += (tmp*(tmp+1))/2;
			break;
		}
		else{
			rem(arr[--r]);
			ans+=(r-l);
			rem(arr[l++]);
		}
	}
	
	pf("%lld\n",ans);
}
 
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}