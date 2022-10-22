#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
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
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;

ll arr[N],csum[N];
int Table[20][N];
int n,k;
ll S;

void solve(int casenum){
	sii(n,k);
	sl(S);
	csum[0]=0;
	for(int j=0; j<20; j++){
		Table[j][n+1]=n+1;
	}
	for(int i=1; i<=n; i++){
		sl(arr[i]);
		csum[i]=arr[i]+csum[i-1];
	}
	
	for(int i=1,low,high,mid,cur; i<=n; i++){
		low=i,high=n;
		cur=i;
		while(low<=high){
			mid = (low+high)>>1;
			if(csum[mid]-csum[i-1]<=S){
				cur=max(cur,mid);
				low=mid+1;
			}
			else high=mid-1;
		}
		Table[0][i]=cur+1;
	}
	
	for(int i=1; i<20; i++){
		for(int j=1; j<=n; j++){
			Table[i][j] = Table[i-1][Table[i-1][j]];
		}
	}
	
	auto get = [&](int cur)->int{
		int kk=k;
		for(int i=19; i>=0; i--){
			if((kk-(1<<i))>=0){
				if(Table[i][cur]>n)return n+1;
				cur = Table[i][cur];
				kk-=(1<<i);
			}
		}
		return cur;
	};
	
	int mx=1;
	for(int i=1; i<=n; i++){
		mx=max(mx,get(i)-i);
	}
	//pf("ans: ");
	pf("%d\n",mx);
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