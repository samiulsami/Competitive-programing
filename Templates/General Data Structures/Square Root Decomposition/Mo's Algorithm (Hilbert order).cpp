
const int N=1e6+5;
const int Div=1000;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

/// k=ceil(log2(n));
/// for each interval[l,r], x = hilbertOrder(l,r,k,0);

struct query{
    int ind,l,r;
    int64_t x;
    query(){}
    query(int ind, int l, int r):ind(ind),l(l),r(r){}
    bool operator<(const query &q)const{
        return x<q.x;
    }
}queries[N];


