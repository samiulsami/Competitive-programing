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
struct pt{
	ptType x,y;
	pt(){}
	pt(ptType a, ptType b){x=a;y=b;}
	pt operator-(const pt p)const{return pt(x-p.x, y-p.y);}
	pt operator+(const pt p)const{return pt(x+p.x, y+p.y);}
	ptType operator*(const pt p)const{return x*p.x + y*p.y;}///dot
	ptType operator^(const pt p)const{return x*p.y - y*p.x;}///cross
	bool operator==(const pt p)const{return x==p.x && y==p.y;}
};

ll dist2(pt &a, pt &b){
	ll x=a.x-b.x, y=a.y-b.y;
	return (x*x)+(y*y);
}

double linePointDistance(pt a, pt b, pt c, bool isSegment=0){
	if(isSegment){
		ptType dot = (b-a)*(c-b);
		if(dot>0)return sqrt(double(dist2(b,c)));
		ptType dot2 = (a-b)*(c-a);
		if(dot2>0)return sqrt(double(dist2(a,c)));
	}
	return abs(double((b-a)^(c-a))/sqrt(double(dist2(a,b))));
}


#undef ptType


void solve(int casenum){
	int n,m;
	si(n);
	vector<pt>r(n);
	FOR(i,n)sll(r[i].x,r[i].y);
	si(m);
	vector<pt>s(m);
	FOR(i,m)sll(s[i].x,s[i].y);
	
	double ans=1e10;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			double cur=linePointDistance(s[j],s[(j+1)%m],r[i],1);
			ans=min(ans,cur);
			//pf("(%2lld,%2lld) - (%2lld,%2lld), (%2lld,%2lld) = %0.8f\n",s[j].x,s[j].y,s[(j+1)%m].x, s[(j+1)%m].y ,r[i].x, r[i].y ,cur);
			ans=min(ans,linePointDistance(r[i],r[(i+1)%n],s[j],1));
			
		}
	}
	
	ans/=double(2);
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