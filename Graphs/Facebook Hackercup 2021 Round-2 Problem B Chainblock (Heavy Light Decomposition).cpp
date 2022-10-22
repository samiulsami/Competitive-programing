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


const int N = 1600000+5;


vector<int>graph[N];

struct HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    int Tree[N<<2];
	bool Lazy[N<<2];

    void init(int x, int root=1){///CALL FIRST
        n=x;
        for(int i=0,lim=n<<2; i<lim; i++){
			Tree[i]=0;
			Lazy[i]=0;
		}
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
    }

    int lca(int u, int v){
        while(chainRoot[u]!=chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            u=parent[chainRoot[u]];
        }
        if(lvl[u]>lvl[v])return v;
        return u;
    }

	void push_update(int node, int l, int r){
		if(Lazy[node]){
			Tree[node]=1;
			if(l^r){
				Lazy[node<<1]=1;
				Lazy[node<<1|1]=1;
			}
			Lazy[node]=0;
		}
	}

	void update(int node, int l, int r, int posl, int posr){
		push_update(node,l,r);
		if(posl>r || posr<l || l>r)return;
		if(l>=posl && r<=posr){
			Lazy[node]=1;
			push_update(node,l,r);
		}
		else{
			int mid = (l+r)>>1;
			update(node<<1,l,mid,posl,posr);
			update(node<<1|1,mid+1,r,posl,posr);
			Tree[node] = Tree[node<<1]+Tree[node<<1|1];
		}
	}

	int get(int u){
		return query(1,1,n,posInChain[u]);
	}

	int query(int node, int l, int r, int pos){
		push_update(node,l,r);
		if(l>r || r<pos || l>pos)return 0;
		if(l>=pos && r<=pos)return Tree[node];
		int mid = (l+r)>>1;
		return query(node<<1,l,mid,pos)+query(node<<1|1,mid+1,r,pos);
	}

    void update1(int u, int v){///Query the path from node u to v
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            update(1,1,n,posInChain[chainRoot[u]], posInChain[u]);
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
		update(1,1,n,u,v);
    }

    int dfs(int u, int p){
        parent[u]=p;
        int ret=1, mx=0,nxt=-1,subtreeSize;
        for(int v:graph[u]){
            if(v==p)continue;
            lvl[v]=lvl[u]+1;
            subtreeSize=dfs(v,u);
            ret+=subtreeSize;
            if(subtreeSize>mx){
                mx=subtreeSize;
                nxt=v;
            }
        }
        maxSubtree[u]=nxt;
        return ret;
    }

    void hld(int u, int p, int chainParent){
        chainRoot[u]=chainParent;
        posInChain[u]=++posCnt;
        chainArr[posCnt]=u;

        if(maxSubtree[u]!=-1)hld(maxSubtree[u],u,chainParent);
        for(int v:graph[u]){
            if(v==p || v==maxSubtree[u])continue;
            hld(v,u,v);
        }
    }

}HLD;

void solve(int casenum){
	int n;
	si(n);
	int cnt=n;
	vi tmp;
	vector<vector<int> > freq(n+1);
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		cnt++;
		graph[u].push_back(cnt);
		graph[v].push_back(cnt);
		graph[cnt].push_back(u);
		graph[cnt].push_back(v);
		tmp.push_back(cnt);
	}

	for(int i=1,x; i<=n; i++){
		si(x);
		freq[x].push_back(i);
	}

	HLD.init(cnt,1);

	for(int i=1; i<=n; i++){
		if(sz(freq[i])<=1)continue;
		sort(all(freq[i]), [&](int &a, int &b)->bool{
			return HLD.lvl[a]>HLD.lvl[b];
		});

		int cur=freq[i][0];
		for(int j=1; j<sz(freq[i]); j++){
			HLD.update1(cur,freq[i][j]);
		}
	}

	int ans=0;
	for(int &i:tmp){
		if(!HLD.get(i))ans++;
	}

	pf("Case #%d: %d\n",casenum,ans);
	for(int i=0; i<=cnt; i++)graph[i].clear();
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
