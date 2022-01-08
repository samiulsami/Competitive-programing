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
struct Treap{
	struct data{
		data *l,*r;
		int cnt,prior;
		T key;
		data(){
			prior = rand(INT_MIN,INT_MAX);
			cnt=0;
			l=r=NULL;
		}
	};
	data *root;
	Treap(){root=NULL;}
	
	int getcnt(data *t){return t?t->cnt:0;}
	void update_cnt(data *t){if(t)t->cnt = getcnt(t->l) + getcnt(t->r)+1;}
	
	void insert(T key){
		if(count(key))return;
		data *d = new data();
		d->key=key;
		insert(root,d);
	}
	
	void insert(data* &t, data *d){
		if(!t)t=d;
		else if(d->prior > t->prior)split(t,d->l,d->r,d->key), t=d;
		else if(d->key < t->key)insert(t->l, d);
		else insert(t->r, d);
		update_cnt(t);
	}
	
	int query(int L, int R){
		data *l, *r, *m;
		split(root,l,m,L);
		split(m,m,r,R+1);
		int ret = getcnt(m);
		merge(m,m,r);
		merge(root,l,m);
		return ret;
	}
	
	void split(data *t, data* &l, data* &r, int key){
		if(!t)return void(l=r=NULL);
		if(t->key >= key)split(t->l, l, t->l, key), r=t;
		else split(t->r, t->r, r, key), l=t;
		update_cnt(t);
	}
	
	void merge(data* &t, data *l, data *r){
		if(!l || !r)t = l?l:r;
		else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
		else merge(r->l, l, r->l), t=r;
		update_cnt(t);
	}
	
	bool count(T val){return count(val,root);}
	bool count(T key, data *t){///Check if key exists in tree
		if(!t)return 0;
		if(t->key==key)return 1;
		if(t->key<key)return count(key,t->r);
		return count(key,t->l);
	}
};

struct nodeA{
	int x,r,f;
}arr[100005];

vector<pii> arr2[10005];

void solve(int casenum){
	int n,k;
	sii(n,k);
	FOR(i,n){
		siii(arr[i].x, arr[i].r, arr[i].f);
		arr2[arr[i].f].push_back(pii(arr[i].x, arr[i].r));
	}
	
	ll ans=0;
	
	for(int i=1; i<=10000; i++){
		if(arr2[i].empty())continue;
		sort(all(arr2[i]));
		vector<pii>tmp;
		for(int j=max(1,i-k); j<=min(10000,i+k); j++){
			for(auto x:arr2[j])tmp.emplace_back(x);
		}
		sort(all(tmp), [&](pii &a, pii &b){return a.first-a.second < b.first-b.second;});
		Treap<int> T;
		
		int j=0;
		for(auto &p:arr2[i]){
			for(;j<sz(tmp) && tmp[j].first-tmp[j].second<=p.first; j++)
				T.insert(tmp[j].first);
			ans+=T.query(p.first+1, p.first + p.second);
		}
	}
	
	pf("%lld\n",ans);
	
	
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