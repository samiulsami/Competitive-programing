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

const int N = 5e4+5;

const int primesN=N;
uint32_t status[(primesN>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<int>primes;
 
void sieve(){
    uint32_t sq=sqrt(primesN)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<=primesN; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<=primesN; i+=2)if(!checkP(i))primes.push_back(i);
}

ll ans=0;

vi graph[N];

struct CentroidDecomposition{
    int subtreeSize[N];
    bool vis[N]={0};///Marks centroids
    int n,curSize,mx=0;
	int dist[N]={0};

    void init(int x, int root=1){///Call first
		n=x;
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
	
	void dfs1(int u, int p, int lvl, bool b){
		if(lvl>n)return;
		mx=max(mx,lvl);
		if(!b){
			for(int i:primes){
				if(i-lvl>=0){
					if(dist[i-lvl]==0)break;
					ans+=dist[i-lvl];
				}
			}
		}
		else dist[lvl]++;
		
		for(int v:graph[u]){
			if(!vis[v] && v!=p)dfs1(v,u,lvl+1,b);
		}
	}

    void centroid_decomposition(int u, int p){
        curSize=dfs(u,u);
        int centroid = find_centroid(u,u);
        vis[centroid]=1;
		
		mx=0;
		for(int v:graph[centroid]){
			if(!vis[v]){
				dfs1(v,centroid,1,0);
				dfs1(v,centroid,1,1);
			}
		}
		for(int i=1; i<=mx; i++)dist[i]=0;
		
        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v,centroid);
    }
}CD;

void solve(int casenum){
	sieve();
	int n;
	si(n);
	CD.dist[0]=1;
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	CD.init(n,1);
	ll total = 1LL*n*(n-1);
	total/=2;
	//pf("ans: %lld\n",ans);
	pf("%0.6Lf\n",ld(ans)/ld(total));
	
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