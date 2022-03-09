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
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int N = 1e5+5;
 
 
 
void solve(int casenum){
	int n;
	sf("%d",&n);
	vector<array<int,3>>arr(n);
	vector<int> contains(n),contained(n);
	for(int i=0; i<n ;i++)sf("%d%d",&arr[i][0],&arr[i][1]),arr[i][2]=i;
	sort(all(arr), [&](auto &a, auto &b)->bool{
		if(a[0]==b[0])return a[1]>b[1];
		return a[0]<b[0];
	});
	
	orderSet<pii>st;
	for(int i=0; i<n; i++){
		contained[arr[i][2]]=sz(st)-st.order_of_key({arr[i][1],-1});
		st.insert({arr[i][1],i});
	}
	
	st.clear();
	for(int i=n-1; i>=0; i--){
		contains[arr[i][2]]=st.order_of_key({arr[i][1],1000000000});
		st.insert({arr[i][1],i});
	}
	
	for(int i=0; i<n; i++)pf("%d ",contains[i]);
	pf("\n");
	for(int i=0; i<n; i++)pf("%d ",contained[i]);
	
	
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