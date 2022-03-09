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
	int n,k;
	sf("%d%d",&n,&k);
	vector<array<int,2> >arr(n);
	for(int i=0; i<n; i++)sf("%d%d",&arr[i][0], &arr[i][1]);
	sort(all(arr));
	
	int ans=0;
	multiset<int>ms;
	for(int i=0; i<k; i++)ms.insert(-1);
	
	int cur=0;
	for(int i=0; i<n; i++){
		auto it = ms.lower_bound(arr[i][0]);
		if((it==ms.end() || *it>arr[i][0]) && it!=ms.begin())it--;
		if(*it >arr[i][0]){
			if(*ms.rbegin()>arr[i][1]){
				ms.erase(ms.find(*ms.rbegin()));
				ms.insert(arr[i][1]);
			}
		}
		else{
			ms.erase(ms.find(*it));
			cur++;
			ms.insert(arr[i][1]);
		}
		
	}
	
	pf("%d\n",cur);
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