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
struct pt{ptType x,y;};

inline ll crossproduct(pt &a, pt &b, pt &c){
	return 1LL*(b.x-a.x)*(c.y-a.y) - 1LL*(b.y-a.y)*(c.x-a.x);
}

int orientation(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ll tmp = crossproduct(a,b,c);
	if(tmp>0)return 1;
	if(tmp<0)return -1;
	return 0;
}


bool onSegment(pt &a, pt &b, pt &c){
	///Check if point c lies on the segment ab
	if(orientation(a,b,c)!=0)return 0;
	if(c.x>=min(a.x, b.x) && c.x<=max(a.x, b.x) && c.y>=min(a.y, b.y) && c.y<=max(a.y, b.y))return 1;
	return 0;
}

int pointInConvexPolygon(vector<pt> &pts, pt p){///YouKn0wWho
	///Points must be in clockwise order
	///1 = inside
	///0 = boundary
	///-1 = outside
	if((int)pts.size()==2)return onSegment(pts[0],pts[1],p)?0:-1;
	int low=1,high=int(pts.size())-1,mid;
	int a=orientation(pts[0],pts[1],p), b=orientation(pts[0],pts.back(),p);
	if(a==1 || b==-1)return -1;
	while(low+1<high){
		mid=(low+high)>>1;
		if(orientation(pts[0],pts[mid],p)<=0)low=mid;
		else high=mid;
	}
	int orient = orientation(pts[low],pts[high],p);
	if(orient==0)return 0;
	if(orient==1)return -1;
	if(low==1 && a==0)return 0;
	if(high==int(pts.size())-1 && b==0)return 0;
	return 1;
}


vector<pt> convexHull(vector<pt> &pts){
	sort(pts.begin(),pts.end(),[&](pt &a, pt &b)->bool{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	});
	vector<pt>ret;
	ret.reserve(sz(pts)+1);
	auto work = [&](int n, int i)->bool{
		if(sz(ret)-n<2)return 0;
		if(orientation(ret[sz(ret)-2],ret.back(),pts[i])<=0)return 1;
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
	reverse(all(ret));
	return ret;
}
///Pick's Theorem: S = I + (B/2) - 1
/// S = Area, I = lattice points inside polygon, B = lattice points on the boundary of the polygon
/// Number of lattice points between point A and B = __gcd(abs(A.x-B.x), abs(A.y-B.y))
#undef ptType

void solve(int casenum){
	int n;
	si(n);
	vector<pt>a(n),b(n);
	FOR(i,n)sii(a[i].x,a[i].y);
	FOR(i,n)sii(b[i].x,b[i].y);
	auto hullA=convexHull(a);
	auto hullB=convexHull(b);
	
	int ansA=0,ansB=0;
	for(pt &x:b){
		if(pointInConvexPolygon(hullA,x)>=0)ansA++;
	}
	for(pt &x:a){
		if(pointInConvexPolygon(hullB,x)>=0)ansB++;
	}
	
	pf("%d %d\n",ansA,ansB);
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    freopen("curling.in","r",stdin);
    freopen("curling.out","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}