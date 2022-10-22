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

template<typename T>
struct Treap{
	struct data{
		data *l=NULL,*r=NULL;
		int prior=rand(INT_MIN,INT_MAX),cnt=0;
		int lazy;
		T key;
		data(){}
	}*root=NULL;
	
	Treap(){root=NULL;}
	~Treap(){destroyTree(root);}
	
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
	
	void push(data *t){
		if(t && t->lazy!=0){
			t->key += t->lazy;
			if(t->l)t->l->lazy += t->lazy;
			if(t->r)t->r->lazy += t->lazy;
			t->lazy=0;
		}
	}
	
	void insert(T val){
		data *l, *r;
		split(root,l,r,val);
		if(r)r->lazy--;
		data *d = new data();
		d->key=val;
		d->lazy=0;
		merge(l,l,d);
		merge(root,l,r);
	}
	
	int get(T x){
		data *l, *r;
		split(root,l,r,x);
		int ret = getcnt(l)+x;
		merge(root,l,r);
		return ret;
	}
	
	void split(data *t, data* &l, data* &r, T key){
		push(t);
		if(!t)return void(l=r=NULL);
		if(key<t->key)split(t->l, l, t->l, key), r=t;
		else split(t->r, t->r, r, key), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		push(l);
		push(r);
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
};

void solve(int casenum){
	int n,m,x;
	char c;
	sii(n,m);
	
	Treap<int> T;
	int cnt=0;
	
	while(m--){
		sf(" %c%d",&c,&x);
		if(c=='D')T.insert(x);
		else pf("%d\n",T.get(x));
		
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