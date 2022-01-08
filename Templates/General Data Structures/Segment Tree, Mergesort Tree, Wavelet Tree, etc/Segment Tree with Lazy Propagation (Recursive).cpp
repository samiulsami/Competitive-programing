struct segtree{
	#define T ll
	T Tree[4*N];
	T Lazy[4*N];
	bool mark[4*N];
	
	inline T Combine(T a, T b){
		return a+b;
	}

	void build(int node, int l, int r){
		mark[node]=0;
		Lazy[node]=0;
		Tree[node]=0;
		if(l==r){
		}
		else{
			int mid = (l+r)>>1;
			build(node<<1,l,mid);
			build(node<<1|1,mid+1,r);
		}
	}
	
	void push_update(int node, int l, int r){
		if(mark[node]){
			Tree[node] += 1LL*(r-l+1)*Lazy[node];
			if(l^r){
				Lazy[node<<1]+=Lazy[node];
				Lazy[node<<1|1]+=Lazy[node];
				mark[node<<1]=1;
				mark[node<<1|1]=1;
			}
			Lazy[node]=0;
			mark[node]=0;
		}
	}

	void update(int node, int l, int r, int posl, int posr, T val){
		push_update(node,l,r);
		if(l>r || posr<l || r<posl)return;
		if(l>=posl && r<=posr){
			mark[node]=1;
			Lazy[node]+=val;
			push_update(node,l,r);
		}
		else{
			int mid = (l+r)>>1;
			update(node<<1,l,mid,posl,posr,val);
			update(node<<1|1,mid+1,r,posl,posr,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}
	
	T query(int node, int l, int r, int posl, int posr){
		push_update(node,l,r);
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
	
	#undef T
}segtree;