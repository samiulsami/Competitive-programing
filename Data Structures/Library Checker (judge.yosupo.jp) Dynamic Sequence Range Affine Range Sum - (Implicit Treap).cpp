#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;
const int MOD = 998244353;
/*	
	push_back(x) inserts 'x' at the end
	push_front(x) inserts 'x' at the front
	insert(i,x) inserts 'x' at the index 'i'
	erase(i) erases the element at index 'i'

	reverse(l,r) reverses the sub-array [l,r]
	cyclic_shift(l,r,k,0) cyclically shifts the sub-array [l,r] k times to the right
	cyclic_shift(l,r,k,1) cyclically shifts the sub-array [l,r] k times to the left

	query(l,r) returns the minimum element in the sub-array [l,r]
	getMinPos(l,r) returns the index of the leftmost occurrence of the minimum element in the subarray [l,r]
	[i] returns the element at index 'i'

	**all above operations take O(log(n)) time**

	clear() deletes all elements O(n)
	size() returns the number of elements in the treap O(1)
*/
///Tested on https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum

mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l=NULL,*r=NULL;
		int cnt=0;
		uint32_t prior = uniform_int_distribution<int>(0, INT_MAX)(rng);
		T val;
		int sum=0,b=0,c=0;
		bool rev=0;
		bool lazyFlag=0;
		data(T x):val(x){reset();}

		inline void reset(){
			rev=0;
			sum=val;
			b=0;
			c=0;
			lazyFlag=0;
		}
	}*root=NULL;
	
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
	inline void clear(){destroyTree(root);root=NULL;}

	inline void Combine(data *cur, data *L, data *R){
		///might need to use temporary variables
		cur->sum = (L->sum + R->sum)%MOD;
	}

	inline void update_cnt(data *t){
		if(t){
			push(t->l);
			push(t->r);
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->reset();
			if(t->l)Combine(t, t->l, t);
			if(t->r)Combine(t, t, t->r);
		}
	}

	inline void propagate(data *t, data *u){
		if(u->lazyFlag){
			u->b = (1LL*u->b * t->b)%MOD;
			u->c = (1LL*u->c*t->b + 1LL*t->c)%MOD;
		}
		else{
			u->lazyFlag=1;
			u->b = t->b;
			u->c = t->c;
		}
	}
		
	inline void push(data *t){///push down lazy values
		if(t && t->rev){
			swap(t->l, t->r);
			if(t->l)t->l->rev^=1;
			if(t->r)t->r->rev^=1;
			t->rev=0;
		}
		if(t && t->lazyFlag){
			int cnt = getcnt(t->l) + getcnt(t->r) + 1;
			ll curSum = (1LL*cnt*t->c + 1LL*t->sum*t->b)%MOD;
			t->sum = curSum;
			t->val = (1LL*t->val*t->b + 1LL*t->c)%MOD;

			if(t->l)propagate(t,t->l);
			if(t->r)propagate(t,t->r);
			t->lazyFlag=0;
			t->b=0;
			t->c=0;
		}
	}
	
	T query(int L, int R){
		assert(L<=R && L>=0 && R<getcnt(root));
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		T ret = m->sum;
		merge(root,l,m);
		merge(root,root,r);
		return ret;
	}

	void update(int L, int R, int b, int c){
		assert(L<=R && L>=0 && R<getcnt(root));
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		push(m);
		m->lazyFlag=1;
		m->b=b;
		m->c=c;
		merge(root,l,m);
		merge(root,root,r);
	}

	void reverse(int L, int R){
		assert(L<=R && L>=0 && R<getcnt(root));
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		m->rev^=1;
		merge(root,l,m);
		merge(root,root,r);
	}
	
	void cyclic_shift(int L, int R, int k, bool leftShift=0){
		assert(L<=R && L>=0 && R<getcnt(root));
		k %= (R-L+1);
		if(k==0)return;
		data *l, *r, *m, *mr;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		if(leftShift)split(m,m,mr,k);
		else split(m,m,mr,(R-L+1)-k);
		merge(l,l,mr);
        merge(l,l,m);
		merge(root,l,r);
	}

	T& operator[](int index){
		assert(index>=0 && index<getcnt(root));
		return valAt(root,index,0);
	}
	T& valAt(data *t, int key, int add){
		push(t);
		int curkey = getcnt(t->l)+add;
		if(key==curkey)return t->val;
		if(key<curkey)return valAt(t->l, key, add);
		return valAt(t->r, key, curkey+1);
	}
	
	void push_back(T val){
		data *d = new data(val);
		merge(root,root,d);
	}

	void push_front(T val){
		data *d = new data(val);
		merge(root,d,root);
	}
	
	void insert(int index, T val){
		data *d = new data(val);
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void erase(int index){
		assert(index>=0 && index<getcnt(root));
		erase(index,root);
	}
	void erase(int index, data* &t, int add=0){
		push(t);
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

inline void solve(int caseNum){
	int n,q;
	cin>>n>>q;

	implicitTreap<int>T;
	for(int i=0,x; i<n; i++){
		cin>>x;
		T.push_back(x);
	}

	int qt,l,r,b,c;
	while(q--){

		cin>>qt;
		if(qt==0){
			cin>>b>>c;
			if(b==T.size())T.push_back(c);
			else T.insert(b,c);
		}
		else if(qt==1){
			cin>>l;
			T.erase(l);
		}
		else if(qt==2){
			cin>>l>>r;
			T.reverse(l,r-1);
		}
		else if(qt==3){
			cin>>l>>r>>b>>c;
			T.update(l,r-1,b,c);
		}
		else {
			cin>>l>>r;
			cout<<T.query(l,r-1)<<"\n";;
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