#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
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
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 2e5+5;

struct data{
	int first,last;
	int preflen,sufflen,len;
	ll total;
	data(){}
	data(int a, int b, int c, int d, int e, ll f){
		first=a;
		last=b;
		preflen=c;
		sufflen=d;
		len=e;
		total=f;
	}
}Tree[4*N];
int arr[N];
int n;

inline data Merge(data L, data R){
	data ret(L.first,R.last,0,0,L.len+R.len,L.total+R.total);
	ret.preflen=L.preflen;
	ret.sufflen=R.sufflen;
	if(L.last<=R.first){
		ret.total+=1LL*L.sufflen*R.preflen;
		if(R.sufflen==R.len)ret.sufflen=R.len+L.sufflen;
		if(L.preflen==L.len)ret.preflen=L.len+R.preflen;
	}
	return ret;
}

void build(int node, int l, int r){
	if(l==r)Tree[node]=data(arr[l],arr[l],1,1,1,1);
	else{
		int mid = (l+r)>>1;
		build(node<<1,l,mid);
		build(node<<1|1,mid+1,r);
		Tree[node] = Merge(Tree[node<<1],Tree[node<<1|1]);
	}
}

void update(int node, int l, int r, int pos, int val){
	if(l==pos && r==pos)Tree[node]=data(val,val,1,1,1,1);
	else{
		int mid = (l+r)>>1;
		if(pos<=mid)update(node<<1,l,mid,pos,val);
		else update(node<<1|1,mid+1,r,pos,val);
		Tree[node]=Merge(Tree[node<<1],Tree[node<<1|1]);
	}
}

data query(int node, int l, int r, int posl, int posr){
	if(l>=posl && r<=posr)return Tree[node];
	int mid = (l+r)>>1;
	if(posr<=mid)return query(node<<1,l,mid,posl,posr);
	if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
	return Merge(query(node<<1,l,mid,posl,posr), query(node<<1|1,mid+1,r,posl,posr));
}

ll get(int l, int r){return query(1,1,n,l,r).total;}

void solve(int casenum){
	int q;
	sii(n,q);
	for(int i=1; i<=n; i++)si(arr[i]);
	build(1,1,n);
	
	int l,r,qt;
	while(q--){
		siii(qt,l,r);
		if(qt==1){
			update(1,1,n,l,r);
		}
		else{
			pf("%lld\n",get(l,r));
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