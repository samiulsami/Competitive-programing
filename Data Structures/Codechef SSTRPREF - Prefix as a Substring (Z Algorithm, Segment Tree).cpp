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


const int N = 1e6+5;

vector<int> Z_Algo(string s){
	int n = (int)s.size();
	vector<int>Z(n);
	for(int i=1,l=0,r=0; i<n; i++){
		if(i<=r)Z[i]=min(r-i+1,Z[i-l]);
		while(i+Z[i]<n && s[Z[i]]==s[i+Z[i]])Z[i]++;
		if(i+Z[i]-1>r)l=i,r=i+Z[i]-1;
	}
	return Z;
}

struct segtree{
	#define T int
	T Tree[4*N];

	inline T Combine(T a, T b){
		return max(a,b);
	}

	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=val;
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}
	
	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
	
	#undef T
}segtree;

void solve(int casenum){
	string S1,S2,X;
	cin>>S1>>S2>>X;
	auto z1 = Z_Algo((S1+"$"+X));
	auto z2 = Z_Algo((S2+"$"+X));
	z2=vector<int>(z2.begin()+sz(S2)+1,z2.end());
	z1=vector<int>(z1.begin()+sz(S1)+1,z1.end());
	int a=sz(S1),b=sz(S2),c=sz(X);
	
	for(int i=0,x=4*c; i<=x; i++)segtree.Tree[i]=0;
	
	for(int i=0; i<c; i++){
		segtree.update(1,1,c,i+1,i+z2[i]);
	}
	ll ans=0;
	for(int i=0,r=0,r1; i<c; i++){
		if(z1[i]==0)ans+=z2[i];
		else if(i+z1[i]==c)ans+=c-i;
		else{
			r=i+z1[i]+1;
			ans+=segtree.query(1,1,c,i+1,r)-i;
		}
	}
	
	cout<<ans<<"\n";
	
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}