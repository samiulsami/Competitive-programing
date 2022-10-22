#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;
const ll INF = 1e18;

int dx[4] = {-1,0,0,1};
int dy[4] = {0,1,-1,0};

ll dist[11][11][21][(1<<10)+2];
int pizza[15][15][2];

struct node{
	ll weight,r,c,minute,mask;
	bool operator<(const node &nd)const{
		if(weight==nd.weight)return minute<nd.minute;
		return weight<nd.weight;
	}
};

inline void solve(int caseNum){
	int n,p,m,ar,ac;
	cin>>n>>p>>m>>ar>>ac;

	for(int mask=0,mx=(1<<p); mask<=mx; mask++)
		for(int i=0; i<=n; i++)
			for(int j=0; j<=n; j++)
				for(int k=0; k<=m; k++)
					dist[i][j][k][mask]=-INF;

	for(int i=0; i<=n; i++)
		for(int j=0; j<=n; j++)
			pizza[i][j][0]=pizza[i][j][1]=-1;

	dist[ar][ac][m][0]=0;
	vector<pair<char,ll> >dir(4);
	for(int i=0; i<4; i++){
		cin>>dir[i].first>>dir[i].second;	
	}

	int pizzacount=0;
	for(int i=0; i<p; i++){
		int a,b;
		cin>>a>>b;
		pizza[a][b][1]=pizzacount++;
		cin>>pizza[a][b][0];
	}

	priority_queue<node>pq;
	pq.push({0,ar,ac,m,0});

	while(!pq.empty()){
		auto top = pq.top();
		pq.pop();
		
		ll r = top.r;
		ll c = top.c;
		ll weight = top.weight;
		ll mask = top.mask;
		ll minute = top.minute;
		if(dist[r][c][minute][mask]>weight)continue;

		if(minute==0)continue;
		if(dist[r][c][minute-1][mask]<weight){
			dist[r][c][minute-1][mask] = weight;
			pq.push({weight,r,c,minute-1,mask});
		}

		for(int k=0; k<4; k++){
			int newr = r + dx[k];
			int newc = c + dy[k];
			if(!(newr>=1 && newr<=n && newc>=1 && newc<=n))continue;

			ll newweight=weight;
			if(dir[k].first=='+')newweight += dir[k].second;
			else if(dir[k].first=='-')newweight -= dir[k].second;
			else if(dir[k].first=='*')newweight *= dir[k].second;
			else {
				//cerr<<newweight<<" "<<dir[k].second<<" "<<(newweight/dir[k].second)<<endl;
				if(newweight>=0)newweight = newweight/dir[k].second;
				else{
					newweight*=-1LL;
					newweight = (newweight + dir[k].second-1LL)/dir[k].second;
					newweight*=-1LL;
				}
			}

			if(dist[newr][newc][minute-1][mask]<newweight){
				dist[newr][newc][minute-1][mask] = newweight;
				pq.push({newweight,newr,newc,minute-1,mask});
			}

			if(pizza[newr][newc][1]==-1)continue;

			ll cur = pizza[newr][newc][1];
			ll newmask = mask|(1<<cur);
			if(!bool(mask&(1<<cur)))newweight += pizza[newr][newc][0];
			else continue;

			if(dist[newr][newc][minute-1][newmask]<newweight){
				dist[newr][newc][minute-1][newmask] = newweight;
				pq.push({newweight,newr,newc,minute-1,newmask});
			}
		}
	}

	ll ans = -INF;
	int mask = (1<<p)-1;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
					ans = max(ans,dist[i][j][0][mask]);

	cout<<"Case #"<<caseNum<<": ";
	if(ans==-INF)cout<<"IMPOSSIBLE\n";
	else cout<<ans<<"\n";
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