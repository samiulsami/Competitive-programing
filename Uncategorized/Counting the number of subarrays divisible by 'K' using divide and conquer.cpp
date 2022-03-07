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
int n;
 
ll f(int l, int r){
	if(l>r)return 0;
	if(l==r)return arr[l]%n==0;
 
	int mid = (l+r)>>1;
	ll ret = f(l,mid) + f(mid+1, r);
	
	map<ll,int>mp;
	ll sum=0;
	for(int i=mid; i>=l; i--){
		sum = (sum+arr[i])%n;
		mp[sum]++;
	}
	
	sum=0;
	for(int i=mid+1; i<=r; i++){
		sum = (sum+arr[i])%n;
		if(sum==0)ret+=mp[0];
		else ret += mp[n-sum];
	}
	return ret;
}
 
void solve(int casenum){
	sf("%d",&n);
	for(int i=0; i<n; i++){
		sf("%d",&arr[i]);
		arr[i]%=n;
		if(arr[i]<0)arr[i]+=n;
	}
	
	pf("%lld\n",f(0,n-1));
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