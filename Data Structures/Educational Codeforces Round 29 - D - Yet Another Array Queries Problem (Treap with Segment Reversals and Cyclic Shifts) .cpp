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


const int N = 2e5+5;


int arr[N];

struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		int val;
		bool rev;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			rev=0;
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
	int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}
	
	inline void update_cnt(data *t){
		if(t){
			push(t->l);
			push(t->r);
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
		}
	}
		
	void propagate(data *t, data *u){
		if(u)u->rev^=1;
	}		
	
	inline void push(data *t){///push down lazy values
		if(t && t->rev){
			swap(t->l, t->r);
			propagate(t,t->l);
			propagate(t,t->r);
			t->rev=0;
		}
	}
	
	void range_rev(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		m->rev^=1;
		merge(root,l,m);
		merge(root,root,r);
	}
	
	void cyclic_shift(int L, int R){
		data *l,*r,*m,*rr;
		split(root,l,m,L);
		split(m,m,r,R-L);
		split(r,rr,r,1);
		merge(m,m,r);
		merge(rr,rr,m);
		merge(root,l,rr);
	}
	
	int getval(int index){
		return valAt(root,index,0);
	}
	
	int valAt(data *t, int key, int add){
		push(t);
		int curkey = getcnt(t->l)+add;
		if(key==curkey)return t->val;
		if(key<curkey)return valAt(t->l, key, add);
		return valAt(t->r, key, curkey+1);
	}
	
	// int find_min(data *t, int add=0){
		// push(t);
		// int cur = getcnt(t->l)+add;
		// if(t->l && t->l->ans == t->ans)return find_min(t->l,add);
		// if(t->r && t->r->ans == t->ans)return find_min(t->r,cur+1);
		// return cur;
	// }
	
	// int getmin(int L, int R){
		// data *l,*r,*m;
		// split(root,l,m,L);
		// split(m,m,r,R-L+1);
		// int ret = find_min(m) + L;
		// merge(root,l,m);
		// merge(root,root,r);
		// return ret;
	// }
	
	void insert(int val){insert(getcnt(root),val);}
	void insert(int index, int val){
		data *d = new data();
		d->val=val;
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void split(data *t, data* &l, data* &r, int key, int add=0){
		if(!t)return void(l=r=NULL);
		push(t);
		int cur=add+getcnt(t->l);
		if(key<=cur)split(t->l, l, t->l, key, add), r=t;
		else split(t->r, t->r, r, key, cur+1), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r, int add=0){
		push(l);
		push(r);
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r, add+1+getcnt(l->l)), t=l;
		else merge(r->l, l, r->l, add), t=r;
		update_cnt(t);
	}
};
 

void solve(int casenum){
	int n,q,m,l,t,r;
	siii(n,q,m);
	
	implicitTreap T;
	
	FOR(i,n){
		si(arr[i]);
		T.insert(arr[i]);
	}
	
	FOR(i,q){
		siii(t,l,r);
		if(l==r)continue;
		if(t==2)T.range_rev(l-1,r-1);
		else T.cyclic_shift(l-1,r-1);
	}
	
	FOR(i,m){
		si(t);
		pf("%d ",T.getval(t-1));
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