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

const int MOD = (1LL<<31)-1;
const int base1 = rand(1031,1<<22);
int P[N];
char s[N];
bool precalc=0;

inline int mod(ll x){
	if(x<MOD)return x;
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return (x>>31)+(x&MOD);
}

template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T val;
		int H,R;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			l=r=NULL;
		}
	}*root;

	
	implicitTreap(){
		if(!precalc){
				precalc=1;
				P[0]=1;
				for(int i=1; i<N; i++)P[i]=mod(1LL*P[i-1]*base1);
		}
		root=NULL;
	}
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
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->H = t->val;
			t->R = t->val;
			if(t->l){
				t->H = mod(1LL*t->l->H + 1LL*mod(1LL*t->H * P[getcnt(t->l)]));
				t->R = mod(1LL*t->R + mod(1LL*t->l->R * base1));
			}
			if(t->r){
				t->H = mod(1LL*t->H + 1LL*mod(1LL*t->r->H * P[getcnt(t->l)+1]));
				t->R = mod(1LL*t->r->R + 1LL*mod(1LL*t->R * P[getcnt(t->r)]));
			}
		}
	}
	
	bool isPalindrome(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		bool ret = bool(m->H == m->R);
		merge(m,m,r);
		merge(root,l,m);
		return ret;
	}
	
	void insert(int index, T val){
		data *d = new data();
		d->val=val;
		d->H=val;
		d->R=val;
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void erase(int L){
		erase(root, L, 0);
	}
	
	void erase(data* &t, int L, int add){
		if(!t)return;
		int curkey = add+getcnt(t->l);
		if(curkey==L){
			data *tmp = t;
			merge(t,t->l,t->r);
			delete tmp;
		}
		else if(curkey<L)erase(t->r, L, curkey+1);
		else erase(t->l, L, add);
		update_cnt(t);
	}
	
	void replace(int index, char c){
		replace(root,index,c,0);
	}
	
	void replace(data *t, int ind, char c, int add=0){
		int curkey = add + getcnt(t->l);
		if(curkey==ind)t->val=t->H=t->R=c;
		else if(curkey<ind)replace(t->r, ind, c, curkey+1);
		else replace(t->l, ind, c, add);
		update_cnt(t);
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
};

void solve(int casenum){
	sf("%s",&s);
	implicitTreap<char> T;
	int q,l,r;
	char c;
	for(int i=0; s[i]; i++)T.insert(i,s[i]);
	
	si(q);
	while(q--){
		sf(" %c",&c);
		if(c=='C'){
			sii(l,r);
			if(T.isPalindrome(l-1,r-1))pf("Yes!\n");
			else pf("No!\n");
		}
		else if(c=='D'){
			si(l);
			T.erase(l-1);
		}
		else{
			sf("%d %c",&l,&c);
			T.replace(l-1,c);
		}
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