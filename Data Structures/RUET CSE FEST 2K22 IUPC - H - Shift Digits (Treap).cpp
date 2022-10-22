#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define nl printf("\n");
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
#define si(x) scanf("%d",&x);
#define sii(x,y) scanf("%d%d",&x,&y);
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z);
#define sl(x) scanf("%lld",&x);
#define sll(x,y) scanf("%lld%lld",&x,&y);
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define FOR(i,j,n) for(int i=j; i<=n; i++)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;
const int MOD = 1e9+7;

int _pow10[N];

template<typename T>
struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		T mask,d;
		int val;
		data(){
			prior=rng();
			cnt=0;
			mask=0;
			val=0;
			d=0;
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
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->val = t->d;
			t->mask = (1<<t->d);
			if(t->l){
				t->val = (1LL*t->val + (10LL*t->l->val)%MOD)%MOD;
				t->mask |= t->l->mask;
			}
			if(t->r){
				t->val = ((1LL*t->val*_pow10[getcnt(t->r)])%MOD + 1LL*t->r->val)%MOD;
				t->mask |= t->r->mask;
			}
		}
	}
	
	void work(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		merge(root,l,r);
		merge(root,root,m);
	}
	
	int findLeft(int d){return findLeft(root,d);}
	int findRight(int d){return findRight(root,d);}
	inline bool check(data *t, int d){
		if(!t)return 0;
		return bool(t->mask&(1<<d));
	}
	
	int findLeft(data *t, int d, int add=0){
		if(check(t->l,d))return findLeft(t->l, d, add);
		if(t->d==d)return add+getcnt(t->l);
		return findLeft(t->r, d, 1+add+getcnt(t->l));
	}
	
	int findRight(data *t, int d, int add=0){
		if(check(t->r,d))return findRight(t->r, d, 1+add+getcnt(t->l));
		if(t->d==d)return add+getcnt(t->l);
		return findRight(t->l, d, add);
	}
	
	void append(T val){
		data *D = new data();
		D->val = val;
		D->d = val;
		D->mask =(1<<val);
		merge(root,root,D);
	}
	
	void erase(int index){erase(index,root);}
	void erase(int index, data* &t, int add=0){
		if(!t)return;
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
	
	void eraseD(data* &t, int d, int &cnt){
		if(!t)return;
		if(!check(t,d))return;
		eraseD(t->l, d, cnt);
		eraseD(t->r, d, cnt);
		if(t->d==d){
			cnt++;
			data *it = t;
			merge(t, t->l, t->r);
			delete it;
		}
		update_cnt(t);
	}
	
	T operator[](int index){return valAt(root,index,0);}
	T valAt(data *t, int key, int add){
		int curkey = getcnt(t->l)+add;
		if(key==curkey)return t->d;
		if(key<curkey)return valAt(t->l, key, add);
		return valAt(t->r, key, curkey+1);
	}
	
	void split(data *t, data* &l, data* &r, int key, int add=0){/// Subtree 'l' contains keys strictly less than 'key'
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


bool dDone[15];
char s[N];

void solve(int casenum){
	for(int i=0; i<=12; i++)dDone[i]=0;
	
	implicitTreap<int>T;
	sf("%s",&s);
	
	for(int i=0; s[i]; i++)T.append(int(s[i]-'0'));
	
	//dbug(T.root->val);
	int q,d;
	si(q);
	pf("Case %d:\n",casenum);
	
	while(q--){
		si(d);
		
		if(!dDone[d]){
			dDone[d]=1;
			int cnt=0;
			T.eraseD(T.root,d,cnt);
			while(cnt--)T.append(d);
		}
		
		
		int ans=0;
		if(T.empty())ans=0;
		else if(!bool(T.root->mask&(1<<d)))ans = T.root->val;
		else {
			T.work(T.findLeft(d),T.findRight(d));
			while(T.size()>1 && T[0]==0)T.erase(0);
			ans = T.root->val;
		}
		
		pf("%d\n",ans);
	}
}

int main(){
	_pow10[0]=1;
	for(int i=1; i<N; i++)_pow10[i] = (1LL*_pow10[i-1]*10LL)%MOD;
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}