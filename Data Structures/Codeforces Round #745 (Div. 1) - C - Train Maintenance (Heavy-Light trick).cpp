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


const int N = 2e5+5;
const int K = 500;

int arr[N][2];
int diff[N]={0};
int light[K+1][K+1]={0};
int dayAdded[N];
int n,m;

void addBig(int day, int k, int val, int &ans){
	for(int i=dayAdded[k]; i+arr[k][0]<=m; i+=arr[k][0]+arr[k][1]){
		diff[i+arr[k][0]]+=val;
		if(i+arr[k][1]+arr[k][0] <= m) diff[i+arr[k][1]+arr[k][0]]-=val;
		if(i+arr[k][0]<=day && i+arr[k][1]+arr[k][0]-1>=day)ans+=val;
	}
}


void solve(int casenum){
	sii(n,m);
	for(int i=1; i<=n; i++)sii(arr[i][0],arr[i][1]);
	
	for(int day=1,op,k,ans=0; day<=m; day++){
		sii(op,k);
		ans+=diff[day];
		if(op==1)dayAdded[k]=day;
		
		if(arr[k][0]+arr[k][1]>K){
			addBig(day, k, op==1?1:-1, ans);
		}
		else {
			int x = arr[k][0]+arr[k][1];
			int tmpDay=dayAdded[k];
			
			for(int i=1; i<=arr[k][1]; i++){
				light[x][(i+arr[k][0]+tmpDay-1)%x]+=(op==1?1:-1);
			}
		}
		
		int tmp=ans;
		for(int i=1; i<=K; i++){
			tmp+=light[i][day%i];
		}
		
		pf("%d\n",tmp);
	}
	
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