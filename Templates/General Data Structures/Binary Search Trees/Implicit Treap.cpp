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

mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l=NULL,*r=NULL;
		int cnt=0;
		uint32_t prior = uniform_int_distribution<int>(0, INT_MAX)(rng);
		T val;
		T minVal;
		bool rev=0;

		data(T x):val(x){reset();}

		inline void reset(){
			minVal = val;
			rev=0;
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
		cur->minVal = min(L->minVal, R->minVal);
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

	int leftMost(data *cur, int add=0){
		push(cur);
		if(cur->l && cur->minVal == cur->l->minVal)return leftMost(cur->l, add);
		if(cur->r && cur->minVal == cur->r->minVal)return leftMost(cur->r, add + getcnt(cur->l) + 1);
		return add + getcnt(cur->l);
	}

	int getMinPos(int L, int R){
		assert(L<=R && L>=0 && R<getcnt(root));
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		int ret = L+leftMost(m);
		merge(root,l,m);
		merge(root,root,r);
		return ret;
	}
	
	T query(int L, int R){
		assert(L<=R && L>=0 && R<getcnt(root));
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		T ret = m->minVal;
		merge(root,l,m);
		merge(root,root,r);
		return ret;
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
