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


const int N = 5e5+5;
struct data{
		data *l,*r,*p;
		int prior,cnt;
		int val;
		ll sum;
		bool rev;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			rev=0;
			l=r=p=NULL;
		}
};
	
data *ptrs[N];

template<typename T>
struct implicitTreap{///0 indexed
	
	implicitTreap(){}
	

	inline int getcnt(data *t){return t ? t->cnt:0;}
	ll getsum(data *t){
		if(t)return t->sum;
		return 0;
	}
	inline void update_cnt(data *t){
		if(t){
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->sum = getsum(t->l) + getsum(t->r) + t->val;
			t->p = NULL;
			if(t->l)t->l->p = t;
			if(t->r)t->r->p = t;
		}
	}
		
	data *getRoot(data *t){
		if(!t->p)return t;
		return getRoot(t->p);
	}

	void query1(int ind, int val){
		//insert(getcnt(root),val);
		data *d = new data();
		d->val=val;
		d->sum=val;
		d->p=NULL;
		ptrs[ind]=d;
	}
	
	void query2(int y, int z){
		data *l=getRoot(ptrs[y]);
		data *r=getRoot(ptrs[z]);
		if(l!=r)merge(l,l,r);
	}
	
	void query3(int y, int z){
		if(getcnt(getRoot(ptrs[y]))<=z)return;
		data *l = getRoot(ptrs[y]),*d,*dd;
		split(l,d,dd,z);
	}
	
	ll query4(int y){
		return getsum(getRoot(ptrs[y]));
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
	implicitTreap<int> T;
	int n,a,b,c;
	si(n);
	for(int i=1; i<=n; i++){
		si(a);
		if(a==1){
			si(a);
			T.query1(i,a);
		}
		else if(a==2){
			sii(b,c);
			T.query2(b,c);
		}
		else if(a==3){
			sii(b,c);
			T.query3(b,c);
		}
		else{
			si(a);
			pf("%lld\n",T.query4(a));
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