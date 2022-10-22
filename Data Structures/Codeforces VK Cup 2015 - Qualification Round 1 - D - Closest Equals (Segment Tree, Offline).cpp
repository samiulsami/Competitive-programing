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

int Tree[4*N];
int arr[N];
int ans[N];

void update(int node, int l, int r, int pos, int val){
	if(l==pos && r==pos)Tree[node]=val;
	else{
		int mid = (l+r)>>1;
		if(pos<=mid)update(node<<1, l, mid, pos, val);
		else update(node<<1|1, mid+1, r, pos, val);
		Tree[node] = min(Tree[node<<1], Tree[node<<1|1]);
	}
}

int query(int node, int l, int r, int posl, int posr){
	if(l>=posl && r<=posr)return Tree[node];
	int mid = (l+r)>>1;
	if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr);
	if(posr<=mid)return query(node<<1, l, mid, posl, posr);
	return min(query(node<<1, l, mid, posl, posr), query(node<<1|1, mid+1, r, posl, posr));
}



void solve(int casenum){
	map<int,int>mp;
	vector<pair<pii,int> >queries;
	int n,m;
	sii(n,m);
	for(int i=0; i<=4*n; i++)Tree[i]=INT_MAX;
	for(int i=1; i<=n; i++)si(arr[i]);
	for(int i=0,a,b; i<m; i++){
		sii(a,b);
		queries.emplace_back(pair<pii,int>(pii(b,a),i));
	}
	sort(all(queries));
	
	int r=0;
	for(auto &p:queries){
		//pf("%d %d\n",p.first.first, p.first.second);
		while(r<p.first.first){
			r++;
			if(!mp.count(arr[r]))mp[arr[r]]=r;
			else{
				int ind = mp[arr[r]];
				update(1,1,n,ind,r-ind);
				mp[arr[r]]=r;
			}
		}
		ans[p.second] = query(1,1,n,p.first.second,n);
	}
	
	for(int i=0,x; i<m; i++){
		x=ans[i];
		if(ans[i]==INT_MAX)x=-1;
		pf("%d\n",x);
	}
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