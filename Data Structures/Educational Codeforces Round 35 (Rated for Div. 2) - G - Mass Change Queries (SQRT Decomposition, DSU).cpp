#include<bits/stdc++.h>
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;
const int K = 450;

int arr[N];
int parent[101][K];
int dsu[N];
int n;

int Find(int u){
	if(u==dsu[u])return u;
	return dsu[u] = Find(dsu[u]);
}

inline void Compute(int x){
	int l = x*K;
	int r = min(n,l+K)-1;
	//for(int i=1; i<=100; i++)parent[i][x]=-1;
	for(int i=l; i<=r; i++)dsu[i]=i;
	for(int i=l; i<=r; i++){
		if(parent[arr[i]][x]==-1)parent[arr[i]][x]=i;
		else {
			dsu[i] = parent[arr[i]][x];
		}
	}
}

inline void updateBlockFast(int x, int oldval, int newval){
	if(parent[oldval][x]==-1)return;

	if(parent[newval][x]==-1){
		arr[Find(parent[oldval][x])]=newval;
		parent[newval][x] = Find(parent[oldval][x]);
		parent[oldval][x] = -1;
		return;
	}

	int u = Find(parent[oldval][x]);
	int v = Find(parent[newval][x]);
	assert(u!=v);
	dsu[u] = v;
	arr[v] = newval;

	parent[newval][x] = v;
	parent[oldval][x]=-1;
}

int tmp[K];

void update(int l, int r, int oldval, int newval){
	int L = l/K;
	int R = r/K;

	auto work = [&](int lll, int rrr, int x)->void{
		int a = x*K;
		int b = min(a+K,n)-1;
		for(int i=a; i<=b; i++){
			tmp[i-a] = arr[Find(i)];
			parent[arr[Find(i)]][x]=-1;
			if(i>=lll && i<=rrr && arr[Find(i)]==oldval)tmp[i-a] = newval;
		}
		for(int i=a; i<=b; i++){
			arr[i] = tmp[i-a];
			parent[arr[i]][x]=-1;
		}
		Compute(x);
	};

	if(L==R){
		work(l,r,L);
		return;
	}

	work(l, (L+1)*K - 1, L);
	work(R*K, r, R);
	for(int i=L+1; i<R; i++)updateBlockFast(i,oldval,newval);
}

inline void solve(int caseNum){
	memset(parent,-1,sizeof(parent));
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>arr[i];
		dsu[i]=i;
	}

	for(int i=0,x=(n+K-1)/K; i<x; i++)
		Compute(i);

	int q,l,r,x,y;
	cin>>q;
	while(q--){
		cin>>l>>r>>x>>y;
		if(x!=y)update(l-1,r-1,x,y);
	}

	for(int i=0; i<n; i++)cout<<arr[Find(i)]<<" ";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}