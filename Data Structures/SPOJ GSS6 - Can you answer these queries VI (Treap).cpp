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
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T val;
		ll pref,suff,total,ans;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			reset();
			l=r=NULL;
		}
		void reset(){
			pref=suff=total=ans=val;
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
	
	inline void Combine(data* &t, data *l, data *r){
		ll pref,suff,total = l->total+r->total;
		pref = l->pref;
		suff = r->suff;
		pref=max({l->pref, l->total, l->total+r->pref});
		suff=max({r->suff, r->total, r->total+l->suff});
		t->ans=max({l->ans,r->ans, pref, suff, l->suff+r->pref});
		t->pref=pref;
		t->suff=suff;
		t->total=l->total+r->total;
	}
	
	inline void update_cnt(data *t){
		if(t){
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->reset();
			if(t->l)Combine(t, t->l, t);
			if(t->r)Combine(t, t, t->r);
		}
	}
		
	
	void replace(int index, int newval){replace(root, index, newval, 0);}
	void replace(data* &t, int key, int newval, int add){
		if(!t)return;
		int curkey = add+getcnt(t->l);
		if(curkey==key){
			t->val=newval;
			t->reset();
		}
		else if(key<curkey)replace(t->l, key, newval, add);
		else replace(t->r, key, newval, curkey+1);
		update_cnt(t);
	}
	
	void append(T val){
		data *d = new data();
		d->val=val;
		merge(root,root,d);
	}
	
	ll get(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		ll ret = m?m->ans:0;
		merge(m,m,r);
		merge(root,l,m);
		return ret;
	}
	
	void insert(int index, T val){
		data *d = new data();
		d->val=val;
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void erase(int index){erase(index,root);}
	void erase(int index, data* &t, int add=0){
		if(!t)return;
		int curkey = getcnt(t->l)+add;
		if(curkey==index){
			data *it = t;
			merge(t, t->l, t->r);
			delete it;
		}
		else if(curkey>index)erase(index, t->l, add);
		else erase(index, t->r, curkey+1);
		update_cnt(t);
	}
	
	void split(data *t, data* &l, data* &r, int key, int add=0){/// Subtree 'l' contains keys strictly less than 'key'
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
};


void solve(int casenum){
	implicitTreap<int>T;
	int n,l,r,x,q;
	char c;
	si(n);
	for(int i=0,x; i<n; i++){
		si(x);
		T.append(x);
	}
	si(q);

	while(q--){
		sf(" %c",&c);
		if(c=='D'){
			si(l);
			T.erase(l-1);
		}
		else{
			sii(l,r);
			if(c=='I')T.insert(l-1,r);
			else if(c=='R')T.replace(l-1,r);
			else{
				pf("%lld\n",T.get(l-1,r-1));
			}
		}
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