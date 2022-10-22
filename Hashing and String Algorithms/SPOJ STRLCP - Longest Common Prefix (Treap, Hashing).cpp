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


const int N = 350005;
const int MOD = (1LL<<31)-1;
const int base1 = rand(1031,1<<22);
int P[N];
char s[100005];

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
		int H;
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
	inline int size(){return getcnt(root);}
	inline int getcnt(data *t){return t ? t->cnt:0;}
	
	
	inline void update_cnt(data *t){
		if(t){
			t->cnt = getcnt(t->l) + getcnt(t->r) + 1;
			t->H = t->val;
			if(t->l){
				t->H = mod(1LL*t->l->H + 1LL*mod(1LL*t->H * P[getcnt(t->l)]));
			}
			if(t->r){
				t->H = mod(1LL*t->H + 1LL*mod(1LL*t->r->H * P[getcnt(t->l)+1]));
			}
		}
	}
	
	int getHash(int L, int R){
		data *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		int H = m->H;
		merge(m,m,r);
		merge(root,l,m);
		return H;
	}
	
	void insert(int index, T val){
		data *d = new data();
		d->val=val;
		d->H=val;
		data *l,*r;
		split(root, l, r, index);
		merge(l,l,d);
		merge(root,l,r);
	}
	
	void replace(int index, T val){
		replace(root,index,val,0);
		// data *l,*r,*m;
		// split(root,l,m,index);
		// split(m,m,r,1);
		// m->val=val;
		// m->H=val;
		// merge(m,m,r);
		// merge(root,l,m);
	}
	
	void replace(data *t, int index, T val, int add=0){
		int curkey = add + getcnt(t->l);
		if(curkey==index){
			t->val=val;
			t->H=val;
		}
		else if(curkey>index)replace(t->l, index, val, add);
		else replace(t->r, index, val, curkey+1);
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
	sf(" %s",&s);
	implicitTreap<char> T;
	for(int i=0; s[i]; i++){
		T.insert(i,s[i]);
	}
	
	int q,l,r,qt,low,mid,high,ans;
	char c;
	si(q);
	while(q--){
		sf(" %c",&c);
		if(c=='Q'){
			sii(l,r);
			if(l==r)pf("%d\n",T.size()-l+1);
			else{
				l--,r--;
				high=min(T.size()-r, T.size()-l);
				low=1;
				ans=0;
				while(low<=high){
					mid = (low+high)>>1;
					if(T.getHash(l,l+mid-1) == T.getHash(r,r+mid-1)){
						ans=max(ans,mid);
						low=mid+1;
					}
					else high=mid-1;
				}
				pf("%d\n",ans);
			}
		}
		else if(c=='R'){
			sf("%d %c",&l,&c);
			T.replace(l-1,c);
		}
		else{
			sf("%d %c",&l,&c);
			T.insert(l,c);
		}
	}
	
}

int main(){
	P[0]=1;
	for(int i=1; i<N; i++)P[i]=mod(1LL*P[i-1]*base1);
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}