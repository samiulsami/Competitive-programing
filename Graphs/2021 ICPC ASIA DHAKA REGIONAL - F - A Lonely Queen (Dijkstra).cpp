#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+100;

int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1, -1,1,-1,0,1};
ll c[8];
ll dist[10][N];
vector<array<ll,3>>graph[N];
bool Blocked[N]={0};
int n,m,p,q;

struct node{
	ll x,y;
	ll weight;
	ll dir;
	node(){}
	node(ll a, ll b, ll c, ll d){
		x=a;
		y=b;
		weight=c;
		dir=d;
	}
	bool operator<(const node &nd)const{
		return weight>nd.weight;
	}
};

inline int get(int i, int j){return (i-1)*m + j;}
inline bool safe(int i, int j){return bool(i>0 && j>0 && i<=n && j<=m);}

inline void solve(int caseNum){

	cin>>n>>m>>p>>q;
	//cerr<<n<<" "<<m<<" "<<p<<" "<<q<<endl;
	//dbug(get(n,m));
	for(int k=0; k<9; k++){
		for(int i=0; i<=n*m; i++){
			dist[k][i]=1e18;
		}
	}

	
	int sx,sy,Dx,Dy;
	cin>>sx>>sy>>Dx>>Dy;
	dist[8][get(sx,sy)]=0;///8 = no direction

	priority_queue<node>pq;
	pq.push({sx,sy,0,8});

	for(int i=0; i<8; i++)
		cin>>c[i];
	

	for(int i=0,ux,uy,vx,vy,w; i<p; i++){
		cin>>ux>>uy>>vx>>vy>>w;
		graph[get(ux,uy)].push_back({w,vx,vy});
	}

	for(int i=0,bx,by; i<q; i++){
		cin>>bx>>by;
		Blocked[get(bx,by)]=1;
	}

	while(!pq.empty()){
		auto top = pq.top();
		pq.pop();
		//if(Blocked[get(top.x,top.y)])continue;
		if(dist[top.dir][get(top.x,top.y)] < top.weight)continue;

		for(int xx=0; xx<8; xx++){
			int newx = top.x+dx[xx];
			int newy = top.y+dy[xx];
			if(!safe(newx, newy) || Blocked[get(newx,newy)])continue;
			int val = get(newx,newy);

			ll newWeight = top.weight;
			if(top.dir!=xx)newWeight += c[xx];

			if(dist[xx][val] > newWeight){
				dist[xx][val] = newWeight;
				pq.push({newx,newy,newWeight,xx});
			}
		}

		//if(graph[get(top.x,top.y)].empty())continue;
		for(auto &e:graph[get(top.x,top.y)]){
			int val = get(e[1],e[2]);
			if(Blocked[val])continue;

			ll newWeight = top.weight + e[0];
			if(dist[8][val] > newWeight){
				dist[8][val] = newWeight;
				pq.push({e[1], e[2], newWeight, 8});
			}
		}
	}

	ll ans=1e18;
	for(int i=0; i<=8; i++){
		ans = min(ans, dist[i][get(Dx,Dy)]);
	}

	if(ans==ll(1e18))ans=-1;
	cout<<"Case "<<caseNum<<": "<<ans<<"\n";

	for(int k=0; k<9; k++){
		for(int i=0; i<=n*m+5; i++){
			dist[k][i]=1e18;
			graph[i].clear();
			Blocked[i]=0;
		}
	}

}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}