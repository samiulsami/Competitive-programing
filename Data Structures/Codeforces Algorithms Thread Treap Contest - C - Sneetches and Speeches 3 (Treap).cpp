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


const int N = 3e5+5;
char s[N];

template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T val;
		bool xorflag;
		bool rev;
		bool rangepaint;
		bool paintval;
		int ans,pref,suff,first,last,total,ones,zeroes;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			rev=0;
			xorflag=0;
			rangepaint=0;
			ones=0;
			zeroes=0;
			total=0;
			ans=0;
			l=r=NULL;
		}
		void reset(){
			ans=1;
			total=1;
			pref=suff=1;
			ones = (val==1);
			zeroes = (val==0);
			rev=0;
			xorflag=0;
			rangepaint=0;
			first=last=val;
		}
		void invert(){
			val^=1;
			first^=1;
			last^=1;
			swap(ones,zeroes);
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
	
	inline void Combine(data *ret, data *L, data *R){
		int pref,suff,ans=1,first,last,total;
		first = L->first;
		last = R->last;
		total = L->total + R->total;
		pref = L->pref;
		suff = R->suff;
		
		if(L->last==R->first){
			ans=L->suff+R->pref;
			if(L->pref==L->total)pref = L->pref+R->pref;
			if(R->suff==R->total)suff = R->suff+L->suff;
		}
		
		ans=max({ans,L->ans,R->ans});
		
		ret->pref=pref;
		ret->suff=suff;
		ret->first=first;
		ret->last=last;
		ret->total=total;
		ret->ans=ans;
		int ones = L->ones + R->ones;
		int zeroes = L->zeroes + R->zeroes;
		ret->ones=ones;
		ret->zeroes=zeroes;
		//pf("%d %d %d %d %d %d %d %d\n",pref,suff,first,last,total,ones,zeroes,ans);
	}
	
	inline void update_cnt(data *t){
		if(t){
			push(t->l);
			push(t->r);
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->reset();
			if(t->l)Combine(t,t->l,t);
			if(t->r)Combine(t,t,t->r);
		}
	}

	void paintAll(data *t, bool val){
		t->ans=t->pref=t->suff=t->total;
		t->ones=t->zeroes=0;
		if(val)t->ones=t->total;
		else t->zeroes=t->total;
		t->first=t->last=val;
		t->val=val;
	}
	
	void setxorflag(data *t){
		if(!t)return;
		if(t->rangepaint){
			t->paintval^=1;
			t->xorflag=0;
		}
		else t->xorflag^=1;
	}
	
	void calcRev(data *t){
		if(t->rev){
			swap(t->first, t->last);
			swap(t->pref, t->suff);
			swap(t->l,t->r);
			if(t->l)t->l->rev^=1;
			if(t->r)t->r->rev^=1;
			t->rev=0;
		}
	}
	
	void setpaintflag(data *t, bool val){
		if(!t)return;
		t->xorflag=t->rev=0;
		t->rangepaint=1;
		t->paintval=val;
	}
	
	inline void push(data *t){///push down lazy values
		if(t){
			calcRev(t);
			
			if(t->rangepaint){
				paintAll(t,t->paintval);
				setpaintflag(t->l, t->paintval);
				setpaintflag(t->r, t->paintval);
				t->rangepaint=0;
				t->xorflag=0;
				t->rev=0;
			}
			else if(t->xorflag){
				t->invert();
				setxorflag(t->l);
				setxorflag(t->r);
				t->xorflag=0;
			}
		}
	}
	
	void query(int L, int R, bool flag=0){
		if(flag && L==R)return;
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		if(!flag)setxorflag(m);
		else m->rev^=1;
		merge(m,m,r);
		merge(root,l,m);
	}
	
	void query3(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);

		if(m->total == m->zeroes || m->total == m->ones){
			merge(m,m,r);
			merge(root,l,m);
		}
		else{
			data *LL,*RR;
			split(m, LL, RR, m->zeroes);
			
			setpaintflag(LL,0);
			setpaintflag(RR,1);
			
			merge(m,LL,RR);
			merge(m,m,r);
			merge(root,l,m);
		}
		
	}
	
	void insert(T val){
		data *d = new data();
		d->val=val;
		d->reset();
		merge(root,root,d);
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
	int n,q,l,r,qt;
	implicitTreap<bool> T;
	sii(n,q);
	sf(" %s",&s);
	for(int i=0; i<n; i++)T.insert(s[i]-'0');
	while(q--){
		siii(qt,l,r);
		if(qt==1)T.query(l-1,r-1,0);
		else if(qt==2)T.query(l-1,r-1,1);
		else T.query3(l-1,r-1);
		pf("%d\n",T.root->ans);
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