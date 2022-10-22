#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

struct minQueue{
	struct node{
		ll val,mn,mx;
	};
	stack<node>A,B;
	minQueue(){}
	
	void push(ll a){
		if(A.empty()){
			A.push({a,a,a});
		}
		else A.push({a,min(a,A.top().mn), max(a,A.top().mx)});
	}
	
	void pop(){
		if(B.empty()){
			while(!A.empty()){
				if(B.empty())B.push({A.top().val, A.top().val, A.top().val});
				else B.push({A.top().val, min(A.top().val, B.top().mn), max(A.top().val, B.top().mx)});
				A.pop();
			}
		}
		B.pop();
	}
	
	ll get(){
		node x;
		if(B.empty())x=A.top();
		else if(A.empty())x=B.top();
		else {
			x = {1,min(A.top().mn,B.top().mn), max(A.top().mx, B.top().mx)};
		}
		return x.mx - x.mn;
	}
};

void solve(int casenum){
	int n;
	ll k;
	minQueue Q;
	sf("%d %lld",&n,&k);
	vector<ll>a(n);
	FOR(i,n)sl(a[i]);
	
	int l=-1;
	ll ans=0;
	for(int i=0; i<n; i++){
		Q.push(a[i]);
		while(l<i && Q.get()>k){
			Q.pop(),l++;
			//dbug(Q.get());
		}
		ans+=i-l;
		//pf("%d %d\n",l+1,i);
	}
	
	pf("%lld\n",ans);
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}