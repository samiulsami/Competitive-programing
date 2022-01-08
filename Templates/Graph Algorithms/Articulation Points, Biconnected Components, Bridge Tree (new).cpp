struct tarjanBCC{
	vector<int>graph[N],cutEdge,bridgeTree[N];
	vector<int>edges;
	int discovery_time[N],parent[N];
	int Time=0,n,cnt=1;
	bool cutVertex[N];
	void reset(int n){///CALL FIRST
		this->n=n;
		Time=0;
		edges.clear();
		cutEdge.clear();
		cnt=0;
		for(int i=0; i<=n; i++){
			graph[i].clear();
			bridgeTree[i].clear();
			discovery_time[i]=0;
			parent[i]=-1;
			cutVertex[i]=0;
		}
	}
	void addEdge(int u, int v){
		edges.push_back(v);
		graph[u].push_back((int)edges.size()-1);
		edges.push_back(u);
		graph[v].push_back((int)edges.size()-1);
	}
	void run(){
		cutEdge.assign((int)edges.size()+1,0);
		dfs(1,1);
	}
	void makeBridgeTree(){
		cnt=1;
		for(int i=1; i<=n; i++){
			if(parent[i]==-1){
				dfs1(i,cnt++);
			}
		}
		for(int i=1,x,y; i<=n; i++){
			x=parent[i];
			for(int &e:graph[i]){
				y=parent[edges[e]];
				if(y^x)bridgeTree[y].push_back(x);
			}
		}
	}
	void dfs1(int u, int belong){
		parent[u]=belong;
		for(int &e:graph[u]){
			if(!cutEdge[e] && parent[edges[e]]==-1)dfs1(edges[e],belong);
		}
	}
	int dfs(int u, int p){
		int low=discovery_time[u]=++Time;
		int children=0,v;

		for(int &e:graph[u]){
			v=edges[e];
			if(v==p)continue;
			else if(discovery_time[v])
				low=min(low,discovery_time[v]);
			else{
				children++;
				int subtree_min = dfs(v,u);
				low=min(low,subtree_min);
				if(discovery_time[u]<subtree_min){
					cutEdge[e]=1;
					cutEdge[e^1]=1;
				}

				if(discovery_time[u]<=subtree_min){
					if(u!=p)cutVertex[u]=1;
					else if(children>1)cutVertex[u]=1;
				}
			}
		}

		return low;
	}
}bcc;