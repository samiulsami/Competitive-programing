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


const int N = 2e5+5;

struct DSU{
    vector<int>parent;
    int n;
    DSU(int n):n(n),parent(n+1){for(int i=0; i<=n; i++)parent[i]=i;}
    inline int Find(int x){
        if(parent[x]==x)return x;
        return parent[x]=Find(parent[x]);
    }
    inline bool Unite(int x, int y){
        x=Find(x);
        y=Find(y);
        if(x!=y){
            parent[x]=y;
            return 1;
        }
        return 0;
    }
};

const int _chars=2;
struct trie{
	struct trienode{
		int id,counter;
		trienode *nxt[_chars];
		trienode(){
			for(int i=0; i<_chars; i++)nxt[i]=NULL;
			counter=0;
		}
	}trienodes[2*30*N];
	int cnt;
	trienode *root;
	
	trie(){reset();}
	
	inline trienode* newNode(){
		trienodes[cnt]=trienode();
		return &trienodes[cnt++];
	}
	
	void insert(int val, int id){
		trienode *cur=root;
		for(int i=29; i>=0; i--){
			bool b = bool(val&(1<<i));
			if(cur->nxt[b]==NULL)cur->nxt[b]=newNode();
			cur=cur->nxt[b];
			cur->counter++;
		}
		cur->id=id;
	}
	
	void del(int val){
		trienode *cur=root;
		for(int i=29; i>=0; i--){
			bool b = bool(val&(1<<i));
			cur=cur->nxt[b];
			cur->counter--;
		}
	}
	
	pii get(int val){
		int ret=0;
		trienode *cur=root;
		for(int i=29; i>=0; i--){
			bool b = bool(val&(1<<i));
			if(cur->nxt[b]==NULL || cur->nxt[b]->counter<=0){
				ret|=(1<<i);
				cur=cur->nxt[b^1];
			}
			else cur=cur->nxt[b];
		}
		return pii(ret,cur->id);
	}
	
	void reset(){
		cnt=0;
		root=newNode();
	}
}Trie;

void solve(int casenum){
	int n;
	si(n);
	vi arr(n);
	FOR(i,n)si(arr[i]);
	sort(all(arr));
	arr.erase(unique(all(arr)),arr.end());
	n=sz(arr);
	int cnt=n;
	ll ans=0;
	DSU dsu(n);
	vector<vector<int> >components(n);
	
	while(cnt>1){
		if(cnt^n)for(int i=0; i<n; i++)components[i].clear();
		for(int i=0; i<n; i++){
			Trie.insert(arr[i],i);
			components[dsu.Find(i)].push_back(i);
		}
		vector<pair<int,pii> >edges;
		
		for(int i=0; i<n; i++){
			if(components[i].empty())continue;
			for(int &j:components[i])Trie.del(arr[j]);
			pair<int,pii>tmp(1e9,pii(0,0));
			
			for(int &j:components[i]){
				pii res=Trie.get(arr[j]);
				if(res.first<tmp.first)tmp=pair<int,pii>(res.first, pii(j, res.second));
			}
			edges.emplace_back(tmp);
			for(int &j:components[i])Trie.insert(arr[j],j);
		}
		sort(all(edges));
		
		for(auto &edge:edges){
			int val=edge.first;
			int u=edge.second.first;
			int v=edge.second.second;
			if(dsu.Unite(u,v)){
				ans+=val;
				cnt--;
			}
		}
		//dbug(ans);
		Trie.reset();
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