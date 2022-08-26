#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

///Implicit Li-Chao tree
///insert({m,c}) inserts line y = mx + c
///query(x) returns minimum value at point x
///for max query set INF to negative, invert comparators in insert(), and change min to max in query()
const int64_t INF = LLONG_MAX;
const int64_t _rangeL=0, _rangeR = 1e6;

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

	LiChaoTree(){root = new lctNode();}
	~LiChaoTree(){destroyTree(root);}
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
		if(!cur->L)cur->L = new lctNode();
		if(!cur->R)cur->R = new lctNode();
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
			else cur->L = new lctNode(line);
		}
		else if(cur->R)insert(line, mid+1, r, cur->R);
		else cur->R = new lctNode(line);
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

inline void solve(int caseNum){
	ll n,c;
	cin>>n>>c;

	LiChaoTree<ll> lct;
	ll dp=0,h;
	for(int i=0; i<n; i++){
		cin>>h;
		if(i)dp = h*h + c + lct.query(h);
		lct.insertSegment({-2LL*h, (dp+h*h)}, _rangeL, _rangeR);
	}

	 cout<<dp;
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}