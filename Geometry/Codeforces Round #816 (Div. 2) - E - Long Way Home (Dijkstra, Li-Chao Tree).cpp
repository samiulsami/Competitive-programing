#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;
vector<pii(2)>graph[N];
ll dist[N];

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

inline void solve(int caseNum){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=0,u,v,w; i<m; i++){
		cin>>u>>v>>w;
		graph[u].push_back({w,v});
		graph[v].push_back({w,u});
	}

	for(int i=1; i<=n; i++)dist[i] = -1;
	dist[1]=0;
	
	priority_queue<array<ll,2>,vector<array<ll,2> >,greater<array<ll,2>> >pq;

	auto dijkstra = [&]()->void{
		while(!pq.empty()){
			auto top = pq.top();
			pq.pop();
			int u = top[1];
			ll w = top[0];
			if(dist[u]<w)continue;

			for(auto &e:graph[u]){
				int v = e[1];
				ll vw = e[0];
				if(dist[v]==-1 || dist[v]>(w+vw)){
					dist[v]=w+vw;
					pq.push({dist[v],v});
				}
			}
		}
	};

	pq.push({dist[1],1});
	dijkstra();

	while(k--){
		LiChaoTree<ll,0LL,int(1e5),LLONG_MAX> lct;

		lct.insert({-2,1});
		for(int i=2; i<=n; i++){
			if(dist[i]!=-1)lct.insert({-2LL*i, 1LL*i*i + dist[i]});
		}

		pq.push({dist[1],1});
		for(int i=2; i<=n; i++){
			ll cur = 1LL*i*i + lct.query(i);
			if(dist[i]==-1 || dist[i]>cur){
				dist[i]=cur;
				pq.push({dist[i],i});
			}
		}

		dijkstra();
	}

	for(int i=1; i<=n; i++)cout<<dist[i]<<" ";
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