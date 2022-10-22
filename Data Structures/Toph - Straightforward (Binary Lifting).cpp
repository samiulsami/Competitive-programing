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


const int N = 5e5+5;


int Table[19][N];

void solve(int casenum){
	int n;
	string s;
	cin>>n>>s;
	stack<int>st;
	
	for(int k=0; k<19; k++)
		for(int i=0; i<=n; i++)
			Table[k][i]=n;
	
	for(int i=0; i<n; i++){
		if(s[i]=='(')st.push(i);
		else{
			if(!st.empty()){
				Table[0][st.top()]=i;
				st.pop();
			}
		}
	}
	
	for(int k=1; k<19; k++){
		for(int i=0; i<n; i++){
			if(Table[k-1][i]+1<n)Table[k][i] = Table[k-1][Table[k-1][i]+1];
		}
	}
	
	int q,l,r;
	cin>>q;
	while(q--){
		cin>>l>>r;
		l--,r--;
		if(Table[0][l]>r){
			cout<<0<<endl;
			continue;
		}
		int x=l;
		for(int i=18; i>=0; i--){
			if(Table[i][x]<=r){
				x=Table[i][x];
				x++;
			}
		}
		cout<<x-l<<"\n";
	}
	
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