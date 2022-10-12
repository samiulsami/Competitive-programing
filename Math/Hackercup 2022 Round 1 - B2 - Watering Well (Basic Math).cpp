#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

template<const int MOD>
///(x1-a)^2 + (x2-a)^2 + ... + (xn-a)^2 = x1^2 + x2^2 + ... xn^2 - + a^n -  a*(2*x1 + 2*x2 + ... + 2*xn)

inline void solve(int caseNum){
	ll n,q;
	cin>>n;
	ll treeXsquare=0;
	ll treeYsquare=0;
	ll tree2X=0;
	ll tree2Y=0;

	for(ll i=0,a,b; i<n; i++){
		cin>>a>>b;
		a%=MOD;
		b%=MOD;
		treeXsquare += (a*a)%MOD;
		treeXsquare%=MOD;
		tree2X += (a+a)%MOD;
		tree2X%=MOD;
		treeYsquare += (b*b)%MOD;
		treeYsquare%=MOD;
		tree2Y += (b+b)%MOD;
		tree2Y%=MOD;
	}
	// dbug(treeXsquare);
	// dbug(tree2X);
	// dbug(treeYsquare);
	// dbug(tree2Y);
	ll x,y;
	ll ans=0;
	cin>>q;

	while(q--){
		cin>>x>>y;
		ll curx = (treeXsquare - (1LL*x*tree2X)%MOD)%MOD;
		ll cury = (treeYsquare - (1LL*y*tree2Y)%MOD)%MOD;
		while(curx<0)curx = (curx+MOD)%MOD;
		while(cury<0)cury = (cury+MOD)%MOD;
		x *=x;
		x%=MOD;
		x*=n;
		x%=MOD;
		y *= y;
		y%=MOD;
		y*=n;
		y%=MOD;
		curx = (curx + x)%MOD;
		cury = (cury + y)%MOD;
		while(curx<0)curx = (curx+MOD)%MOD;
		while(cury<0)cury = (cury+MOD)%MOD;
		ans = (ans + curx + cury)%MOD;
	}

	cout<<"Case #"<<caseNum<<": "<<(ans+MOD)%MOD<<"\n";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}