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
 
template<typename T>
struct Treap{
	struct data{
		data *l=NULL,*r=NULL;
		int prior=rand(INT_MIN,INT_MAX),cnt=0;
		T key;
		ll sum;
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
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->sum = t->key[0];
			if(t->l)t->sum += t->l->sum;
			if(t->r)t->sum += t->r->sum;
		}
	}
	
	void insert(T val){
	
			data *d = new data();
			d->key=val;
			d->sum=val[0];
			insert(root,d);
		
	}

	void insert(data* &t, data *u){
		if(!t)t=u;
		else if(u->prior > t->prior)split(t, u->l, u->r, u->key), t=u;
		else insert(t->key <= u->key ? t->r : t->l, u);
		update_cnt(t);
	}
	
	void erase(T val){erase(val,root);}
	void erase(T key, data* &t){
		if(!t)return;
		if(t->key==key){
			data *it = t;
			merge(t, t->l, t->r);
			delete it;
		}
		else erase(key, key < t->key ? t->l: t->r);
		update_cnt(t);
	}
	
	T kth(int k){return kth(k,root);}
	T kth(int k, data *t){///Returns the k'th smallest element
		if(!t)return {0,0};
		if(getcnt(t->l)==k)return t->key;
		if(getcnt(t->l)>k)return kth(k, t->l);
		return kth(k-getcnt(t->l)-1, t->r);
	}
	
	ll get(int median){
		data *l,*r;
		split(root,l,r,{median,2000000000});
		ll lesserEqual = 0;
		ll lesserEqualCount = 0;
		ll greater = 0;
		ll greaterCount = 0;
		
		if(l){
			lesserEqual = l->sum;
			lesserEqualCount = l->cnt;
		}
		if(r){
			greater = r->sum;
			greaterCount = r->cnt;
		}
		
		merge(root,l,r);
		ll ans = lesserEqualCount*median - lesserEqual + greater - 1LL*median*greaterCount;
		return ans;
	}
	
	void split(data *t, data* &l, data* &r, T key){/// Subtree 'l' contains keys strictly less than 'key'
		if(!t)return void(l=r=NULL);
		if(key<=t->key)split(t->l, l, t->l, key), r=t;
		else split(t->r, t->r, r, key), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
};
 
int arr[N];


void solve(int casenum){
	int n,k;
	sf("%d%d",&n,&k);
	
	for(int i=1; i<=n; i++)sf("%d",&arr[i]);

	Treap<pii>T;
	
	for(int i=1; i<=n; i++){
		T.insert({arr[i],i});
		
		if(T.size()==k){
			
			pf("%lld ",T.get(T.kth(k/2)[0]));
			T.erase({arr[i-k+1],i-k+1});
			
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