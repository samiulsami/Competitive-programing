vector<pii>queries[N];
int color[N];
int colorCnt[N]={0};
int cntSum[N]={0};

struct dsuOnTree{
	vector<int>graph[N];
	int dTime[N],eTime[N],euler[N];
	int maxSubtree[N];
	int ans[N];
	int Time=0;

	void init(int root){
		dfs1(root,root);
		dfs(root,root,0);
	}
	
	void addEdge(int u, int v){
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	int dfs1(int u, int p){
		dTime[u]=++Time;
		euler[Time]=u;
		int ret=1,mxSubtree=-1,curmx=-1,tmp;
		for(int &v:graph[u])
			if(v^p){
				tmp=dfs1(v,u);
				ret+=tmp;
				if(tmp>curmx){
					mxSubtree=v;
					curmx=tmp;
				}
			}
		maxSubtree[u]=mxSubtree;
		eTime[u]=Time;
		return ret;
	}

	void dfs(int u, int p, bool keep){
		int heavyChild = maxSubtree[u];
		for(int &v:graph[u])
			if(v^p && v^heavyChild)dfs(v,u,0);
		if(heavyChild!=-1)dfs(heavyChild,u,1);
		for(int &v:graph[u])
			if(v^p && v^heavyChild)
				for(int x=dTime[v]; x<=eTime[v]; x++)add(euler[x]);
		add(u);
		calc(u);
		if(!keep)for(int x=dTime[u]; x<=eTime[u]; x++)
				remove(euler[x]);
	}
	
	inline void add(int u){
		colorCnt[color[u]]++;
		cntSum[colorCnt[color[u]]]++;
	}
	
	inline void remove(int u){
		cntSum[colorCnt[color[u]]]--;
		colorCnt[color[u]]--;
	}
	
	inline int calc(int u){
		for(auto &q:queries[u]){
			ans[q.first] = cntSum[q.second];
		}
	}
	
}dot;