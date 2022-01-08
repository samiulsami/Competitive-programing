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

const int N = 50004;
vi graph[N];

struct LCA{
    ///LCA with Binary Lifting, O(nlogn) preprocessing, O(logn) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    int lvl[N],Table[18][N];
    int LOG,n;

    void init(int n, int root=1){
		this->n=n;
		LOG = ceil(log2(n))+1;
		lvl[root]=0;
        dfs(root,-1);
        for(int i=1; i<LOG; i++)
            for(int j=1; j<=n; j++)
                if(Table[i-1][j]!=-1)
                    Table[i][j] = Table[i-1][Table[i-1][j]];
				else Table[i][j]=-1;
    }

    void dfs(int u, int p){
        Table[0][u]=p;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
            }
    }

    int lca(int u, int v){
        if(lvl[u]!=lvl[v]){
                if(lvl[u]>lvl[v])swap(u,v);
                for(int i=LOG-1; i>=0; i--)
                    if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u])
                        v=Table[i][v];
        }
        if(u==v)return u;
        for(int i=LOG-1; i>=0; i--){
            if(Table[i][u]!=Table[i][v]){
                u=Table[i][u];
                v=Table[i][v];
            }
        }
        return Table[0][u];
    }
	
	inline int dist(int u, int v){
		return lvl[u]+lvl[v] - 2*(lvl[lca(u,v)]);
	}
}lca;

struct CentroidDecomposition{
    int parent[N],subtreeSize[N];
    bool vis[N];///Marks centroids
    int n,curSize;

    void init(int x, int root=1){///Call first
        n=x;
        for(int i=0; i<=n; i++)vis[i]=0;
        centroid_decomposition(root,-1);
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

    void centroid_decomposition(int u, int p){
        curSize=dfs(u,u);
        int centroid = find_centroid(u,u);
        vis[centroid]=1;
        parent[centroid]=p;
        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v,centroid);
    }
}CD;

map<int,int>mp[N],mp2[N];

void solve(int casenum){
	int n,k;
	sii(n,k);
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	lca.init(n,1);
	CD.init(n,1);
	
	ll ans=0;
	for(int i=1,u,prev,dist,req; i<=n; i++){
		u=i;
		prev=-1;
		while(u!=-1){
			dist=lca.dist(i,u);
			req=k-dist;
			if(mp[u].count(req))ans+=mp[u][req];
			if(prev!=-1){
				if(mp2[prev].count(req))ans-=mp2[prev][req];
			}
			mp[u][dist]++;
			if(prev!=-1)mp2[prev][dist]++;
			prev=u;
			u=CD.parent[u];
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