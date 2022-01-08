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


#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

int get(char c){
	if(c>='a' && c<='z')return c-'a';
	return c-'A';
}

template<typename T>
struct Treap{
	struct data{
		data *l=NULL,*r=NULL;
		int prior=rand(INT_MIN,INT_MAX),cnt=0;
		T key;
		data(){}
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
	inline void update_cnt(data *t){if(t)t->cnt = getcnt(t->l) + getcnt(t->r) + 1;}
	
	
	void insert(T val){
		//if(!count(val)){
			data *d = new data();
			d->key=val;
			insert(root,d);
		//}
	}
	
	void insert(data* &t, data *u){
		if(!t)t=u;
		else if(u->prior > t->prior)split(t, u->l, u->r, u->key), t=u;
		else insert(t->key <= u->key ? t->r : t->l, u);
		update_cnt(t);
	}
	
	int getans(int L, int R){
		data *l, *r, *m;
		split(root,l,m,L);
		split(m,m,r,R+1);
		int ret=getcnt(m);
		merge(m,m,r);
		merge(root,l,m);
		return ret;
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

void solve(int casenum){
	Treap<int>st[26];
	int n,m;
	string s;
	cin>>n>>m>>s;
	for(int i=0; i<n; i++)st[get(s[i])].insert(i);
	
	int qt,l,r;
	char c;
	while(m--){
		cin>>qt;
		if(qt==1){
			cin>>l>>c;
			st[get(s[l-1])].erase(l-1);
			st[get(c)].insert(l-1);
			s[l-1]=c;
		}
		else{
			cin>>l>>r>>c;
			cout<<st[get(c)].getans(l-1,r-1)<<"\n";
		}
	}
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}