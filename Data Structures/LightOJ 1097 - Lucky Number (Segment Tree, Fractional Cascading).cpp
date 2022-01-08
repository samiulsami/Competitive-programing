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


const int N = 1429431+5;

int Tree[4*N];
int n = 1429431;

void build(int node, int l, int r){
	if(l==r)Tree[node]=(l&1)?1:0;
	else{
		int mid = (l+r)>>1;
		build(node<<1,l,mid);
		build(node<<1|1,mid+1,r);
		Tree[node]=Tree[node<<1]+Tree[node<<1|1];
	}
}

void update(int node, int l, int r, int pos){
	if(l==pos && r==pos)Tree[node]=0;
	else{
		int mid = (l+r)>>1;
		if(pos<=mid)update(node<<1,l,mid,pos);
		else update(node<<1|1,mid+1,r,pos);
		Tree[node]=Tree[node<<1]+Tree[node<<1|1];
	}
}

int kth(int node, int l, int r, int k){
	if(l==r)return l;
	int mid = (l+r)>>1;
	if(Tree[node<<1]>=k)return kth(node<<1,l,mid,k);
	return kth(node<<1|1,mid+1,r,k-Tree[node<<1]);
}

void solve(int casenum){
	int k;
	si(k);
	pf("Case %d: %d\n",casenum,kth(1,1,n,k));
	
}

int main(){
	build(1,1,n);
	for(int i=2,k; Tree[1]>=i; i++){
		k=kth(1,1,n,i);
		for(int j=k,l=0; j<=1429431; j+=k,l++)update(1,1,n,kth(1,1,n,j-l));

	}
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	///for(int i=1; i<=20; i++)pf("%d ",kth(1,1,n,i));
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}