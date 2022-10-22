const int _rangeL=-1e5;
const int _rangeR=1e5;
const ll INF = LLONG_MAX;

struct Line{
	ll m,c;
	Line(){m=0;c=INF;}
	Line(ll a, ll b):m(a),c(b){}
	ll operator()(ll x){return m*x + c;}
};
 
struct lctNode{
	Line seg;
	lctNode *L=NULL,*R=NULL;
	lctNode(){}
	lctNode(Line _l){seg = _l;}
};
 	
ll curlow,curhigh;
 	
 void _del(lctNode *root){
 	if(!root)return;
 	if(root->L)_del(root->L);
 	if(root->R)_del(root->R);
 	delete root;
 }	

lctNode* insert(Line line, int l, int r, lctNode *cur){
	if(!cur)return new lctNode(line);
	if(l==r){
		if(cur->seg(l) > line(l))cur->seg = line;
		return cur;
	}
	ll thislow=cur->seg(_rangeL);
	ll thisHigh=cur->seg(_rangeR);

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
	 
void insert(Line line, lctNode *root){
	curlow = line(_rangeL);
	curhigh = line(_rangeR);
	root = insert(line, _rangeL, _rangeR, root);
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

void insertSegment(Line line, int l, int r, lctNode *root){
	curlow = line(_rangeL);
	curhigh = line(_rangeR);
	root = insertSegment(line, _rangeL, _rangeR, l, r, root);
}
 
ll query(int x, int l, int r, lctNode *cur){
	if(!cur)return INF;
	if(l==r)return cur->seg(x);
	int mid = (l+r)>>1;
	if(x<=mid)return min(cur->seg(x), query(x, l, mid, cur->L));
	return min(cur->seg(x), query(x, mid+1, r, cur->R));
}

ll query(int x, lctNode *root){return query(x,_rangeL, _rangeR, root);}

void merge(lctNode *a, lctNode *b){
	if(!b)return;
	insert(b->seg, a);
	if(b->L)merge(a, b->L);
	if(b->R)merge(a, b->R);
}
