  
struct tarjanSCC{
	vector<int>graph[N],dag[N];
	int discovery_time[N],parent[N];
	int Time=0,scc=0,n;
	stack<int>curTree;
	bool inTree[N];
	void reset(int n){///CALL FIRST
		this->n=n;
		Time=0;
		scc=0;
		while(!curTree.empty())curTree.pop();
		for(int i=0; i<=n; i++){
			discovery_time[i]=0;
			parent[i]=0;
			graph[i].clear();
			inTree[i]=0;
			dag[i].clear();
		}
	}
	void addEdge(int u, int v){graph[u].push_back(v);}
	void run(){for(int i=1; i<=n; i++)if(!discovery_time[i])dfs(i);}
	void makedag(){
		for(int i=1; i<=n; i++){
			for(int v:graph[i]){
				if(parent[i]!=parent[v])
					dag[parent[i]].push_back(parent[v]);
			}
		}
	}
	int dfs(int u){
		int low=discovery_time[u]=++Time;
		curTree.push(u);
		inTree[u]=1;

		for(int v:graph[u]){
			if(!discovery_time[v])low=min(low,dfs(v));
			else if(inTree[v])low=min(low,discovery_time[v]);
		}
		if(low==discovery_time[u]){
			int top;
			scc++;
			do{
				top=curTree.top();
				curTree.pop();
				inTree[top]=0;
				parent[top]=scc;
			}while(u!=top);
		}
		return low;
	}
	
}scc;