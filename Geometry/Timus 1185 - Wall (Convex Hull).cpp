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

inline ptType crossproduct(pt &a, pt &b, pt &c){
	return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

int isleft(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType tmp = crossproduct(a,b,c);
	if(tmp>0)return 1;
	if(tmp<0)return -1;
	return 0;
}

bool onSegment(pt &a, pt &b, pt &c){
	///Check if point c lies on the segment ab
	if(isleft(a,b,c)!=0)return 0;
	if(c.x>=min(a.x, b.x) && c.x<=max(a.x, b.x) && c.y>=min(a.y, b.y) && c.y<=max(a.y, b.y))return 1;
	return 0;
}

bool lineSegmentIntersection(pt &a, pt &b, pt &c, pt &d){
	///Check if segment ab intersects segment cd
	if(onSegment(a,b,c) || onSegment(a,b,d))return 1;
	else if(onSegment(c,d,a) || onSegment(c,d,b))return 1;
	else if(isleft(a,b,c)!=isleft(a,b,d) && isleft(c,d,a)!=isleft(c,d,b))return 1;
	return 0;
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
			int orientation = isleft(p,points[i],points[j]);
			if(orientation==0)return 0;
			if((below && orientation==1) || (!below && orientation==-1))cnt+=(below?1:-1);
		}
	}
	return (cnt?1:0);
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
		while((points[i].x - points[j].x)>=ans){
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

///Monotone Chain
vector<pt> convexHull(vector<pt> &pts){
	sort(pts.begin(),pts.end(),[&](pt &a, pt &b)->bool{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	});
	vector<pt>ret;
	ret.reserve(sz(pts)+1);
	auto work = [&](int n, int i)->bool{
		if(sz(ret)-n<2)return 0;
		if(isleft(ret[sz(ret)-2],ret.back(),pts[i])==-1)return 1;
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
/// S = Area, I = lattice points inside polygon, B = lattice points outside polygon
#undef ptType

void solve(int casenum){
	int n,L;
	sii(n,L);
	vector<pt>pts(n);
	FOR(i,n)sii(pts[i].x,pts[i].y);
	auto hull = convexHull(pts);
	
	double perimeter=0;
	auto dist = [&](pt &a, pt &b)->double{
		double aa=a.x-b.x;
		double bb=a.y-b.y;
		return sqrt((aa*aa)+(bb*bb));
	};
	
	for(int i=0; i<sz(hull); i++){
		perimeter+=dist(hull[i],hull[(i+1)%n]);
	}
	
	double PI = acos(-1.0);
	perimeter+=(double(2)*PI*double(L));
	pf("%0.0f\n",(perimeter));
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