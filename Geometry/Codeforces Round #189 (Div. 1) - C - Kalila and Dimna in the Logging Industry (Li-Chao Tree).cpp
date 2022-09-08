#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;

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
		// T thislow=cur->seg(_rangeL);
		// T thisHigh=cur->seg(_rangeR);

		// if(thislow <= curlow && thisHigh <= curhigh)return cur;
		// if(thislow >= curlow && thisHigh >= curhigh){
		// 	cur->seg = line;
		// 	return cur;
		// }

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

int a[N];
int b[N];

inline void solve(int caseNum){
	int n;
	cin>>n;
	for(int i=0; i<n; i++)cin>>a[i];
	for(int i=0; i<n; i++)cin>>b[i];

	LiChaoTree<ll,0,int(1e9)>lct;
	lct.insert({b[0],0});

	for(int i=1; i<n; i++){
		ll cur = lct.query(a[i]);
		lct.insert({b[i], cur});
		if(i==n-1){
			cout<<cur;
		}
	}
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