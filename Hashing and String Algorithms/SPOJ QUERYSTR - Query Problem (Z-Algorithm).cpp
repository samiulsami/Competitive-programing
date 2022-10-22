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

const int N = 1e6+5;

vector<int> Z_Algo(const string &s){
	int n = (int)s.size();
	vector<int>Z(n);
	for(int i=1,l=0,r=0; i<n; i++){
		if(i<=r)Z[i]=min(r-i+1,Z[i-l]);
		while(i+Z[i]<n && s[Z[i]]==s[i+Z[i]])Z[i]++;
		if(i+Z[i]-1>r)l=i,r=i+Z[i]-1;
	}
	return Z;
}

void solve(int casenum){
	string s;
	cin>>s;
	reverse(all(s));
	vi z = Z_Algo(s);
	z[0]=sz(s);
	int q,x;
	cin>>q;
	while(q--){
		cin>>x;
		cout<<z[sz(s)-x]<<'\n';
	}
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}