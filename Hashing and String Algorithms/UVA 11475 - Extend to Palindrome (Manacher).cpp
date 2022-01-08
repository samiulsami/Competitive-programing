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
string manacher(string s){
	int n = s.length();
	vector<int>odd(n),even(n);
	///even[i] stores the value for the right center of even length palindromes
	int x=0;
	for(int i=0,l=0,r=-1,k; i<n; i++){
		k=(i>r)?1:min(odd[l+r-i],r-i+1);
		while(i-k>=0 && i+k<n && s[i-k]==s[i+k])k++;
		odd[i]=k;
		if(i+k-1>r){
			l=i-k+1;
			r=i+k-1;
		}
		if(i+odd[i]==n)x=max(x,odd[i]);
	}
	int y=0;
	
	for(int i=0,l=0,r=-1,k; i<n; i++){
		k=(i>r)?0:min(even[l+r-i+1],r-i+1);
		while(i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k])k++;
		even[i]=k;
		if(i+k-1>r){
			l=i-k;
			r=i+k-1;
		}
		if(i+even[i]==n)y=max(y,even[i]);
	}
	
	
	string r=s.substr(0,min(n-(2*x-1), n-(2*y)));
	s.erase(s.begin(),s.begin()+sz(r));
	s=r+s;
	reverse(all(r));
	s=s+r;
	return s;
}


void solve(int casenum){
	string s;
	while(cin>>s){
		cout<<manacher(s)<<"\n";
	}
	
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
   // freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}