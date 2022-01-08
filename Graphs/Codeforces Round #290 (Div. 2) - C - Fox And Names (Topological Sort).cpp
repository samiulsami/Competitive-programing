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

int indeg[500]={0};
vi graph[500];


void solve(int casenum){
	int n;
	cin>>n;
	vector<string>strings(n);
	FOR(i,n){
		cin>>strings[i];
	}
	
	for(int i=0; i<n-1; i++){
		bool equal=1;
		for(int j=0; j<min(sz(strings[i]),sz(strings[i+1])); j++){
			if(strings[i][j]==strings[i+1][j])continue;
			equal=0;
			graph[strings[i][j]].push_back(strings[i+1][j]);
			indeg[strings[i+1][j]]++;
			//cout<<strings[i][j]<<" "<<strings[i+1][j]<<endl;
			break;
		}
		if(equal && sz(strings[i])>sz(strings[i+1])){
			cout<<"Impossible"<<endl;
			return;
		}		
	}
	//nl;
	bool pos=1;

	string ans;
	queue<int>q;
	for(int i='a'; i<='z'; i++){
		if(indeg[i]==0)q.push(i);
	}
	
	while(!q.empty()){
		int u=q.front();
		q.pop();
		ans.push_back(u);
		for(int v:graph[u]){
			if(--indeg[v]==0){
				q.push(v);
			}
		}
	}
	
	if(sz(ans)<26)cout<<"Impossible"<<endl;
	else cout<<ans<<endl;
	


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