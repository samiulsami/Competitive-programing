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
 
const int N = 2e5+5;
 
int arr[N];
ll suff[N]={0};
 
void solve(int casenum){
	int n,a,b;
	sf("%d%d%d",&n,&a,&b);
	
	for(int i=0; i<n; i++){
		sf("%d",&arr[i]);
	}
	
	ll cursum=0;
	int r=n-1,l;
	for(int i=n-1; i>=0; i--){
		cursum += arr[i];
		while(r>=i && (r-i+1>b-a)){
			cursum-=arr[r--];
		}
		suff[i] = cursum;
		if(cursum<=0){
			cursum=0;
			r=i-1;
		}
	}
	
	cursum=0;
	r=0,l=0;
	ll ans=-1e18;
	while(r<n){
		while(r-l<a && r<n){
			cursum+=arr[r];
			r++;
		}
		if(r-l<a)break;
		ans = max(ans, cursum);
		if(r<n)ans = max(ans,cursum+suff[r]);
		cursum-=arr[l++];
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