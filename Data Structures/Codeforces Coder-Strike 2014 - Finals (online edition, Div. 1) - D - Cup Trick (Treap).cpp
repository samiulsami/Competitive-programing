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
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e6+5;

int arr[N];
int rem[N]={0};

struct implicitTreap{///0 indexed
	struct data{
		data *l,*r;
		int prior,cnt;
		pii val;
		data(){
			prior=rand(INT_MIN,INT_MAX);
			cnt=0;
			l=r=NULL;
		}
	}*root;
	data Tree[N];
	int nodeCnt=0;
	
	implicitTreap(){root=NULL;}
	
	inline bool empty(){return getcnt(root)==0;}
	inline int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}
	
	inline void update_cnt(data *t){
		if(t)t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
	}
	
	void insert(){
		//insert(getcnt(root),val);
		data *d = &Tree[nodeCnt++];
		d->val=pii(-1,getcnt(root));
		d->l=NULL;
		d->r=NULL;
		d->cnt=0;
		merge(root,root,d);
	}
	
	bool work(int L, int val){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,1);
		if(m->val.first!=val && m->val.first!=-1)return 0;
		if(rem[val] && m->val.first!=val)return 0;
		rem[val]=1;
		m->val.first=val;
		merge(root,m,l);
		merge(root,root,r);
		return 1;
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
	
	void dfs(data *t){
		if(!t)return;
		dfs(t->l);
		arr[t->val.second]=t->val.first;
		dfs(t->r);
	}
}T;

void solve(int casenum){
	int n,m,x,y;
	sii(n,m);

	FOR(i,n)T.insert();
	while(m--){
		sii(x,y);
		//pf("%d at position %d\n",x,y);
		if(!T.work(y-1,x)){
			pf("-1\n");
			exit(0);
		}
	}
	
	T.dfs(T.root);
	int cnt=1;
	for(int i=0; i<n; i++){
		while(rem[cnt]==1)cnt++;
		if(arr[i]==-1){
			arr[i]=cnt;
			rem[cnt]=1;
		}
		pf("%d ",arr[i]);
	}
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