#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define nl printf("\n");
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
#define si(x) scanf("%d",&x);
#define sii(x,y) scanf("%d%d",&x,&y);
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z);
#define sl(x) scanf("%lld",&x);
#define sll(x,y) scanf("%lld%lld",&x,&y);
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define FOR(i,j,n) for(int i=j; i<=n; i++)
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;

ll arr[N];

void solve(int casenum){
	int n,q;
	sii(n,q);
	for(int i=0; i<=n; i++)arr[i]=-1;
	
	int l,r;
	bool possible=1;
	set<pii>ranges;
	
	while(q--){
		sii(l,r);
		if(r-l+1>64)possible=0;
		else ranges.insert({l,r});
	}
	
	if(possible){
		int _prev=1;
		set<int>st;
		for(int i=0; i<64; i++)st.insert(i);
		int maxR=1;
		
		for(pii p:ranges){
			l=p[0];
			r=p[1];
			while(_prev<l){
				if(arr[_prev]!=-1)st.insert(arr[_prev]);
				_prev++;
			}
			
			maxR = max(l,maxR);
			while(maxR<=r){
				arr[maxR++] = *st.begin();
				st.erase(*st.begin());
			}			
		
		}
	}
	pf("Case %d:\n",casenum);
	if(!possible){
		pf("Impossible\n");
	}
	else {
		for(int i=1; i<=n; i++){
			unsigned long long x;
			if(arr[i]==-1)x=1;
			else x = (1uLL<<(unsigned long long)arr[i]);
			pf("%llu",x);
			if(i!=n)pf(" ");
		}
		nl;
	}
	
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