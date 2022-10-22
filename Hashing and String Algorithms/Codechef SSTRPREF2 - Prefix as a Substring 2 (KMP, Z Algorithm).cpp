#include<bits/stdc++.h>
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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


const int N = 1e6+5;

char S1[N],S2[N],X[N];
char tmp[N+N];
int s1pi[N],s2pi[N];
int Z[N+N];

void kmp(const char *s, int *pi, int n){///kmp
	pi[0]=0;
    for(int i=1,j=0; i<n; i++){
        j=pi[i-1];
        while(j && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])pi[i]=j+1;
		else pi[i]=0;
    }
}

int calc(const char *s, int *pi, int n, int xn){
	int ret=0;
	for(int i=0,j=0; i<xn; i++){
		while(j && s[j]!=X[i])j=pi[j-1];
		if(s[j]==X[i])j++;
		if(j==n)return n;
		ret=max(ret,j);
	}
	return ret;
}

void Z_Algo(string tmp, int *Z){
	Z[0]=0;
	for(int i=1,l=0,r=0,n=sz(tmp); i<n; i++){
		Z[i]=0;
		if(i<=r)Z[i]=min(r-i+1,Z[i-l]);
		while(i+Z[i]<n && tmp[Z[i]]==tmp[i+Z[i]])Z[i]++;
		if(i+Z[i]-1>r)l=i,r=i+Z[i]-1;
	}
	Z[sz(tmp)]=0;
}

int counter[N];

void solve(int casenum){
	sf("%s%s%s",&S1,&S2,&X);
	int s1n=strlen(S1);
	int s2n=strlen(S2);
	int Xn=strlen(X);
	for(int i=0; i<=s1n; i++)counter[i]=0;
	kmp(S2,s2pi,s2n);
	kmp(S1,s1pi,s1n);
	Z_Algo(string(S2)+"$"+string(X),Z);
	ll ans = 1 + calc(S2,s2pi,s2n,Xn);
	int mx=0;
	
	for(int i=0,j=0,k; i<Xn; i++){
		while(j && S1[j]!=X[i])j=s1pi[j-1];
		if(S1[j]==X[i])j++;
		k=j;
		if(k>0){
			if(i+1<Xn)counter[k]=max(counter[k],Z[i+2+s2n]);
			k=s1pi[k-1];
		}
		while(k){
			if(counter[k]>=counter[j])break;
			counter[k]=counter[j];
			k=s1pi[k-1];
		}
		mx=max(mx,j);
		if(j==s1n)j=s1pi[j-1];
	}
	ans+=mx;
	for(int i=1; i<=s1n; i++)ans+=(ll)counter[i];
	pf("%lld\n",ans);
	
	 // string a(S1),b(S2),c(X);
	// ll ans1=1;
	// for(int i=0; i<=sz(a); i++){
		// for(int j=0; j<=sz(b); j++){
			// string req="";
			// if(i>0)req+=a.substr(0,i);
			// if(j>0)req+=b.substr(0,j);
			// if(sz(req)==0)continue;
			// for(int k=0; k<sz(c); k++){
				// if(c.substr(k,sz(req))==req){
					// ans1++;
					// break;
				// }
			// }
		// }
	// }
	// if(ans!=ans1){
		// cout<<"ans: "<<ans<<", ans1: "<<ans1<<"\n strings: "<<a<<endl<<b<<endl<<c<<endl;
		// cout<<"----------------------\n";
	// }
	//cout<<ans1<<"\n";
}

/*fail case
1
vvzklrqeaixmggchqkmqybksjwprpyhije
mybgfcmauwytkeunderzgvc
zruzfgmafitevvmomzstnqrzbgrtqujwjpcyvfivrxkhehnpet
*/
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
     // freopen("randinput.txt","r",stdin);
      //freopen("randoutput1.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}