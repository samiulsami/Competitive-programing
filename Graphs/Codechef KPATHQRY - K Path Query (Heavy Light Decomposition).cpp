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

vector<int>graph[N];

struct HLD{
    int posInChain[N],chainRoot[N];
    int parent[N],maxSubtree[N],lvl[N];
    int chainArr[N];
    int n,posCnt;
    pii Tree[4*N];
	int Lazy[4*N];
	
	inline pii Merge(pii a, pii b){
		if(a.first==b.first)return pii(a.first,a.second+b.second);
		if(a.first<b.first)return b;
		return a;
	}
	
	inline void push_update(int node, int l, int r){
		if(Lazy[node]){
			Tree[node].first+=Lazy[node];
			if(l^r){
				Lazy[node<<1]+=Lazy[node];
				Lazy[node<<1|1]+=Lazy[node];
			}
			Lazy[node]=0;
		}
	}
	
	void build(int node, int l, int r){
		Lazy[node]=0;
		if(l==r)Tree[node]=pii(0,1);
		else{
			int mid = (l+r)>>1;
			build(node<<1,l,mid);
			build(node<<1|1,mid+1,r);
			Tree[node] = Merge(Tree[node<<1],Tree[node<<1|1]);
		}
	}
	
	bool check(int u){
		return query1(1,1,posCnt,posInChain[u]).first>0;
	}
	
	pii query1(int node, int l, int r, int pos){
		push_update(node,l,r);
		if(l>r || r<pos || l>pos)return pii(0,0);
		if(l==pos && r==pos)return Tree[node];
		int mid = (l+r)>>1;
		return Merge(query1(node<<1,l,mid,pos),query1(node<<1|1,mid+1,r,pos));
	}
	
	pii tree_query(int node, int l, int r, int posl, int posr){
		push_update(node,l,r);
		if(l>r || r<posl || l>posr)return pii(-1,0);
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		return Merge(tree_query(node<<1,l,mid,posl,posr), tree_query(node<<1|1,mid+1,r,posl,posr));
	}

	void tree_update(int node, int l, int r, int posl, int posr, int val){
		push_update(node,l,r);
		if(l>r || r<posl || l>posr)return;
		if(l>=posl && r<=posr){
			Lazy[node]+=val;
			push_update(node,l,r);
		}
		else{
			int mid = (l+r)>>1;
			tree_update(node<<1,l,mid,posl,posr,val);
			tree_update(node<<1|1,mid+1,r,posl,posr,val);
			Tree[node] = Merge(Tree[node<<1],Tree[node<<1|1]);
		}
	}
    void init(int x, int root=1){///CALL FIRST
        n=x;
        posCnt=0;
        lvl[root]=0;
        dfs(root,root);
        hld(root,root,root);
		build(1,1,posCnt);
    }

    int lca(int u, int v){
        while(chainRoot[u]!=chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
            u=parent[chainRoot[u]];
        }
        if(lvl[u]>lvl[v])return v;
        return u;
    }


    void addPath(int u, int v, int val){
        while(chainRoot[u] != chainRoot[v]){
            if(lvl[chainRoot[u]]<lvl[chainRoot[v]])swap(u,v);
			tree_update(1,1,posCnt,posInChain[chainRoot[u]],posInChain[u],val);
            u=parent[chainRoot[u]];
        }

        u=posInChain[u];
        v=posInChain[v];
        if(u>v)swap(u,v);
        tree_update(1,1,posCnt,u,v,val);
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

	pii get(int u){
		return tree_query(1,1,posCnt,posInChain[u],posInChain[u]);
	}
}HLD;

int arr[N];

void solve(int casenum){
	int n;
	si(n);

	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	HLD.init(n,1);
	
	int q,k;
	si(q);
	while(q--){
		si(k);
		if(k==1){
			si(arr[0]);
			pf("YES\n");
			continue;
		}
		int L=-1,x,y;
		for(int i=0; i<k; i++){
			si(arr[i]);
			if(L==-1)L=arr[i],x=arr[i];
			else {
				L=HLD.lca(L,arr[i]);
				if(HLD.lvl[x]<HLD.lvl[arr[i]])x=arr[i];
			}
		}
		
		HLD.addPath(x,L,1);
		y=-1;
		for(int i=0; i<k; i++){
			if(!HLD.check(arr[i])){
				if(y==-1 || HLD.lvl[arr[i]]>HLD.lvl[y])y=arr[i];
			}
		}
		
		if(y!=-1)HLD.addPath(y,L,1);
		
		pii tmp = HLD.Tree[1];
		bool b=1;
		//pf("%d %d\n",tmp.first, tmp.second);
		if(tmp.first==2 && tmp.second>=2)b=0;
		
		for(int i=0; b && i<k; i++){
			//pii cur = HLD.get(arr[i]);
			//pf("node: %d, val: %d, occurences: %d\n",arr[i],cur.first,cur.second);
			if(arr[i]==x || arr[i]==y || arr[i]==L)continue;
			if(!HLD.check(arr[i])){
				b=0;
				break;
			}
		}
		
		if(!b)pf("NO\n");
		else pf("YES\n");
		
		HLD.addPath(x,L,-1);
		if(y!=-1)HLD.addPath(y,L,-1);
		
	}
	
	for(int i=0; i<=n; i++)graph[i].clear();
}
/*

1
12
1 11
1 2
2 7
2 3
3 5
3 4
3 6
5 10
5 8
4 9
6 12
100
4 10 5 3 4
*/
//5 1 2 3 8 10 11
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