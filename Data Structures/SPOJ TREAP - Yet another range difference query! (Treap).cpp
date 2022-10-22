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

struct data{
	data *l,*r;
	int key,cnt,prior;
	int minval,maxval;
	int mindiff;
	data(){
		cnt=0;
		l=r=NULL;
		prior = rand(INT_MIN,INT_MAX);
	}
	void reset(){
		minval=maxval=key;
		mindiff=INT_MAX;
	}
}*root=NULL;

inline void Combine(data *t, data *l, data *r){
	t->mindiff = min({t->mindiff, abs(l->maxval - r->minval), l->mindiff, r->mindiff});
	t->maxval = r->maxval;
	t->minval = l->minval;
	//dbug(t->mindiff);
}

inline int getcnt(data *t){return t?t->cnt:0;}
inline void update_cnt(data *t){
	if(t){
		t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
		t->reset();
		if(t->l)Combine(t,t->l, t);
		if(t->r)Combine(t,t, t->r);
	}
}

///if x == 1, split by index
///if x == 0, split by value
void split(data *t, data* &l, data* &r, int key, int add, bool x){
	if(!t)return void(l=r=NULL);
	
		int curkey;
		if(x)curkey = getcnt(t->l) + add;
		else curkey = t->key;
		
		if(curkey<key)split(t->r, t->r, r, key, curkey+1, x), l=t;
		else split(t->l, l, t->l, key, add, x), r=t;
	
	update_cnt(t);
}


void merge(data* &t, data *l, data *r){
	if(!l || !r)t = l?l:r;
	else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
	else merge(r->l, l, r->l), t=r;
	update_cnt(t);
}

void insert(data* &t, data *u){
	if(!t)t=u;
	else if(u->prior > t->prior)split(t,u->l,u->r,u->key,0,0),t=u;
	else insert(t->key > u->key ? t->l: t->r, u);
	update_cnt(t);
}

bool count(data *t, int key){
	if(!t)return 0;
	if(t->key==key)return 1;
	else if(t->key<key)return count(t->r, key);
	return count(t->l,key);
}
bool count(int key){return count(root,key);}

void insert(int key){
	if(!count(key)){
		data *d = new data();
		d->key=key;
		d->reset();
		insert(root,d);
	}
}

void erase(data* &t, int key){
	if(!t)return;
	if(t->key==key){
		data *tmp = t;
		merge(t,t->l,t->r);
		delete tmp;
	}
	else if(t->key<key)erase(t->r, key);
	else erase(t->l, key);
	update_cnt(t);
}

void erase(int key){
	erase(root,key);
}

int query(int L, int R, char c){
	if(R<=L)return -1;
	data *l, *r, *m;
	split(root,l,m,L,0,1);
	split(m,m,r,R-L+1,0,1);
	int ret;
	if(c=='N')ret=m->mindiff;
	else ret = m->maxval - m->minval;
	merge(m,m,r);
	merge(root,l,m);
	return ret;
}

void solve(int casenum){
	int q,l,r,x;
	char c;
	si(q);
	while(q--){
		sf(" %c",&c);
		if(c=='I'){
			si(x);
			insert(x);
		}
		else if(c=='D'){
			si(x);
			erase(x);
		}
		else{
			sii(l,r);
			pf("%d\n",query(l,r,c));
		}
		//dbug(getcnt(root));
	}
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