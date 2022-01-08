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
const int K = 320;

int arr[N];
int nxt[N];
int cnt[N];
int n;

void updateBlock(int i){
	int st = i*K;
	int ed = min(st+K,n)-1;
	for(int j=ed; j>=st; j--){
		nxt[j] = arr[j]+j;
		if(nxt[j]>ed)cnt[j]=1;
		else {
			cnt[j] = cnt[nxt[j]]+1;
			nxt[j] = nxt[nxt[j]];
		}
		//pf("nxt[%d] = %d, cnt = %d\n",j, nxt[j], cnt[j]);
	}
}

void solve(int casenum){
	int m,qt,a,b;
	sii(n,m);
	FOR(i,n)si(arr[i]);
	
	int blocks = (n+K-1)/K;
	for(int i=0; i<blocks; i++){
		updateBlock(i);
	}
	
	while(m--){
		si(qt);
		if(qt==0){
			sii(a,b);
			a--;
			arr[a]=b;
			updateBlock(a/K);
		}
		else {
			si(a);
			a--;
			int ans=0, last = -1, st,ed;
			while(a<n){
				ans+=cnt[a];
				if(last==-1 && nxt[a]>=n)last=a;
				a = nxt[a];
			}
			
			for(int i=last; i<n; i = i+arr[i]){
				last=i;
			}
			pf("%d %d\n",last+1, ans);
		}
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