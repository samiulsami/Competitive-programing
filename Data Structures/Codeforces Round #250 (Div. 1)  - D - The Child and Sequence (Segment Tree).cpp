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

typedef pair<int,ll>pil;
pil Tree[4*N];
int arr[N];

inline pil Merge(pil l, pil r){
	return pil(max(l.first, r.first), l.second+r.second);
}

void build(int node, int l, int r){
	if(l==r){
		Tree[node] = pil(arr[l],arr[l]);
	}
	else{
		int mid = (l+r)>>1;
		build(node<<1, l, mid);
		build(node<<1|1, mid+1, r);
		Tree[node] = Merge(Tree[node<<1], Tree[node<<1|1]);
	}
}

void update(int node, int l, int r, int pos, int x){///set
	if(l==pos && r==pos)Tree[node] = {x,x};
	else{
		int mid = (l+r)>>1;
		if(pos<=mid)update(node<<1,l,mid,pos,x);
		else update(node<<1|1, mid+1, r, pos, x);
		Tree[node] = Merge(Tree[node<<1], Tree[node<<1|1]);
	}
}

void updatemod(int node, int l, int r, int posl, int posr, int x){///MOD
	if(l>r || posl>r || posr<l || posl>posr || Tree[node].first<x)return;
	if(l==r){
		x=Tree[node].first%x;
		Tree[node] = {x,x};
	}
	else{
		int mid = (l+r)>>1;
		updatemod(node<<1,l,mid,posl,posr, x);
		updatemod(node<<1|1, mid+1, r, posl,posr, x);
		Tree[node] = Merge(Tree[node<<1], Tree[node<<1|1]);
	}
}

ll query(int node, int l, int r, int posl, int posr){
	if(l>=posl && r<=posr)return Tree[node].second;
	int mid = (l+r)>>1;
	if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr);
	if(posr<=mid)return query(node<<1, l, mid, posl, posr);
	return query(node<<1, l, mid, posl, posr) + query(node<<1|1, mid+1, r, posl, posr);
}

void solve(int casenum){
	 int n,m;
	 sii(n,m);
	FOR(i,n)si(arr[i+1]);
	build(1,1,n);
	
	int qt,l,r,x;
	while(m--){
		siii(qt,l,r);
		if(qt==1){
			pf("%lld\n",query(1,1,n,l,r));
		}
		else if(qt==2){
			si(x);
			updatemod(1,1,n,l,r,x);
		}
		else{
			update(1,1,n,l,r);
		}
	}
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