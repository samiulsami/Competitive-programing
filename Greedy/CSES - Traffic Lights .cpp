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
	int x,n;
	sf("%d%d",&x,&n);
	
	set<int>st;
	st.insert(x);
	st.insert(0);
	int lft=0,rgt=x;
	set<array<int,3> >pts;
	pts.insert({rgt-lft,lft,rgt});
	
	for(int i=0,a; i<n; i++){
		sf("%d",&a);
		st.insert(a);
		int l,r;
		auto itL = st.lower_bound(a);
		itL--;
		l = *itL;
		r = *st.upper_bound(a);
		
		pts.erase({r-l,l,r});
		pts.insert({a-l,l,a});
		pts.insert({r-a,a,r});
		
		pf("%d ",(*pts.rbegin())[0]);
	}
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