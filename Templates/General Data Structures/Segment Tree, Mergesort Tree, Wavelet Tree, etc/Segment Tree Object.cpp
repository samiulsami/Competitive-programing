template<typename T>
struct segtree{/// 1 indexed
	vector<T>Tree;
	int n;
	function<T(T,T)> Combine;

	segtree(){}
	segtree(int x, function<T(T,T)> _cmb):n(x),Tree(4*x){Combine = _cmb;}
	segtree(const vector<T> &arr, function<T(T,T)> _cmb){
		Combine = _cmb;
		n = int(arr.size());
		Tree.resize(4*n);
		build(1,1,n,arr);
	}

	void build(int node, int l, int r, const vector<T> &arr){
		if(l==r)Tree[node] = arr[l-1];
		else{
			int mid = (l+r)>>1;
			build(node<<1, l, mid, arr);
			build(node<<1|1, mid+1, r, arr);
			Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
		}
	}

	void update(int pos, T val){update(1,1,n,pos,val);}
	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=val;
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	T query(int l, int r){return query(1,1,n,l,r);}
	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}

	int Find(int node, int l, int r){
		if(l==r)return l;
		int mid = (l+r)>>1;
		if(Tree[node<<1][0] <= Tree[1][1])return Find(node<<1, l, mid);
		return Find(node<<1|1, mid+1, r);
	}
};