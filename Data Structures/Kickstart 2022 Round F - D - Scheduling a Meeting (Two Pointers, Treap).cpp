#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

template<typename T>
struct Treap{///0 indexed
	struct data{
		data *l=NULL,*r=NULL;
		int prior=rand(INT_MIN,INT_MAX),cnt=0;
		T key;
		int sum;
		data(){sum=0;}
	}*root=NULL;
	
	Treap(){root=NULL;}
	~Treap(){destroyTree(root);}
	
	void destroyTree(data *t){
		if(!t)return;
		if(t->l)destroyTree(t->l);
		if(t->r)destroyTree(t->r);
		delete t;
	}
	
	inline bool empty(){return getcnt(root)==0;}
	int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}

	inline void update_cnt(data *t){
		if(t){
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->sum = t->key.first;
			if(t->l)t->sum += t->l->sum;
			if(t->r)t->sum += t->r->sum;
		}
	}
	
	void insert(T val){
		data *d = new data();
		d->key=val;
		d->sum=val.first;
		insert(root,d);
	}
	
	void insert(data* &t, data *u){
		if(!t)t=u;
		else if(u->prior > t->prior)split(t, u->l, u->r, u->key), t=u;
		else insert(t->key <= u->key ? t->r : t->l, u);
		update_cnt(t);
	}
	
	void erase(T val){erase(val,root);}
	void erase(T key, data* &t){
		if(!t)return;
		if(t->key==key){
			data *it = t;
			merge(t, t->l, t->r);
			delete it;
		}
		else erase(key, key < t->key ? t->l: t->r);
		update_cnt(t);
	}
	
	int kth(int k){return kth(k,root);}
	int kth(int k, data *t){///total number of meetings of k+1 tech leads with the least number of meetings
		if(!t)return 0;
		if(getcnt(t->l)==k){
			int ret = t->key.first;
			if(t->l)ret += t->l->sum;
			return ret;
		}
		if(getcnt(t->l)>k)return kth(k, t->l);
		int ret = t->key.first;
		if(t->l)ret += t->l->sum;
		return ret + kth(k-getcnt(t->l)-1, t->r);
	}
	
	void split(data *t, data* &l, data* &r, T key){/// Subtree 'l' contains keys strictly less than 'key'
		if(!t)return void(l=r=NULL);
		if(key<=t->key)split(t->l, l, t->l, key), r=t;
		else split(t->r, t->r, r, key), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
};

vector<int>starts[N],_ends[N];

inline void solve(int caseNum){
	int n,k,x,d;
	cin>>n>>k>>x>>d;
	int m;
	cin>>m;

	for(int i=0,p,l,r; i<m; i++){
		cin>>p>>l>>r;
		starts[l].push_back(p-1);
		_ends[r].push_back(p-1);
	}

	Treap<pair<int,int> >T;
	vector<int>cnt(n+1,0);
	int ans = m;

	auto add = [&](int ind)->void{
		vector<int>tmp;
		for(int x:starts[ind])
			tmp.push_back(x);

		sort(all(tmp));
		tmp.erase(unique(all(tmp)), tmp.end());
		for(int x:tmp)
			if(cnt[x]>0)T.erase({cnt[x],x});

		for(int x:starts[ind])cnt[x]++;
		for(int x:tmp)T.insert({cnt[x],x});
	};

	auto rem = [&](int ind)->void{
		vector<int>tmp;
		for(int x:_ends[ind])
			tmp.push_back(x);

		sort(all(tmp));
		tmp.erase(unique(all(tmp)), tmp.end());

		for(int x:tmp)
			if(cnt[x]){
				T.erase({cnt[x],x});
			}

		for(int x:_ends[ind])cnt[x]--;
		for(int x:tmp)if(cnt[x])T.insert({cnt[x],x});
	};
	

	for(int i=0; i<x; i++)add(i);
	for(int i=x; i<=d; i++){
		rem(i-x);
		if((n-T.size())>=k){
			ans=0;
		}
		else{
			int req = k-(n-T.size());
			int xd = T.kth(req-1);
			ans = min(ans, xd);
		}
		add(i);
	}

	cout<<"Case #"<<caseNum<<": "<<ans<<"\n";
	for(int i=0; i<=d; i++){
		starts[i].clear();
		_ends[i].clear();
	}
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}