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


const int N = 4e5+5;
const int MOD = 1e9+7;

int bigmod(int a, int b){
	int ret=1;
	while(b){
		if(b&1)ret = (1LL*ret*a)%MOD;
		a = (1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

typedef pair<int,ll>pil;
pil Tree[4*N];
int LazyMUL[4*N];
ll LazyOR[4*N]={0};
int arr[N];
vector<int>primes;
vector<int>primeInv;

inline pil Merge(pil &a, pil &b){
	return pil((1LL*a.first*1LL*b.first)%MOD, a.second|b.second);
}

void build(int node, int l, int r){
	LazyMUL[node]=1;
	LazyOR[node]=0;
	if(l==r){
		Tree[node].first=arr[l-1];
		Tree[node].second=0;
		for(int i=0; i<sz(primes); i++){
			if(arr[l-1]%primes[i]==0){
				Tree[node].second|=(1LL<<i);
			}
		}
	}
	else{
		int mid = (l+r)>>1;
		build(node<<1, l, mid);
		build(node<<1|1, mid+1, r);
		Tree[node] = Merge(Tree[node<<1], Tree[node<<1|1]);
	}
}

inline void push_update(int node, int l, int r){
	if(LazyMUL[node]>1){
		Tree[node].first = (1LL*Tree[node].first * bigmod(LazyMUL[node], r-l+1))%MOD;
		if(l^r){
			LazyMUL[node<<1] = (1LL*LazyMUL[node<<1]*LazyMUL[node])%MOD;
			LazyMUL[node<<1|1] = (1LL*LazyMUL[node<<1|1]*LazyMUL[node])%MOD;
		}
		LazyMUL[node]=1;
	}
	if(LazyOR[node]){
		Tree[node].second |= LazyOR[node];
		if(l^r){
			LazyOR[node<<1] |= LazyOR[node];
			LazyOR[node<<1|1] |= LazyOR[node];
		}
		LazyOR[node]=0;
	}
}

void update(int node, int l, int r, int posl, int posr, int mul, ll orval){
	push_update(node,l,r);
	if(l>r || posr<l || posl>r)return;
	if(l>=posl && r<=posr){
		LazyMUL[node] = (1LL*LazyMUL[node]*mul)%MOD;
		LazyOR[node] |= orval;
		push_update(node,l,r);
	}
	else{
		int mid = (l+r)>>1;
		update(node<<1, l, mid, posl, posr, mul, orval);
		update(node<<1|1, mid+1, r, posl, posr, mul, orval);
		Tree[node] = Merge(Tree[node<<1], Tree[node<<1|1]);
	}
}

pil query(int node, int l, int r, int posl, int posr){
	push_update(node,l,r);
	if(l>=posl && r<=posr)return Tree[node];
	int mid = (l+r)>>1;
	if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr);
	if(posr<=mid)return query(node<<1, l, mid, posl, posr);
	pil L = query(node<<1, l, mid, posl, posr);
	pil R = query(node<<1|1, mid+1, r, posl, posr);
	return Merge(L,R);
}

char s[20];

void solve(int casenum){
	int n,q,l,r,x;
	sii(n,q);
	FOR(i,n)si(arr[i]);
	build(1,1,n);
	
	while(q--){
		sf(" %s%d%d",&s, &l, &r);
		//pf("%s %d %d\n",s,l,r);
		if(s[0]=='M'){
			si(x);
			ll orval=0;
			for(int i=0; i<sz(primes); i++){
				if(x%primes[i]==0)orval|=(1LL<<i);
			}
			update(1,1,n,l,r,x,orval);
		}
		else{
			pil Q = query(1,1,n,l,r);
			int product = Q.first;
			ll mask = Q.second;
			
			for(int i=0; i<sz(primes); i++){
				if(bool(mask&(1LL<<i))){
					product = (1LL*product *(primes[i]-1))%MOD;
					product = (1LL*product *primeInv[i])%MOD;
				}
			}
			
			pf("%d\n",product);
		}
		
	}
	
}

int main(){
	primes.push_back(2);
	primeInv.push_back(bigmod(2,MOD-2));
	for(int i=3; i<=300; i+=2){
		bool b=1;
		for(int j=2; j*j<=i; j++){
			if(i%j==0){
				b=0;
				break;
			}
		}
		if(b){
			primes.push_back(i);
			primeInv.push_back(bigmod(i,MOD-2));
		}
	}
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