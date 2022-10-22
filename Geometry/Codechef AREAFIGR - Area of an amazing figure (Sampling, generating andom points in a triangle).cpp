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
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

#define ptType double
#define ptType2 double

struct pt{
	ptType x,y;
	pt(){}
	pt(ptType a, ptType b){x=a;y=b;}
	pt operator-(const pt p)const{return pt(x-p.x, y-p.y);}
	pt operator+(const pt p)const{return pt(x+p.x, y+p.y);}
	pt operator/(const ptType d)const{return pt(x/d,y/d);}
	pt operator*(const ptType d)const{return pt(x*d,y*d);}
	ptType2 operator*(const pt p)const{return ptType2(1)*x*p.x + ptType2(1)*y*p.y;}///dot
	ptType2 operator^(const pt p)const{return ptType2(1)*x*p.y - ptType2(1)*y*p.x;}///cross
	bool operator==(const pt p)const{return x==p.x && y==p.y;}
	bool operator<(const pt p)const{return p.x==x?y<p.y:x<p.x;}
	void input(){
		cin>>x>>y;
	}
		
};

struct line{
	double a,b,c;
	pt x,y;
	line(){}
	line(double a, double b, double c):a(a),b(b),c(c){}
	line(pt x, pt y){
		this->x=x;
		this->y=y;
		a=x.y-y.y;
		b=y.x-x.x;
		c=1LL*x.x*y.y-1LL*x.y*y.x;
	}
	
	double distanceToPoint(pt p){
		return abs(a*p.x + b*p.y + c)/sqrt(a*a+b*b);
	}
};

///Assuming line A intersects line B and they're not parallel, returns their point of intersection
pair<double,double> intersection(line A, line B){
	double D = A.a*B.b - B.a*A.b;
	pair<double,double>ret;
	ret.first = (A.b*B.c - B.b*A.c)/D;
	ret.second = (B.a*A.c - A.a*B.c)/D;
	return ret;
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

double dist2(pt &a, pt &b){
	double x=a.x-b.x, y=a.y-b.y;
	return (x*x)+(y*y);
}

double dist(pt &a, pt &b){
	return sqrt(double(dist2(a,b)));
}

int pointInTriangle(pt &a, pt &b, pt &c, pt &p){
	/// 0 = Boundary
	/// 1 = Inside
	/// -1 0 Outside
	if(onSegment(a,b,p) || onSegment(b,c,p) || onSegment(a,c,p))return 1;
	int x=orientation(a,b,p),y=orientation(b,c,p),z=orientation(c,a,p);
	if(x==y && y==z)return 1;
	return -1;
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



#undef ptType
#undef ptType2
const double eps=1e-7;

struct Circle{
	double r;
	pt c;
	Circle(){}
	Circle(double r, pt c):r(r),c(c){}
	bool inside(pt x){
		return r-dist(c,x)>eps;
	}
};
Circle circles[3];
pt A,B,C;

void solve(int casenum){
	double a,r1,r2,r3;
	cin>>a>>r1>>r2>>r3;
	Circle cx,cy,cz;

	A=pt(-a,0);
	B=pt(a,0);
	C=pt(0,double(sqrt(3.0))*a);
	
	cx.r=r1;
	cx.c=(A+B)/double(2);
	cy.r=r2;
	cy.c=(B+C)/double(2);
	cz.r=r3;
	cz.c=(A+C)/double(2);
	circles[0]=cx;
	circles[1]=cy;
	circles[2]=cz;
	
	//pt tl(-MAXDIST,MAXDIST), tr(MAXDIST,MAXDIST), bl(-MAXDIST,-MAXDIST), br(MAXDIST,-MAXDIST);
	double TArea=a*C.y;
	double inTriangle=0;
	double inCircle=0;
	double pr1,pr2;
	
	for(int i=0; i<2500000; i++){
		inTriangle++;
		pr1=double(rand(0,10000000))/10000000.0;
		pr2=double(rand(0,10000000))/10000000.0;
		double sqr1=sqrt(pr1);
		pt p = A*(1.0-sqr1) + B*(sqr1*(1.0-pr2)) + C*(pr2*sqr1);
		bool b=1;
		for(int j=0; j<3; j++){
			if(!circles[j].inside(p)){
				b=0;
				break;
			}
		}
		if(b)inCircle++;
	}
	
	double ans=(TArea*inCircle)/inTriangle;
	pf("%0.8f\n",ans);
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