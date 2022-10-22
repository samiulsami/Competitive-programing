#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef long double ld;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<"\n"
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;
int arr[N];
int Tree[2][4*N];
int n;

inline int CombineLeft(int a, int b){
	if(arr[a]-a<arr[b]-b)return a;
	return b;
}

inline int CombineRight(int a, int b){
	if(arr[a]+a<arr[b]+b)return a;
	return b;
}

void build(int node, int l, int r){
	if(l==r)Tree[0][node]=Tree[1][node]=l;
	else{
		int mid = (l+r)>>1;
		build(node<<1, l, mid);
		build(node<<1|1, mid+1, r);
		Tree[0][node] = CombineLeft(Tree[0][node<<1], Tree[0][node<<1|1]);
		Tree[1][node] = CombineRight(Tree[1][node<<1], Tree[1][node<<1|1]);
	}
}

void update(int node, int l, int r, int pos){
	if(l==pos && r==pos)
		Tree[0][node] = Tree[1][node]=pos;
	else{
		int mid = (l+r)>>1;
		if(pos<=mid)update(node<<1, l, mid, pos);
		else update(node<<1|1, mid+1, r, pos);
		Tree[0][node] = CombineLeft(Tree[0][node<<1], Tree[0][node<<1|1]);
		Tree[1][node] = CombineRight(Tree[1][node<<1], Tree[1][node<<1|1]);
	}
}

int query(int node, int l, int r, int posl, int posr, bool b){
	if(l>=posl && r<=posr)return Tree[b][node];
	int mid = (l+r)>>1;
	if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr, b);
	if(posr<=mid)return query(node<<1, l, mid, posl, posr, b);
	
	if(b==0)return CombineLeft(query(node<<1, l, mid, posl, posr, b), query(node<<1|1, mid+1, r, posl, posr, b));
	return CombineRight(query(node<<1, l, mid, posl, posr, b), query(node<<1|1, mid+1, r, posl, posr, b));
}

void solve(int casenum){
	int q;
	sf("%d%d",&n,&q);
	for(int i=1; i<=n; i++)sf("%d",&arr[i]);
	build(1,1,n);
	
	int t,k,x;
	while(q--){
		sf("%d%d",&t,&k);
		if(t==1){
			sf("%d",&x);
			arr[k]=x;
			update(1,1,n,k);
		}
		else{
			int ans = INT_MAX;
			if(k!=1){
				int left = query(1,1,n,1,k,0);
				ans = min(ans, k-left+arr[left]);
			}
			if(k!=n){
				int right = query(1,1,n,k,n,1);
				ans = min(ans, right-k+arr[right]);
			}
			
			pf("%d\n",ans);
		}
	}
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}