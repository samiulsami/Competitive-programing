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
 
struct node{
	int x;
	bool status;
	int ind;
	node(int a, bool b, int c):x(a),status(b),ind(c){}
	node(){}
	bool operator<(const node &n)const{
		if(x==n.x)return status>n.status;
		return x<n.x;
	}
};
 
int ans[200005];
 
void solve(int casenum){
	int n;
	sf("%d",&n);
	
	vector<node>arr;
	arr.reserve(n+n);
	
	for(int i=0,l,r; i<n; i++){
		sf("%d%d",&l,&r);
		arr.emplace_back(l,0,i);
		arr.emplace_back(r+1,1,i);
	}
	sort(arr.begin(), arr.end());
	
	stack<int>st;
	int roomCount=0;
	for(auto &nd:arr){
		if(nd.status){
			st.push(ans[nd.ind]);
		}
		else{
			int roomID;
			if(st.empty()){
				roomID = ++roomCount;
			}
			else{
				roomID = st.top();
				st.pop();
			}
			ans[nd.ind]=roomID;
		}
	}
	
	pf("%d\n",roomCount);
	for(int i=0; i<n; i++)pf("%d ",ans[i]);
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