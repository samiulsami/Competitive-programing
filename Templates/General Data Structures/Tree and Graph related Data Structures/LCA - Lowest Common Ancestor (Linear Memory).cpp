struct LCA{
	///Credits:
	///lrvideckis
	///https://codeforces.com/blog/entry/74847 
	
	int jump[N],lvl[N],parent[N];
	int root=-1;
	
	void init(int r=1){
		root=r;
		jump[root]=root;
		parent[root]=root;
		lvl[root]=0;
		dfs(root,root);
	}
	
	void dfs(int u, int p){
		int par2 = jump[p];
		lvl[u] = lvl[p] + 1;
		jump[u] = (lvl[p] - lvl[par2] == lvl[par2] - lvl[jump[par2]]) ? jump[par2] : p;
		parent[u] = p;
		for(int &v:graph[u])
			if(v^p)dfs(v,u);
	}
	
	int kthParent(int u, int k){
		while(k>0 && u!=root){
			if(lvl[u] - k <= lvl[jump[u]]){
				k -= lvl[u] - lvl[jump[u]];
				u = jump[u];
			}
			else{
				k--;
				u = parent[u];
			}
		}
		return u;
	}
	
	int lca(int u, int v){
		if(lvl[u]<lvl[v])swap(u,v);
		u = kthParent(u, lvl[u] - lvl[v]);
		if(u==v)return v;
		
		while(u!=v){
			if(jump[u] == jump[v]){
				u = parent[u];
				v = parent[v];
			}
			else{
				u = jump[u];
				v = jump[v];
			}
		}
		
		return u;		
	}
	
	inline int dist(int u, int v){
		return lvl[u] + lvl[v] - 2*lvl[lca(u,v];
	}
}lca;