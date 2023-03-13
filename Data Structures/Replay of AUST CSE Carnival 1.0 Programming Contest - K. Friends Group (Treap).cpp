#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

template<typename T>
struct Treap{
	struct data{
		data *l=NULL,*r=NULL;
		int prior=rng(),cnt=0;
		T key;
		int minindex,maxindex;
		int pref,suff,ans;
		data(){}
		void reset(){
			minindex=key;
			maxindex=key;
			pref=1;
			suff=1;
			ans=1;
		}
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

	inline void Combine(data *cur, data *L, data *R){
		int suff = R->suff;
		int pref = L->pref;
		if(L->maxindex+1 == R->minindex){
			if(L->pref == L->maxindex-L->minindex+1)
				pref = L->pref + R->pref;
			if(R->suff = R->maxindex-R->minindex+1)
				suff = R->suff + L->suff;
		}
		int minindex = L->minindex;
		int maxindex = R->maxindex;
		cur->suff = suff;
		cur->pref = pref;
		cur->minindex = minindex;
		cur->maxindex = maxindex;
	}

	inline void update_cnt(data *t){
		if(t){
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->reset();
			if(t->l)Combine(t, t->l, t);
			if(t->r)Combine(t, t, t->r);
		}
	}
	
	int query(int x){
		data *L, *R;
		split(root,L,R,x);
		assert(R);
		int ret = R->pref;
		if(L && L->maxindex +1 == R->minindex)ret = L->suff + R->pref;
		merge(root,L,R);
		return ret;
	}
	
	void insert(T val){
		data *d = new data();
		d->key=val;
		d->reset();
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

int arr[100005];

inline void solve(int caseNum){
	int n,q;
	cin>>n>>q;

	map<int,Treap<int> >mp;
	for(int i=1; i<=n; i++){
		cin>>arr[i];
		mp[arr[i]].insert(i);
	}

	int qt,x,y;
	while(q--){
		cin>>qt>>x;
		if(qt==1){
			cin>>y;
			mp[arr[x]].erase(x);
			arr[x] = y;
			mp[arr[x]].insert(x);
		}
		else{
			cout<<mp[arr[x]].query(x)-1<<"\n";
		}
	}
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