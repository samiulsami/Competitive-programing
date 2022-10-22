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

int pointInConvexPolygon(vector<pt> &pts, pt p){///YouKn0wWho
	///Points must be in clockwise order
	///1 = inside
	///0 = boundary
	///-1 = outside
	int low=1,high=int(pts.size())-1,mid;
	int a=isleft(pts[0],pts[1],p), b=isleft(pts[0],pts.back(),p);
	if(a==1 || b==-1)return -1;
	while(low+1<high){
		mid=(low+high)>>1;
		if(isleft(pts[0],pts[mid],p)<=0)low=mid;
		else high=mid;
	}
	int orient = isleft(pts[low],pts[high],p);
	if(orient==0)return 0;
	if(orient==1)return -1;
	if(low==1 && a==0)return 0;
	if(high=int(pts.size()-1 && b==0))return 0;
	return 1;
}



#undef ptType


void solve(int casenum){
	int n,m;
	si(n);
	vector<pt>pts(n);
	FOR(i,n)sll(pts[i].x,pts[i].y);
	bool flag=1;
	
	si(m);
	int x,y;
	while(m--){
		sii(x,y);
		if(pointInConvexPolygon(pts,(pt){x,y})!=1)flag=0;
	}
	if(!flag)pf("NO\n");
	else pf("YES\n");
	
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