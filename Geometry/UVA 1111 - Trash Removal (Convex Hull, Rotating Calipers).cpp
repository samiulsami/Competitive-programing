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


#define ptType int
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

int orientation(pt &a, pt &b, pt &c, pt &d){
	///Check if vector ab lies anti-clockwise to vector cd
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType2 tmp = (b-a)^(d-c);
	if(tmp>0)return 1;
	if(tmp<0)return -1;
	return 0;
}


ll dist2(pt &a, pt &b){
	ll x=a.x-b.x, y=a.y-b.y;
	return (x*x)+(y*y);
}

double linePointDistance(pt a, pt b, pt c, bool isSegment=0){///Topcoder
	if(isSegment){
		ptType dot = (b-a)*(c-b);
		if(dot>0)return sqrt(double(dist2(b,c)));
		ptType dot2 = (a-b)*(c-a);
		if(dot2>0)return sqrt(double(dist2(a,c)));
	}
	return abs(double((b-a)^(c-a))/sqrt(double(dist2(a,b))));
}


double get(vector<pt>&pts){

	int n = (int)pts.size();
	if(n<=1)return 0;
	auto nxt = [&](int i)->int{return i+1>=n?0:i+1;};
	double ret=1e10;
	for(int i=0; i<n; i++){
		double tmp=0;
		for(int j=nxt(i); j!=i; j=nxt(j)){
			tmp=max(tmp,linePointDistance(pts[i],pts[nxt(i)],pts[j]));
			if(orientation(pts[i],pts[nxt(i)],pts[j],pts[nxt(j)])>=0)break;
		}
		ret=min(ret,tmp);
	}
	return ret;
}

///Monotone Chain Algorithm
///Returns the convex hull in clockwise order
vector<pt> convexHull(vector<pt> &pts){
	sort(pts.begin(),pts.end(),[&](pt &a, pt &b)->bool{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	});
	vector<pt>ret;
	ret.reserve(sz(pts)+1);
	auto work = [&](int n, int i)->bool{
		if(sz(ret)-n<2)return 0;
		if(orientation(ret[sz(ret)-2],ret.back(),pts[i])>=0)return 1;
		return 0;
	};
	for(int i=0; i<sz(pts); i++){
		while(work(0,i))ret.pop_back();
		ret.push_back(pts[i]);
	}
	ret.pop_back();
	for(int i=sz(pts)-1,x=sz(ret); i>=0; i--){
		while(work(x,i))ret.pop_back();
		ret.push_back(pts[i]);
	}
	ret.pop_back();
	if(sz(ret)==2 && ret[0].x==ret[1].x && ret[0].y==ret[1].y)ret.pop_back();
	return ret;
}

///Pick's Theorem: S = I + (B/2) - 1
/// S = Area, I = lattice points inside polygon, B = lattice points on the boundary of the polygon
/// Number of lattice points between point A and B = __gcd(abs(A.x-B.x), abs(A.y-B.y))
#undef ptType
#undef ptType2

void solve(int casenum){
	int n;
	si(n);
	if(n==0)exit(0);
	vector<pt>pts(n);
	FOR(i,n)sii(pts[i].x,pts[i].y);
	auto hull = convexHull(pts);
	pf("Case %d: %0.2f\n",casenum, get(hull));
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; ;i++)
        solve(i);

return 0;
}