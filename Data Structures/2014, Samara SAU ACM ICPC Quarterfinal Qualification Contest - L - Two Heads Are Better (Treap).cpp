#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T val;
		bool rev;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			rev=0;
			l=r=NULL;
		}
	}*root;
	
	implicitTreap(){root=NULL;}
	~implicitTreap(){destroyTree(root);}
	
	void destroyTree(data *t){
		if(!t)return;
		if(t->l)destroyTree(t->l);
		if(t->r)destroyTree(t->r);
		delete t;
	}
	
	inline bool empty(){return getcnt(root)==0;}
	inline int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}
	
	inline void update_cnt(data *t){
		if(t){
			push(t->l);
			push(t->r);
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
		}
	}
		
	void propagate(data *t, data *u){
		if(u)u->rev^=1;
	}		
	
	inline void push(data *t){///push down lazy values
		if(t && t->rev){
			swap(t->l, t->r);
			propagate(t,t->l);
			propagate(t,t->r);
			t->rev=0;
		}
	}
	
	void reverse(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		m->rev^=1;
		merge(root,l,m);
		merge(root,root,r);
	}
	
	void cyclic_shiftR(int L, int R){///right shift
		data *l,*r,*m,*rr;
		split(root,l,m,L);
		split(m,m,r,R-L);
		split(r,rr,r,1);
		merge(m,m,r);
		merge(rr,rr,m);
		merge(root,l,rr);
	}
	
	void cyclic_shiftL(int L, int R){///left shift
		data *l,*r,*m,*ll;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		split(m,ll,m,1);
		merge(m,m,ll);
		merge(m,m,r);
		merge(root,l,m);
	}
	
	T at(int index){return valAt(root,index,0);}
	T valAt(data *t, int key, int add){
		push(t);
		int curkey = getcnt(t->l)+add;
		if(key==curkey)return t->val;
		if(key<curkey)return valAt(t->l, key, add);
		return valAt(t->r, key, curkey+1);
	}
	
	void insert(T val){
		//insert(getcnt(root),val);
		data *d = new data();
		d->val=val;
		merge(root,root,d);
	}
	
	void insert(int index, T val){
		data *d = new data();
		d->val=val;
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void erase(int index){erase(index,root);}
	void erase(int index, data* &t, int add=0){
		if(!t)return;
		push(t);
		int curkey = getcnt(t->l)+add;
		if(curkey==index){
			data *it = t;
			merge(t, t->l, t->r);
			delete it;
		}
		else if(curkey>index)erase(index, t->l, add);
		else erase(index, t->r, curkey+1);
		update_cnt(t);
	}
	
	void split(data *t, data* &l, data* &r, int key, int add=0){
		if(!t)return void(l=r=NULL);
		push(t);
		int cur=add+getcnt(t->l);
		if(key<=cur)split(t->l, l, t->l, key, add), r=t;
		else split(t->r, t->r, r, key, cur+1), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		push(l);
		push(r);
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
};


void solve(int casenum){
	implicitTreap<char> T;
	int n,l,r;
	cin>>n>>l>>r;
	l--,r--;
	string s,out;
	cin>>s;
	for(char &c:s)T.insert(c);
	
	int m;
	cin>>m;
	char c,x,y;
	while(m--){
		cin>>c;
		if(c=='S'){
			cin>>x>>y;
			if(x=='L')l+=(y=='L'?-1:1);
			else r+=(y=='L'?-1:1);
		}
		else if(c=='R'){
			if(l!=r)T.reverse(min(l,r),max(l,r));
		}
		else{
			cin>>x;
			out+=T.at((x=='L')?l:r);
		}
	}
	
	cout<<out<<endl;
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}