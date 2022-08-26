///Sparse Li-Chao tree
///insert({m,c}) inserts line y = mx + c
///insertSegment({m,c}, l, r) inserts segment y = mx + c at points l<=x<=r
///query(x) returns minimum value at point x
///for max query set INF to negative, invert comparators in insert(), and change min to max in query()
const int64_t INF = LLONG_MAX;
const int64_t _rangeL=0, _rangeR = 1e6+5;
const int MaxNodes = 1e6+20; ///~log2(|range|)*(number of queries/insertions)

template<typename T>
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

	//lctNode *Tree=NULL;
	int nodecnt=0;

	lctNode* newlctNode(Line l){
		// Tree[nodecnt] = lctNode(l);
		// return &Tree[nodecnt++];
		lctNode *tmp = new lctNode(l);
		return tmp;
	}

	LiChaoTree(){
		//Tree = new lctNode[MaxNodes];
		root = newlctNode({0,INF});
	}
	~LiChaoTree(){
		//if(Tree)delete []Tree;
		destroyTree(root);
	}
	void destroyTree(lctNode *cur){
		if(!cur)return;
		if(cur->L)destroyTree(cur->L);
		if(cur->R)destroyTree(cur->R);
		delete cur;
	}

	void insertSegment(Line line, int l, int r){insertSegment(line, _rangeL, _rangeR, l, r, root);}
	void insertSegment(Line line, int l, int r, int posl, int posr,  lctNode *cur){
		if(l>r || r<posl || l>posr)return;
		if(l>=posl && r<=posr){
			insert(line, l, r, cur);
			return;
		}
		if(!cur->L)cur->L = newlctNode(cur->seg);
		if(!cur->R)cur->R = newlctNode(cur->seg);
		int mid = (l+r)>>1;
		insertSegment(line, l, mid, posl, posr, cur->L);
		insertSegment(line, mid+1, r, posl, posr, cur->R);
	}

	void insert(Line line){insert(line, _rangeL, _rangeR, root);}
	void insert(Line line, int l, int r, lctNode *cur){
		if(l==r){
			if(cur->seg(l) > line(l))cur->seg = line;
			return;
		}
		int mid = (l+r)>>1;
		if(cur->seg.m < line.m)swap(cur->seg,line);
		if(cur->seg(mid) > line(mid)){
			swap(cur->seg, line);
			if(cur->L)insert(line, l, mid, cur->L);
			else cur->L = newlctNode(line);
		}
		else if(cur->R)insert(line, mid+1, r, cur->R);
		else cur->R = newlctNode(line);
	}

	T query(int x){return query(x,_rangeL, _rangeR, root);}
	T query(int x, int l, int r, lctNode *cur){
		if(l==r)return cur->seg(x);
		int mid = (l+r)>>1;
		if(x<=mid && cur->L)return min(cur->seg(x), query(x, l, mid, cur->L));
		else if(cur->R)return min(cur->seg(x), query(x, mid+1, r, cur->R));
		return cur->seg(x);
	}
};