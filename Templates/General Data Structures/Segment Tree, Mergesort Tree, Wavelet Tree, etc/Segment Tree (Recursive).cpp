template<typename T>
struct segTree{
    vector<T>Tree;
	T defaultval;
	function <T(T,T)>Combine;
    int n;
    segTree(int n, T defaultval, function <T(T,T)> func):n(n),defaultval(defaultval),Tree(4*n),Combine(func){}
	
    inline void build(){build(1,1,n);}
    void build(int node, int l, int r){
        if(l==r)Tree[node]=defaultval;
        else{
            int mid = (l+r)>>1;
            build(node<<1,l,mid);
            build(node<<1|1,mid+1,r);
            Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
        }
    }

    inline void update(int pos, T val){assert(pos<=n && pos>=1);update(1,1,n,pos,val);}
    void update(int node, int l, int r, int pos, T val){
        if(l==pos && r==pos)Tree[node]+=val;
        else{
            int mid = (l+r)>>1;
            if(pos<=mid)update(node<<1, l, mid, pos, val);
            else update(node<<1|1, mid+1, r, pos, val);
            Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
        }
    }

    inline T query(int posl, int posr){assert(posl<=posr && posl>=1 && posr<=n);return query(1,1,n,posl,posr);}
    T query(int node, int l, int r, int posl, int posr){
        if(l>=posl && r<=posr)return Tree[node];
        int mid = (l+r)>>1;
        if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr);
        if(posr<=mid)return query(node<<1, l, mid, posl, posr);
        return Combine(query(node<<1, l, mid, posl, posr), query(node<<1|1, mid+1, r, posl, posr));
    }
};