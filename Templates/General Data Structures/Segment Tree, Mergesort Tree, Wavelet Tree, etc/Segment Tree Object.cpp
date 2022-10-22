template<typename T>
struct segtree{/// 0 indexed
	T *Tree=NULL;
	int n;
	function<T(T,T)> Combine;

	segtree(){}
	~segtree(){delete []Tree;}
	segtree(int x, T id, function<T(T,T)> _cmb):n(x){
		Combine = _cmb;
		Tree = new T[4*n];
		fill(Tree,Tree+4*n,id);
	}

	template<typename Iterator>
	segtree(Iterator l, Iterator r, function<T(T,T)> _cmb):segtree(vector<T>(l,r), _cmb){}
	segtree(const vector<T> &arr, function<T(T,T)> _cmb){
		Combine = _cmb;
		n = int(arr.size());
		Tree = new T[4*n];
		build(1,0,n-1,arr);
	}

	void build(int node, int l, int r, const vector<T> &arr){
		if(l==r)Tree[node] = arr[l];
		else{
			int mid = (l+r)>>1;
			build(node<<1, l, mid, arr);
			build(node<<1|1, mid+1, r, arr);
			Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
		}
	}

	void update(int pos, T val){update(1,0,n-1,pos,val);}
	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=Combine(Tree[node], val);
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	T query(int l, int r){return query(1,0,n-1,l,r);}
	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
};
