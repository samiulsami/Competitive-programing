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
		T val[2];
		int pref[2],suff[2],total[2],ans[2];
		bool rev;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			rev=0;
			l=r=NULL;
		}
		void reset(){
			for(int i=0; i<2; i++){
				pref[i]=suff[i]=total[i]=ans[i]=val[i];
			}
		}
		void invert(){
			swap(val[0],val[1]);
			swap(pref[0],pref[1]);
			swap(suff[0],suff[1]);
			swap(total[0],total[1]);
			swap(ans[0],ans[1]);
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
	
	void Combine(data *ret, data *L, data *R){
		for(int i=0; i<2; i++){
			int pref,suff,total,ans;
			total = L->total[i] + R->total[i];
			pref = max({L->pref[i], L->total[i] + R->pref[i], total});
			suff = max({R->suff[i], R->total[i] + L->suff[i], total});
			ans = max({L->ans[i], R->ans[i], L->suff[i] + R->pref[i]});
			
			ret->pref[i]=pref;
			ret->suff[i]=suff;
			ret->ans[i]=ans;
			ret->total[i]=total;
		}
	}
	
	inline void update_cnt(data *t){
		if(t){
			push(t->l);
			push(t->r);
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->reset();
			if(t->l)Combine(t,t->l,t);
			if(t->r)Combine(t,t,t->r);
		}
	}
		
	void propagate(data *t, data *u){
		if(u)u->rev^=1;
	}		
	
	inline void push(data *t){///push down lazy values
		if(t && t->rev){
			t->invert();
			propagate(t,t->l);
			propagate(t,t->r);
			t->rev=0;
		}
	}
	
	int query(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		int ret = m->ans[0];
		merge(root,l,m);
		merge(root,root,r);
		return ret;
	}
	
	void cyclic_shift(int L, int R, int x){///left shift
		if(R-L+1==x){
			data *l, *r, *m;
			split(root,l,m,L);
			split(m,m,r,R-L+1);
			m->rev^=1;
			merge(m,m,r);
			merge(root,l,m);
		}
		else{
			data *l,*r,*m,*LL;
			split(root,l,m,L);
			split(m,m,r,R-L+1);
			split(m,LL,m,x);
			LL->rev^=1;
			merge(m,m,LL);
			merge(m,m,r);
			merge(root,l,m);
		}
	}
	
	T at(int index){return valAt(root,index,0);}
	T valAt(data *t, int key, int add){
		push(t);
		int curkey = getcnt(t->l)+add;
		if(key==curkey)return t->val;
		if(key<curkey)return valAt(t->l, key, add);
		return valAt(t->r, key, curkey+1);
	}
	
	void insert(T val){
		//insert(getcnt(root),val);
		data *d = new data();
		d->val[0]=val;
		d->val[1]=-val;
		d->reset();
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
		push(t);
		int cur=add+getcnt(t->l);
		if(key<=cur)split(t->l, l, t->l, key, add), r=t;
		else split(t->r, t->r, r, key, cur+1), l=t;
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
	int n,q,l,r,qt;
	implicitTreap<int> T;
	
	si(n);
	FOR(i,n){
		si(qt);
		T.insert(qt);
	}
	
	pf("Case #%d:\n",casenum);
	si(q);
	while(q--){
		si(qt);
		if(qt==1){
			sii(l,r);
			pf("%d\n",T.query(l-1,r-1));
		}
		else{
			siii(l,r,qt);
			if(qt>0)T.cyclic_shift(l-1,r-1,qt);
		}
		// pf("treap: ");
		// for(int i=0; i<n; i++)pf("%d ",T.at(i));
		// nl;
	}
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}