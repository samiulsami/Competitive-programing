///insert({m,c}) inserts line y = mx + c
///query(x) returns minimum value at point x
///for max query set INF to negative, invert comparators in insert(), and change min to max in query()
const int64_t INF = LLONG_MAX;
const int64_t _range=1e6;

struct Line{
	int64_t m,c;
	Line(){m=0;c=INF;}
	Line(int64_t a, int64_t b):m(a),c(b){}
	int64_t operator()(int64_t x){return m*x + c;}
}Tree[4*_range];

void insert(Line line, int l=0, int r=_range, int node=1){
	if(l==r){
		if(Tree[node](l) > line(l))Tree[node] = line;
		return;
	}
	int mid = (l+r)>>1;
	if(Tree[node].m < line.m)swap(Tree[node],line);
	if(Tree[node](mid) > line(mid)){
		swap(Tree[node], line);
		insert(line, l, mid, node<<1);
	}
	else insert(line, mid+1, r, node<<1|1);
}

int64_t query(int x, int l=0, int r=_range, int node=1){
	if(l==r)return Tree[node](x);
	int mid = (l+r)>>1;
	if(x<mid)return min(Tree[node](x), query(x, l, mid, node<<1));
	return min(Tree[node](x), query(x, mid+1, r, node<<1|1));
}