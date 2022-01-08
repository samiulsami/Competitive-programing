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

 
inline int get(char c){
	if(c>='a' && c<='z')return (int)c-'a';
	if(c>='A' && c<='Z')return (int)c-'A'+26;
	return (int)c-'0'+52;
}

struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		char c;
		ll val;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
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
	int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}

	inline void update_cnt(data *t){
		if(t){
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->val = 1LL<<get(t->c);
			if(t->l)t->val |= t->l->val;
			if(t->r)t->val |= t->r->val;
		}
	}
	
	void work(data* &t, int add, int c){
		if(!t)return;
		if(!bool(t->val&(1LL<<c)))return;
		work(t->l, add, c);
		work(t->r, add+getcnt(t->l)+1, c);
		if(get(t->c)==c){
			data *tmp = t;
			merge(t,t->l,t->r);
			if(tmp!=NULL)delete tmp;
		}
		update_cnt(t);
	}
	
	void query(int L, int R, char c){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		work(m,L,get(c));
		merge(root,l,m);
		merge(root,root,r);
	}
	
	void insert(int val){insert(getcnt(root),val);}
	void insert(int index, char c){
		data *d = new data();
		d->c=c;
		d->val = (1LL<<get(c));
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
		update_cnt(root);
	}
	
	void split(data *t, data* &l, data* &r, int key, int add=0){
		if(!t)return void(l=r=NULL);
		int cur=add+getcnt(t->l);
		if(key<=cur)split(t->l, l, t->l, key, add), r=t;
		else split(t->r, t->r, r, key, cur+1), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
	
	void print(data *t){
		if(!t)return;
		print(t->l);
		pf("%c",t->c);
		print(t->r);
	}
};
char s[int(2e5+5)];

void solve(int casenum){
	int n,m,l,r;
	char c;
	sii(n,m);
	sf("%s",&s);
	
	implicitTreap T;
	//pf("%s",s);
	for(int i=0; i<n; i++){
		T.insert(i,s[i]);
	}
	
	while(m--){
		sf("%d%d %c",&l,&r,&c);
		//pf("%d %d %c\n",l,r,c);
		l--,r--;
		T.query(l,r,c);
	}
	//dbug(T.size());
	T.print(T.root);
	nl;
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