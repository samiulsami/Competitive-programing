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
#undef ptType

pt pts[701];

void solve(int casenum){
	int n;
	si(n);
	FOR(i,n)sii(pts[i].x,pts[i].y);
	
	int ans=0;

	for(int i=0,x,y,G; i<n; i++){
		map<pii,int>mp;
		pii xx;
		for(int j=i+1; j<n; j++){
			x = pts[j].x-pts[i].x;
			y = pts[j].y-pts[i].y;
			G=__gcd(x,y);
			if(x==0){
				xx=pii(1e9,1e9);
			}
			else{
				x/=G;
				y/=G;
				xx=pii(x,y);
			}
			mp[xx]++;
			ans=max(ans,mp[xx]);
		}
	}
	pf("Case %d: %d\n",casenum,min(n,ans+1));
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