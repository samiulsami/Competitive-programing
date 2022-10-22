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

const int N = 1e5+5;
vi graph[N];
int dTime[N],eTime[N];

const int K = __lg(N<<1)+1;
struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
	int discoveryTime[N],lvl[N],sparseTable[K][N<<1];
    int n,Time;

    void init(int n, int root=1){
        lvl[root]=0;
        Time=0;
        dfs(root,-1);

        for(int i=1; i<K; i++){
            for(int j=1; j+(1<<i)-1<=Time; j++){
                int left=sparseTable[i-1][j];
                int right=sparseTable[i-1][j+(1<<(i-1))];
                if(lvl[left]<lvl[right])sparseTable[i][j] = left;
                else sparseTable[i][j] = right;
            }
        }
    }

    void dfs(int u, int p){
        discoveryTime[u]=++Time;
        sparseTable[0][Time]=u;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
    }

    inline int lca(int u, int v){
        u=discoveryTime[u];
        v=discoveryTime[v];
        if(u>v)swap(u,v);
        int logVal = __lg(v-u+1);
        int x=sparseTable[logVal][u];
        int y=sparseTable[logVal][v-(1<<logVal)+1];
        if(lvl[x]<lvl[y])return x;
        return y;
    }
	
	int dist(int u, int v){
		return lvl[u]+lvl[v] - 2*lvl[lca(u,v)];
	}
}lca;
	

struct CentroidDecomposition{
    int parent[N],subtreeSize[N];
    bool vis[N];///Marks centroids
    int n,curSize,Time;

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
		dTime[centroid]=++Time;
        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v,centroid);
		eTime[centroid]=Time;
    }
}CD;

int arr[N];
vector<pii>mp[N];
bool vis[N]={0};

void solve(int casenum){
	int n,q,k,d;
	sii(n,q);
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	CD.Time=0;
	lca.init(n,1);
	CD.init(n,1);
	ll ans=0;
	int u,req,dist,prev;
	
	while(q--){
		sii(k,d);
		ans=0;
		if(d==0){
			FOR(i,k)sl(ans);
			pf("0\n",k);
			continue;
		}
		FOR(i,k){
			si(arr[i]);
			u=arr[i];
			while(u!=-1){
				dist = lca.dist(u,arr[i]);
				mp[u].push_back(pii(dist,dTime[arr[i]]));
				u=CD.parent[u];
			}
		}
		
		FOR(i,k){
			u=arr[i];
			prev=-1;
			while(u!=-1){
				dist = lca.dist(u,arr[i]);
				req=d-dist;
				if(!vis[u]){
					sort(all(mp[u]));
					vis[u]=1;
				}
				
				if(req>=0){
					ans+=upper_bound(all(mp[u]),pii(req,1e9)) - lower_bound(all(mp[u]),pii(req,0));
					if(prev!=-1)ans-=upper_bound(all(mp[u]),pii(req,eTime[prev])) - lower_bound(all(mp[u]),pii(req,dTime[prev]));
				}
				prev=u;
				u=CD.parent[u];
			}
		}
		
		FOR(i,k){
			u=arr[i];
			while(u!=-1){
				if(!vis[u])break;
				vis[u]=0;
				mp[u].clear();
				u=CD.parent[u];
			}
		}

		pf("%lld\n",ans>>1);
	}
	
	
	for(int i=0; i<=n; i++)graph[i].clear();
}


int main(){

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