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


const int N = 3e5+5;

int nxt[N][26];
void prefixautomaton(const string &s){
	int n = (int)s.size();
	vector<int>pi(n);
	for(int i=1,j=0; i<n; i++){
		j=pi[i-1];
		while(j && s[i]!=s[j])j=pi[j-1];
		if(s[i]==s[j])pi[i]=j+1;
		else pi[i]=0;
	}
	for(char i='a'; i<='z'; i++){
		if(s[0]==i)nxt[0][i-'a']=1;
		else nxt[0][i-'a']=0;
	}
	for(int i=1; i<=n; i++){
		for(char c='a'; c<='z'; c++){
			if(i==n || s[i]!=c)nxt[i][c-'a']=nxt[pi[i-1]][c-'a'];
			else nxt[i][c-'a']=i+1;
		}
	}
}

vector<pair<int,string>>graph[N];
int m;

int dfs(int u, int pos){
	int ret=0,tmp;
	for(auto &e:graph[u]){
		tmp=pos;
		for(char &c:e.second){
			tmp=nxt[tmp][c-'a'];
			if(tmp==m)ret++;
		}
		ret+=dfs(e.first,tmp);
	}
	return ret;
}

void solve(int casenum){
	int n;
	cin>>n;
	string t;
	for(int i=2,u; i<=n; i++){
		cin>>u>>t;
		graph[u].emplace_back(i,t);
	}
	cin>>t;
	prefixautomaton(t);
	m=sz(t);
	cout<<dfs(1,0)<<endl;
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