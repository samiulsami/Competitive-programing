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

template<typename T>
struct Treap{
	struct data{
		data *l=NULL,*r=NULL;
		int prior=rand(INT_MIN,INT_MAX),cnt=0;
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
	inline void update_cnt(data *t){if(t)t->cnt = getcnt(t->l) + getcnt(t->r) + 1;}
	
	
	void insert(T val){
		if(!count(val)){
			data *d = new data();
			d->key=val;
			insert(root,d);
		}
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
	
	bool count(T val){return count(val,root);}
	bool count(T key, data *t){///Check if key exists in tree
		if(!t)return 0;
		if(t->key==key)return 1;
		if(t->key<key)return count(key,t->r);
		return count(key,t->l);
	}
	
	T kth(int k){return kth(k,root);}
	T kth(int k, data *t){///Returns the k'th smallest element
		if(!t)return 0;
		if(getcnt(t->l)==k)return t->key;
		if(getcnt(t->l)>k)return kth(k, t->l);
		return kth(k-getcnt(t->l)-1, t->r);
	}
	
	int LTE(T key){return LTE(key,root);}
	int LTE(T key, data *t){///Counts the number of elements less than or equal to 'key'
		if(!t)return 0;
		if(t->key >= key)return LTE(key, t->l);
		return getcnt(t->l) + 1 + LTE(key, t->r);
	}
	
	void split(data *t, data* &l, data* &r, T key){
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
	map<int,Treap<int> >mp;
	int n,m;
	sii(n,m);
	for(int i=0,x; i<n; i++){
		si(x);
		mp[x].insert(i);
		arr[i]=x;
	}
	
	int l,k;
	while(m--){
		sii(l,k);
		mp[arr[l]].erase(l);
		arr[l]=k;
		mp[k].insert(l);
		pf("%d\n",mp[k].LTE(l));
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