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
};

///Assuming line A intersect B and they're not parallel, returns their point of intersection
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

ll dist2(pt &a, pt &b){
	ll x=a.x-b.x, y=a.y-b.y;
	return (x*x)+(y*y);
}

double dist(pt &a, pt &b){
	return sqrt(double(dist2(a,b)));
}


#undef ptType
#undef ptType2


void solve(int casenum){
	int n;
	si(n);
	pt a;
	si(a.x);
	a.y=0;
	double ans=0;
	pt cur,prev;
	sii(prev.x,prev.y);
	line l(a,prev);
	
	for(int i=1; i<n; i++){
		sii(cur.x,cur.y);
		if(orientation(a,l.y,cur)>0){
			//pf("here, %d %d\n",cur.x,cur.y);
			line m(cur,prev);
			auto inter=intersection(l,m);
			double aa=inter.first-double(cur.x);
			double bb=inter.second-double(cur.y);
			double val = sqrt(aa*aa+bb*bb);
			//pf("intersect: %0.2f %0.2f\n",inter.first,inter.second);
			//dbug(val);
			ans+=val;
			l=line(a,cur);
		}
		prev=cur;
	}

	pf("Case %d: %0.8f\n",casenum,ans);
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