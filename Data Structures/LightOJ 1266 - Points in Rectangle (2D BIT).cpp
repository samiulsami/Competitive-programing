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


const int N = 1001;

int BIT[N+1][N+1];

int query(int x, int y){
	int ret=0;
	for(int i=x; i>0; i -= i&-i)
		for(int j=y; j>0; j -= j&-j)
			ret+=BIT[i][j];
	return ret;
}

void update(int x, int y, int val){
	for(int i=x; i<=N; i += i&-i)
		for(int j=y; j<=N; j += j&-j)
			BIT[i][j]+=val;
}

int getAns(int x1, int y1, int x2, int y2){///Number of points in the rectangle (x1,y1), (x2,y2) (assuming (x2,y2)>(x1,x1))
	return query(x2,y2) + query(x1-1,y1-1) - query(x2,y1-1) - query(x1-1,y2);
}


bool arr[N+1][N+1];

void solve(int casenum){
	int q,qt,x1,y1,x2,y2;
	si(q);
	memset(arr,0,sizeof(arr));
	memset(BIT,0,sizeof(BIT));
	pf("Case %d:\n",casenum);
	while(q--){
		si(qt);
		if(qt==0){
			sii(x1,y1);
			x1++;
			y1++;
			if(!arr[x1][y1]){
				update(x1,y1,1);
				arr[x1][y1]=1;
			}
		}
		else {
			sf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1++,x2++;
			y1++,y2++;
			pf("%d\n",getAns(x1,y1,x2,y2));
		}
	}
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