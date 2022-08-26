///Sparse Li-Chao tree
///insert({m,c}) inserts line y = mx + c
///insertSegment({m,c}, l, r) inserts segment y = mx + c at points l<=x<=r
///query(x) returns minimum value at point x
///for max query set INF to negative, invert comparators in insert(), and change min to max in query()

template<typename T, const T _rangeL=int(-1e9), const T _rangeR=int(1e9), const T INF = LLONG_MAX>
struct LiChaoTree{
	struct Line{
		T m,c;
		Line(){m=0;c=INF;}
		Line(T a, T b):m(a),c(b){}
		T operator()(T x){return m*x + c;}
	};
 
	struct lctNode{
		Line seg;
		lctNode *L=NULL,*R=NULL;
		lctNode(){}
		lctNode(Line _l){seg = _l;}
	}*root=NULL;
 	
	T curlow,curhigh;

	LiChaoTree(){}
	~LiChaoTree(){if(root)destroyTree(root);}
	void destroyTree(lctNode *cur){
		if(!cur)return;
		if(cur->L)destroyTree(cur->L);
		if(cur->R)destroyTree(cur->R);
		delete cur;
	}
 
	void insertSegment(Line line, int l, int r){
		curlow = line(_rangeL);
		curhigh = line(_rangeR);
		root = insertSegment(line, _rangeL, _rangeR, l, r, root);
	}

	lctNode* insertSegment(Line line, int l, int r, int posl, int posr,  lctNode* cur){
		if(l>r || r<posl || l>posr)return cur;
		if(l>=posl && r<=posr)return insert(line, l, r, cur);
		if(cur){
			if(cur->seg(_rangeL)<=curlow && cur->seg(_rangeR)<=curhigh)return cur;
		}
		else cur = new lctNode();
		int mid = (l+r)>>1;
		cur->L = insertSegment(line, l, mid, posl, posr, cur->L);
		cur->R = insertSegment(line, mid+1, r, posl, posr, cur->R);
		return cur;
	}
 
	void insert(Line line){
		curlow = line(_rangeL);
		curhigh = line(_rangeR);
		root = insert(line, _rangeL, _rangeR, root);
	}

	lctNode* insert(Line line, int l, int r, lctNode *cur){
		if(!cur)return new lctNode(line);
		if(l==r){
			if(cur->seg(l) > line(l))cur->seg = line;
			return cur;
		}
		T thislow=cur->seg(_rangeL);
		T thisHigh=cur->seg(_rangeR);

		if(thislow <= curlow && thisHigh <= curhigh)return cur;
		if(thislow >= curlow && thisHigh >= curhigh){
			cur->seg = line;
			return cur;
		}

		int mid = (l+r)>>1;
		bool b1 = line(l) < cur->seg(l);
		bool b2 = line(mid) < cur->seg(mid);
		if(b2)swap(cur->seg,line);
		if(b1!=b2)cur->L = insert(line, l, mid, cur->L);
		else cur->R = insert(line, mid+1, r, cur->R);
		return cur;
	}
 
	T query(int x){return query(x,_rangeL, _rangeR, root);}
	T query(int x, int l, int r, lctNode *cur){
		if(!cur)return INF;
		if(l==r)return cur->seg(x);
		int mid = (l+r)>>1;
		if(x<=mid)return min(cur->seg(x), query(x, l, mid, cur->L));
		return min(cur->seg(x), query(x, mid+1, r, cur->R));
	}
};