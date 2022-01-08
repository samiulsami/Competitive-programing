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

ll Tree[4*N];
ll mx[4*N];
ll arr[N];

void build(int node, int l, int r){
	if(l==r){
		Tree[node]=arr[l];
		mx[node]=arr[l];
	}
	else{
		int mid = (l+r)>>1;
		build(node<<1,l,mid);
		build(node<<1|1, mid+1,r);
		Tree[node] = Tree[node<<1] + Tree[node<<1|1];
		mx[node] = max(mx[node<<1], mx[node<<1|1]);
	}
}

void update(int node, int l, int r, int posl, int posr){
	if(l>r || l>posr || posl>r || mx[node]==1)return;
	if(l==r){
		Tree[node] = sqrt(Tree[node]);
		mx[node] = Tree[node];
	}
	else{
		int mid = (l+r)>>1;
		update(node<<1, l, mid, posl, posr);
		update(node<<1|1, mid+1, r, posl, posr);
		Tree[node] = Tree[node<<1] + Tree[node<<1|1];
		mx[node] = max(mx[node<<1], mx[node<<1|1]);
	}
}

ll query(int node, int l, int r, int posl, int posr){
	if(l>r || posl>r || posr<l)return 0;
	if(l>=posl && r<=posr)return Tree[node];
	int mid = (l+r)>>1;
	return query(node<<1, l, mid, posl, posr) + query(node<<1|1, mid+1, r, posl, posr);
}

void solve(int casenum){
	casenum=1;
	int n,m,qt,l,r;
	while(sf("%d",&n)!=EOF){
		for(int i=1; i<=n; i++)sl(arr[i]);
		build(1,1,n);
		si(m);
		pf("Case #%d:\n", casenum);
		casenum++;
		
		while(m--){
			siii(qt,l,r);
			if(l>r)swap(l,r);
			if(qt==0)update(1,1,n,l,r);
			else pf("%lld\n",query(1,1,n,l,r));
		}
		nl;
	}
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    // for(int i=1; i<=T; i++)
        // solve(i);
	solve(0);
return 0;
}