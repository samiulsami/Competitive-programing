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
int Tree[4*N]={0};
int n;
 
void update(int node, int l, int r, int pos, int val){
	if(l==pos && r==pos)Tree[node]=val;
	else{
		int mid = (l+r)>>1;
		if(pos<=mid)update(node<<1, l, mid, pos, val);
		else update(node<<1|1, mid+1, r, pos, val);
		Tree[node] = max(Tree[node<<1], Tree[node<<1|1]);
	}
}
 
int query(int node, int l, int r, int posl, int posr){
	if(l>=posl && r<=posr)return Tree[node];
	int mid = (l+r)>>1;
	if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr);
	if(posr<=mid)return query(node<<1, l, mid, posl, posr);
	return max(query(node<<1|1, mid+1, r, posl, posr),  query(node<<1, l, mid, posl, posr));
}
 

template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T val;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			l=r=NULL;
		}
	}*root;
	
	implicitTreap(){root=NULL;}
	~implicitTreap(){destroyTree(root);}
	
	void destroyTree(data *t){
		if(!t)return;
		if(t->l)destroyTree(t->l);
		if(t->r)destroyTree(t->r);
		delete t;
	}
	
	inline bool empty(){return getcnt(root)==0;}
	inline int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}
	
	inline void update_cnt(data *t){
		if(t)t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
	}
		
	void reverse(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		m->rev^=1;
		merge(root,l,m);
		merge(root,root,r);
	}
	
	void cyclic_shift(int L, int R){///right shift
		data *l,*r,*m,*rr;
		split(root,l,m,L);
		split(m,m,r,R-L);
		split(r,rr,r,1);
		merge(m,m,r);
		merge(rr,rr,m);
		merge(root,l,rr);
	}
	
	void cyclic_shiftL(int L, int R){///left shift
		data *l,*r,*m,*ll;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		split(m,ll,m,1);
		merge(m,m,ll);
		merge(m,m,r);
		merge(root,l,m);
	}
	
	T at(int index){return valAt(root,index,0);}
	T valAt(data *t, int key, int add){
		int curkey = getcnt(t->l)+add;
		if(key==curkey)return t->val;
		if(key<curkey)return valAt(t->l, key, add);
		return valAt(t->r, key, curkey+1);
	}
	
	void insert(T val){
		//insert(getcnt(root),val);
		data *d = new data();
		d->val=val;
		merge(root,root,d);
	}
	
	void insert(int index, T val){
		data *d = new data();
		d->val=val;
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	
	void split(data *t, data* &l, data* &r, int key, int add=0){
		if(!t)return void(l=r=NULL);
		int cur=add+getcnt(t->l);
		if(key<=cur)split(t->l, l, t->l, key, add), r=t;
		else split(t->r, t->r, r, key, cur+1), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
	
	void dfs(data *t){
		if(!t)return;
		dfs(t->l);
		int cur=1;
		//pf("%d ",t->val);
		if(t->val > 1)cur = query(1,1,n,1,t->val - 1) + 1;
		update(1,1,n,t->val,cur);
		dfs(t->r);
	}
};


void solve(int casenum){
	int q,l,r,x;
	implicitTreap<int> T;
	sii(n,q);
	for(int i=1; i<=n; i++)T.insert(i);
		// T.dfs(T.root);
		// nl;
	while(q--){
		sii(l,r);
		l--,r--;
		if(l==r)continue;
		if(l>r)T.cyclic_shift(r,l);
		else T.cyclic_shiftL(l,r);
		// T.dfs(T.root);
		// nl;
	}
	
	T.dfs(T.root);
	pf("%d\n",n-Tree[1]);
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