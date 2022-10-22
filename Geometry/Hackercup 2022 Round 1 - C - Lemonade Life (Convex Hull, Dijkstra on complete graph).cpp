#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

typedef int ptType;
typedef ll ptType2;
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const double PI = acos(-1.0);
const double eps = 1e-9;

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
	void rotateccw(double a){
		///Rotate anti-clockwise about origin
		double s = sin(a);double c = cos(a);
		double newx = x*c - y*s;
		double newy = x*s + y*c;
		x=newx;
		y=newy;
	}
	void rotatecw(double a){rotateccw(PI-a);}
	void rotateccw(double a, pt p){
		///Rotate anti-clockwise about p
		x-=p.x;y-=p.y;
		rotateccw(a);
		x+=p.x;y+=p.y;
	}
	void rotatecw(double a, pt p){rotateccw(PI-a,p);}
	void in(){cin>>x>>y;}	
};

inline double toRad(double deg){return (deg*PI)/180.0;}
inline double toDeg(double rad){return (rad*180.0)/PI;}

int orientation(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType2 tmp = (b-a)^(c-a);
	if(tmp==0)return 0;
	if(tmp>0)return 1;
	return -1;
}

ptType2 dist2(pt &a, pt &b){
	ptType2 x=a.x-b.x, y=a.y-b.y;
	return (x*x)+(y*y);
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

inline void solve(int caseNum){
	ll n,k,d;
	cin>>n>>k>>d;
	vector<pt>pts(n);
	for(int i=0; i<n; i++)pts[i].in();
	auto ch = convexHull(pts);
	sort(all(ch));

	vector<ll>dist(n,LLONG_MAX);
	dist[0]=0;
	vector<int>vis(n,0);

	for(int i=0; i<sz(ch); i++){
		int id=-1;
		for(int j=0; j<sz(ch); j++){
			if(dist[j]==LLONG_MAX || vis[j])continue;
			if(id==-1 || dist[j]<dist[id])id=j;
		}

		if(id==-1)break;
		vis[id]=1;

		for(int j=0; j<sz(ch); j++){
			if(vis[j])continue;
			if(dist2(ch[id], ch[j])>d*d)continue;
			dist[j] = min(dist[j], dist[id] + max(k, dist2(ch[id], ch[j])));
		}
	}


	ll ans = dist[sz(ch)-1];
	if(ans==LLONG_MAX)ans=-1;
	cout<<"Case #"<<caseNum<<": "<<ans<<"\n";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output2.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}