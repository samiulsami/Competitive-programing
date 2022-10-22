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


ll arr[N];

template<typename T>
struct minQueue{
    stack<pair<T,T> >A,B;
    minQueue(){}
    T check(const T &a, const T &b){return __gcd(a,b);}
    void push(T x){
        T y = A.empty()?x:check(x,A.top().second);
        A.push({x,y});
    }
    T pop(){
        if(B.empty()){
            while(!A.empty()){
                T x=A.top().first;
                A.pop();
                T y = B.empty()?x:check(x,B.top().second);
                B.push({x,y});
            }
        }
        T ret=B.top().first;
        B.pop();
        return ret;
	}
    T top(){
        if(A.empty())return B.top().second;
        if(B.empty())return A.top().second;
        return check(A.top().second, B.top().second);
    }
    bool empty(){return A.empty() && B.empty();}
};

void solve(int casenum){
	int n;
	si(n);
	bool b=0;
	for(int i=0; i<n; i++){
		sf("%lld",&arr[i]);
		if(arr[i]==1)b=1;
	}
	
	if(b)pf("1\n"),exit(0);
	
	minQueue<ll>Q;
	int ans=n+1;
	int l=0;
	for(int i=0; i<n; i++){
		Q.push(arr[i]);
		while(l<i && Q.top()==1){
			ans=min(ans,i-l+1);
			l++;
			Q.pop();
		}
	}
	
	if(ans==n+1)ans=-1;
	pf("%d\n",ans);
	
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