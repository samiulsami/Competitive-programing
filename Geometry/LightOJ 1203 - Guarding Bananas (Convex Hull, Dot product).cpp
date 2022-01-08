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

bool onSegment(pt &a, pt &b, pt &c){
	///Check if point c lies on the segment ab
	if(orientation(a,b,c)!=0)return 0;
	if(c.x>=min(a.x, b.x) && c.x<=max(a.x, b.x) && c.y>=min(a.y, b.y) && c.y<=max(a.y, b.y))return 1;
	return 0;
}

bool lineSegmentIntersection(pt &a, pt &b, pt &c, pt &d){
	///Check if segment ab intersects segment cd
	if(onSegment(a,b,c) || onSegment(a,b,d))return 1;
	else if(onSegment(c,d,a) || onSegment(c,d,b))return 1;
	else if(orientation(a,b,c)!=orientation(a,b,d) && orientation(c,d,a)!=orientation(c,d,b))return 1;
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

///Winding Number
int pointInsidePolygon(vector<pt> &points, pt &p){
	///1 = p lies inside polygon
	///0 = p lies outside polygon
	///-1 = p lies on the boundary
	int nn=(int)points.size(), cnt=0;
	for(int i=0; i<nn; i++)
		if(onSegment(points[i],points[(i+1)%nn],p))return -1;
	for(int i=0,j; i<nn; i++){
		j=(i+1)%nn;
		bool below = points[i].y<p.y;
		if(below!=(points[j].y<p.y)){
			int orient = orientation(p,points[i],points[j]);
			if(orient==0)return 0;
			if((below && orient==1) || (!below && orient==-1))cnt+=(below?1:-1);
		}
	}
	return (cnt?1:0);
}

///O(logn)
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


ull minEuclideanDistance(vector<pt> &points){///bicsi
	sort(points.begin(), points.end(), [&](auto &a, auto &b)->bool{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	});
	set<pair<ptType,ptType> >st;
	ull ans=ULLONG_MAX;
	for(int i=0,j=0; i<sz(points); i++){
		ull d = ceil(sqrt(ans));
		while((points[i].x - points[j].x)>=d){
			st.erase({points[j].y, points[j].x});
			j++;
		}
		auto it1 = st.lower_bound({points[i].y-d, points[i].x});
		auto it2 = st.upper_bound({points[i].y+d, points[i].x});
		for(auto it=it1 ;it!=it2; it++){
			ll x = points[i].y - it->first;
			ll y = points[i].x - it->second;
			ans = min(ans, (ull)(x*x)+(y*y));
		}
		st.insert({points[i].y, points[i].x});
	}
	return ans;
}


///Rotating Calipers
ll maxEuclideanDistance(vector<pt>&pts){
	///Points must be in clockwise order
	///Computes the maximum distance(squared) between any two points in a convex polygon in O(n);
	int n = (int)pts.size();
	if(n<=1)return 0;
	auto nxt = [&](int i)->int{return i+1>=n?0:i+1;};
	ll ret=0;
	for(int i=0,j=1; i<j; i++){
		for(;;j=nxt(j)){
			ret=max(ret,dist2(pts[i],pts[j]));
			if(orientation(pts[i],pts[nxt(i)],pts[j],pts[nxt(j)])>=0)break;
		}
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
const double K = double(180)/double(acos(-1.0));

ld mag(pt a){
	ll x = 1LL*a.x*a.x;
	ll b = 1LL*a.y*a.y;
	ld ret = sqrt(ld(x+b));
	return ret;
}

void solve(int casenum){
	int n;
	si(n);
	vector<pt>pts(n);
	FOR(i,n)sii(pts[i].x,pts[i].y);
	double ans=0;
	
	if(n>2){
		pts = convexHull(pts);
		ans=1e9;
		n=sz(pts);
		bool allCollinear=1;
		if(n<=2)ans=0;
		else{
			for(int i=0,a,b; i<n; i++){
				a=(i-1+n)%n;
				b=(i+1)%n;
				if(orientation(pts[a],pts[b],pts[i])!=0){
					allCollinear=0;
				}
				pt ia = pts[a]-pts[i];
				pt ib = pts[b]-pts[i];
				ld dot = ia*ib;
				ld magnitude = mag(ia)*mag(ib);
				ld angle = acos(dot/magnitude)*K;
				ans=min(ans,(double)abs(angle));
			}
		}
		if(allCollinear)ans=0;
	}
	pf("Case %d: %0.12f\n",casenum, ans);
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}