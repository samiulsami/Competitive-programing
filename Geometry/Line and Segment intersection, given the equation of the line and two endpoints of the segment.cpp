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

#define ptType ll
#define ptType2 ll

struct pt{
	ptType x,y;
	pt(){}
	pt(ptType a, ptType b){x=a;y=b;}
	pt operator-(const pt p)const{return pt(x-p.x, y-p.y);}
	pt operator+(const pt p)const{return pt(x+p.x, y+p.y);}
	ptType2 operator*(const pt p)const{return ptType2(1)*x*p.x + ptType2(1)*y*p.y;}///dot
	ptType2 operator^(const pt p)const{return ptType2(1)*x*p.y - ptType2(1)*y*p.x;}///cross
	bool operator==(const pt p)const{return x==p.x && y==p.y;}
	bool operator<(const pt p)const{return p.x==x?y<p.y:x<p.x;}
};

struct line{
	ll a,b,c;
	pt x,y;
	line(){}
	line(ll a, ll b, ll c):a(a),b(b),c(c){}
	line(pt x, pt y){
		this->x=x;
		this->y=y;
		a=x.y-y.y;
		b=y.x-x.x;
		c=1LL*x.x*y.y-1LL*x.y*y.x;
	}

};

///Assuming line A intersects line B and they're not parallel, returns their point of intersection
bool intersection(line A, line B, pair<ll,ll>&ret, ll &D){
	D = A.a*B.b - B.a*A.b;
	if(D==0)return 0;
	ret.first = (A.b*B.c - B.b*A.c);
	ret.second = (B.a*A.c - A.a*B.c);
	return 1;
}

int orientation(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType2 tmp = (b-a)^(c-a);
	if(tmp>0)return 1;
	if(tmp<0)return -1;
	return 0;
}

///Pick's Theorem: S = I + (B/2) - 1
/// S = Area, I = lattice points inside polygon, B = lattice points on the boundary of the polygon
/// Number of lattice points between point A and B = __gcd(abs(A.x-B.x), abs(A.y-B.y))
#undef ptType
#undef ptType2

void solve(int casenum){
	ll a,b,c,d,e,f;
	sll(a,b);
	sll(c,d);
	pt x(a,b);
	pt y(c,d);
	slll(a,b,c);
	line l(a,b,c);
	line m(x,y);
	
	pair<ll,ll>tmp;
	ll D;
	if(!intersection(l,m,tmp,D))pf("YES\n");
	else{
		pt ret(tmp.first,tmp.second);
		if(ret.x>=min(D*x.x,D*y.x) && ret.x<=max(D*x.x,D*y.x) && ret.y>=min(D*x.y,D*y.y) && ret.y<=max(D*x.y,D*y.y))pf("NO\n");
		else pf("YES\n");
	}
	
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
      freopen("position.in","r",stdin);
      freopen("position.out","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}