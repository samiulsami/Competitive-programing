#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;
vector<int>pf[N];
int arr[N];
vector<int>graph[N];
int ans=0;
int primeLen[N]={0};
bool status[N]={0};

struct CentroidDecomposition{
    int subtreeSize[N];
    bool vis[N]={0};///Marks centroids
    int n,curSize,curmx=0;

    void init(int root=1){///Call first
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
	
	void calc(int u, int p, bool b, int lvl, int G){
		if(b){
			for(int i:pf[G])primeLen[i] = max(primeLen[i], lvl);
		}
		else {
			for(int i:pf[G])ans = max(ans, lvl + primeLen[i]);
		}
		for(int v:graph[u]){
			int newG = __gcd(G, arr[v]);
			if(!vis[v] && v^p && newG!=1)calc(v,u,b,lvl+1,newG);
		}
	}

    void centroid_decomposition(int u){
        curSize=dfs(u,u);
        int centroid = find_centroid(u,u);
        vis[centroid]=1;

		for(int v:graph[centroid]){
			if(!vis[v]){
				int G = __gcd(arr[v],arr[centroid]);
				if(G==1)continue;
				calc(v,centroid,0,1,G);
				calc(v,centroid,1,1,G);
			}
		}
		for(int i:pf[arr[centroid]])primeLen[i]=0;

        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v);
    }
}CD;


inline void solve(int caseNum){
	for(int i=2; i<N; i++){
		if(!status[i]){
			for(int j=i; j<N; j+=i){
				status[j]=1;
				pf[j].push_back(i);
			}
		}
	}

	int n;
	cin>>n;

	int all1=1;

	for(int i=1; i<=n; i++){
		cin>>arr[i];
		if(arr[i]>1)all1=0;
	}

	for(int i=1,u,v; i<n; i++){
		cin>>u>>v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	if(all1){
		cout<<"0\n";
		return;
	}

	CD.init();

	cout<<ans+1<<"\n";

}

int main(){
	sieve();
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}