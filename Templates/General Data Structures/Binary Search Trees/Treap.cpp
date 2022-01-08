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
		if(t->key > key)return LTE(key, t->l);
		return getcnt(t->l) + 1 + LTE(key, t->r);
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