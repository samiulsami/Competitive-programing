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
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;
const int mod = 1e9+7;

const ull mod1 = (1ull<<61) - 1;
inline ull hashmodmul(ull a, ull b){
    ull l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    ull ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod1) + (ret>>61);
    ret = (ret & mod1) + (ret>>61);
    return ret-1;
}
inline ull hashAdd(ull a, ull b){a+=b;return a>=mod1?a-mod1:a;}
inline ull hashSub(ull a, ull b){a-=b;return a>=mod1?a+mod1:a;}
const ull base1 = (ull)1541+(ull)rng()%(1<<22);
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0;i<n; i++)
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
};

int diff[1000005]={0};

void solve(int casenum){
	int n,m,len;
	cin>>n>>m;
	string p;
	cin>>p;
	len=sz(p);
	ll ans=1;
	Hash H(p,len);

	int prev=-1e9,x;
	FOR(i,m){
		cin>>x;
		x--;
		diff[x]++;
		diff[x+len]--;
		if(prev+len-1>=x){
			int matchlen=prev+len-1-x+1;
			if(H.getHash(1,matchlen)!=H.getHash(len-matchlen+1,len))ans=0;
		}
		prev=x;
	}

	int cnt=0;
	for(int i=0; i<n; i++){
		cnt+=diff[i];
		if(cnt==0)ans = (1LL*ans*26)%mod;
	}
	cout<<ans<<endl;
	
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}