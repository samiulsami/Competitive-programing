struct segtree{
	#define T int
	T Tree[4*N];

	inline T Combine(T a, T b){
		return min(a,b);
	}

	void build(int node, int l, int r){
		if(l==r){
			///Tree[node]=arr[l-1];
		}
		else{
			int mid = (l+r)>>1;
			build(node<<1,l,mid);
			build(node<<1|1,mid+1,r);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=val;
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}
	
	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
	
	#undef T
}segtree;