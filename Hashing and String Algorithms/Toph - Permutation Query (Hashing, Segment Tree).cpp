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
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
//inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 2e5+5;

typedef unsigned short tmpType;
tmpType h[N];
tmpType hXor[N];
tmpType hSum[N];
int arr[N];

#define T pair<tmpType,tmpType>

inline T Combine(T &a, T &b){
	return {a.first^b.first, a.second+b.second};
}

int n;
T Tree[2*N];

void update(int ind, int val){
    ind+=n-1;
    Tree[ind]={h[val],h[val]};
    for(;ind>1; ind>>=1)Tree[ind>>1] = Combine(Tree[ind],Tree[ind^1]);
}

T query(int l, int r){ ///[l,r]
    l+=n-1;
    r+=n;
    T ret(0,0);
    for(;l<r; l>>=1,r>>=1){
        if(l&1)ret=Combine(ret,Tree[l++]);
        if(r&1)ret=Combine(ret,Tree[--r]);
    }
    return ret;
}

#undef T

void solve(int casenum){
	int q,qt,l,r,x;
	sii(n,q);
	hXor[0]=0;
	hSum[0]=0;
	for(int i=0,len=n+n; i<=len; i++)Tree[i]={0,0};
	for(int i=1; i<=n; i++){
		si(arr[i]);
		h[i]=rng();
		hSum[i] = hSum[i-1]+h[i];
		hXor[i] = h[i]^hXor[i-1];
	}
	for(int i=1; i<=n; i++)update(i,arr[i]);
	
	while(q--){
		siii(qt,l,r);
		if(qt==1){
			auto val = query(l,r);
			l=(r-l+1);
			if(val.first==hXor[l] && val.second==hSum[l])pf("YES\n");
			else pf("NO\n");
		}
		else{
			update(l,r);
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