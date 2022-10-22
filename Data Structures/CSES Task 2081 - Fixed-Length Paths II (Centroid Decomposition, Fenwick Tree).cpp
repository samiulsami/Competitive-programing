#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
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
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;

vi graph[N];
ll ans=0;
int k1,k2,n;
ll BIT[N]={0};

inline ll query(int i){
	ll ret=0;
	i++;
	while(i>0){
		ret+=BIT[i];
		i-=(i&-i);
	}
	return ret;
}

ll query(int i, int j){return query(j)-query(i-1);}

void update(int i, ll val){
	i++;
	while(i<=n){
		BIT[i]+=val;
		i+=(i&-i);
	}
}

struct CentroidDecomposition{
    int subtreeSize[N];
    bool vis[N]={0};///Marks centroids
    int curSize,curmx=0;

    void init(int x, int root=1){///Call first
        centroid_decomposition(root);
    }

    int dfs(int u, int p){
        subtreeSize[u]=1;
        for(int v:graph[u])
            if(!vis[v] && v!=p)subtreeSize[u]+=dfs(v,u);
        return subtreeSize[u];
    }

    int find_centroid(int u, int p){
        for(int v:graph[u])
            if(!vis[v] && v!=p)
                if(subtreeSize[v]>curSize/2)return find_centroid(v,u);
        return u;
    }
	
	void calc(int u, int p, bool b, int lvl){
		if(lvl>k2)return;
		curmx=max(curmx,lvl);
		if(b)update(lvl,1);
		else ans+=query(max(0,k1-lvl),k2-lvl);
		for(int v:graph[u]){
			if(!vis[v] && v^p)calc(v,u,b,lvl+1);
		}
	}

    void centroid_decomposition(int u){
        curSize=dfs(u,u);
        int centroid = find_centroid(u,u);
        vis[centroid]=1;
		curmx=0;
		for(int v:graph[centroid]){
			if(!vis[v]){
				calc(v,centroid,0,1);
				calc(v,centroid,1,1);
			}
		}
		for(int i=1; i<=curmx+1; i++)update(i,-query(i,i));
        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v);
    }
}CD;


void solve(int casenum){
	siii(n,k1,k2);
	update(0,1);
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	CD.init(n);
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