const int MOD = (1LL<<31)-1;
const int bases[2] = {(int)rand(1023,1<<22),(int)rand(1033,1<<22)};
const int _hashCnt=2;
int P[_hashCnt][N];
bool precalc=0;

inline int mod(ll x){
	if(x<MOD)return x;
	x+=MOD;
	x=(x>>31)+(x&MOD);
	return int((x>>31)+(x&MOD));
}

template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T val;
		int H[_hashCnt],R[_hashCnt];
		bool rev;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			rev=0;
			l=r=NULL;
		}
		void reset(){
			for(int i=0; i<_hashCnt; i++)
				H[i]=R[i]=val;
		}
	}*root;
	
	implicitTreap(){
		if(!precalc){
				precalc=1;
				for(int j=0; j<_hashCnt; j++){
					P[j][0]=1;
					for(int i=1; i<N; i++)P[j][i]=mod(1LL*P[j][i-1]*bases[j]);
				}
		}
		root=NULL;
	}
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
	
	void push(data *t){
		if(t && t->rev){
			swap(t->l,t->r);
			for(int i=0; i<_hashCnt; i++)
				swap(t->H[i],t->R[i]);
			if(t->l)t->l->rev^=1;
			if(t->r)t->r->rev^=1;
			t->rev=0;
		}
	}
	
	inline void update_cnt(data *t){
		if(t){
			push(t->l);
			push(t->r);
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->reset();
			if(t->l){
				for(int i=0; i<_hashCnt; i++){
					t->H[i] = mod(1LL*t->l->H[i] + 1LL*mod(1LL*t->H[i] * P[i][getcnt(t->l)]));
					t->R[i] = mod(1LL*t->R[i] + mod(1LL*t->l->R[i] * bases[i]));
				}
			}
			if(t->r){
				for(int i=0; i<_hashCnt; i++){
					t->H[i] = mod(1LL*t->H[i] + 1LL*mod(1LL*t->r->H[i] * P[i][getcnt(t->l)+1]));
					t->R[i] = mod(1LL*t->r->R[i] + 1LL*mod(1LL*t->R[i] * P[i][getcnt(t->r)]));
				}
			}
		}
	}
	
	bool isPalindrome(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		bool ret=1;
		for(int i=0; i<_hashCnt; i++)ret&=(m->H[i]==m->R[i]);
		merge(m,m,r);
		merge(root,l,m);
		return ret;
	}
	
	// void modification1(int i, int j, int k){
		// data *l,*r,*m;
		// split(root,l,m,i);
		// split(m,m,r,j-i+1);
		// merge(l,l,r);
		// split(l,l,r,k);
		// merge(l,l,m);
		// merge(root,l,r);
	// }
	
	void reverse(int L, int R){
		data *l, *r, *m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		m->rev^=1;
		merge(m,m,r);
		merge(root,l,m);
	}
	
	void append(T val){
		data *d = new data();
		d->val=val;
		d->reset();
		merge(root,root,d);
	}
	
	void insert(int index, T val){
		data *d = new data();
		d->val=val;
		d->reset();
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void replace(int index, T c){replace(root,index,c,0);}
	void replace(data *t, int ind, T c, int add=0){
		push(t);
		int curkey = add + getcnt(t->l);
		if(curkey==ind)t->val=t->H=t->R=c;
		else if(curkey<ind)replace(t->r, ind, c, curkey+1);
		else replace(t->l, ind, c, add);
		update_cnt(t);
	}
	
	void erase(int L, int R){erase(root, L, R, 0);}
	void erase(data* &t, int L, int R, int add){
		push(t);
		if(!t)return;
		int curkey = add+getcnt(t->l);
		if(curkey>=L && curkey<=R){
			erase(t->l, L, R, add);
			erase(t->r, L, R, curkey+1);
			data *tmp = t;
			merge(t,t->l,t->r);
			delete tmp;
		}
		else if(curkey<L)erase(t->r, L, R, curkey+1);
		else erase(t->l, L, R, add);
		update_cnt(t);
	}
	
	void split(data *t, data* &l, data* &r, int key, int add=0){
		push(t);
		if(!t)return void(l=r=NULL);
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
