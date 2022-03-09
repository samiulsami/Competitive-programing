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
 
int mp[N],arr[N];
 
void solve(int casenum){
	int n,m;
	sf("%d%d",&n,&m);
	
	for(int i=1; i<=n; i++){
		sf("%d",&arr[i]);
		mp[arr[i]]=i;
	}
	
	auto query = [&](int l, int r)->void{
		if(l==r)return;
		swap(mp[arr[l]],mp[arr[r]]);
		swap(arr[l],arr[r]);
	};
	
	auto get = [&](int l)->int{
		int ret=0;
		int x = arr[l];
		if(x>1 && mp[x-1]>l)ret++;
		if(x<n && mp[x+1]<l)ret++;
		return ret;
	};
	
	
	int cur=mp[1];
	int ans=1;
	for(int i=2; i<=n; i++){
		if(mp[i]<cur)ans++;
		cur=mp[i];
	}
	//dbug(ans);
	
	for(int i=0,l,r; i<m; i++){
		sf("%d%d",&l,&r);
		
		if(l!=r){
			if(l>r)swap(l,r);
			
			int diff = get(l) + get(r);
			if(min(arr[l],arr[r])+1==max(arr[l], arr[r]) && arr[l]>arr[r])diff--;
			query(l,r);
			int diff2 = get(l) + get(r);
			if(min(arr[l],arr[r])+1==max(arr[l], arr[r]) && arr[l]>arr[r])diff2--;
			//pf("1: %d, 2: %d\n",diff, diff2);
			ans+=(diff2-diff);
		}
		// for(int j=1; j<=n; j++)cout<<arr[j]<<" ";
		// cout<<endl;
		pf("%d\n",ans);
	}
}
 
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}