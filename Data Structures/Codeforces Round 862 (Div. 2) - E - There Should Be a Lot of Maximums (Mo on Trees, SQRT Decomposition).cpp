#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;
const int K = 320;

vector<int>graph[N];
int cnt[105000]={0};
int Block[K]={0};
int arr[N];
int mp[N],original[N];
int euler[N],dTime[N],eTime[N];
int Time=0;

void dfs(int u, int p){
	dTime[u] = ++Time;
	euler[Time] = u;
	for(int v:graph[u])
		if(v^p)dfs(v,u);
	eTime[u] = Time;
}

void add(int x){
	x = arr[euler[x]];
	if(++cnt[x] == 2)Block[x/K]++;
}

void rem(int x){
	x = arr[euler[x]];
	if(--cnt[x] == 1)Block[x/K]--;
}

int getAns(){
	int x=K-1;
	while(x>=0 && Block[x]==0)x--;
	if(x==-1)return 0;
	x = ((x+1)*K)-1;
	while(cnt[x]<2)x--;
	return original[x];
}

inline void solve(int caseNum){
	int n;
	cin>>n;
	vector<pii(2)>edges(n-1);
	for(int i=0,u,v; i<n-1; i++){
		cin>>u>>v;
		graph[u].push_back(v);
		graph[v].push_back(u);
		edges[i] = {u,v};
	}

	{
		vector<int>tmp;
		for(int i=1; i<=n; i++){
			cin>>arr[i];
			tmp.push_back(arr[i]);
		}
		sort(all(tmp));
		tmp.erase(unique(all(tmp)), tmp.end());
		for(int i=0; i<sz(tmp); i++)original[i] = tmp[i];
		for(int i=1; i<=n; i++){
			//cout<<arr[i]<<" -> ";
			arr[i] = upper_bound(all(tmp),arr[i]) - tmp.begin()-1;
			//cout<<arr[i]<<endl;
		}
	}

	dfs(1,1);
	struct query{
		int l,r,x,i;
		bool operator<(const query &q)const{
			if(x^q.x)return x<q.x;
			return (x&1)?r<q.r:r>q.r;
		}
	};

	vector<query>queries(n-1);
	for(int i=0; i<n-1; i++){
		int u = edges[i][0];
		int v = edges[i][1];
		if(dTime[u]<dTime[v])swap(u,v);
		queries[i] = {dTime[u],eTime[u],dTime[u]/K,i};
	}
	sort(all(queries));

	vector<int>ans(n-1,-1);
	int L=1,R=0;

	for(auto &q:queries){
		while(L>q.l)add(--L);
		while(R<q.r)add(++R);
		while(R>q.r)rem(R--);
		while(L<q.l)rem(L++);
		ans[q.i] = max(ans[q.i], getAns());
	}

	memset(cnt,0,sizeof(cnt));
	memset(Block,0,sizeof(Block));
	for(int i=1; i<=Time; i++)add(i);

	L=1,R=0;
	for(auto &q:queries){
		while(L>q.l)rem(--L);
		while(R<q.r)rem(++R);
		while(R>q.r)add(R--);
		while(L<q.l)add(L++);
		ans[q.i] = max(ans[q.i], getAns());
	}

	for(int i:ans)cout<<i<<"\n";
}

int main(){

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