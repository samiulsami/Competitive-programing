#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
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
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

#define ptType int
struct pt{ptType x,y;};

inline ll crossproduct(pt &a, pt &b, pt &c){
	return 1LL*(b.x-a.x)*(c.y-a.y) - 1LL*(b.y-a.y)*(c.x-a.x);
}

int orientation(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ll tmp = crossproduct(a,b,c);
	if(tmp>0)return 1;
	if(tmp<0)return -1;
	return 0;
}

///O(logn)
int pointInConvexPolygon(vector<pt> &pts, pt p){///YouKn0wWho
	///Points must be in clockwise order
	///1 = inside
	///0 = boundary
	///-1 = outside
	int low=1,high=int(pts.size())-1,mid;
	int a=orientation(pts[0],pts[1],p), b=orientation(pts[0],pts.back(),p);
	if(a==1 || b==-1)return -1;
	while(low+1<high){
		mid=(low+high)>>1;
		if(orientation(pts[0],pts[mid],p)<=0)low=mid;
		else high=mid;
	}
	int orient = orientation(pts[low],pts[high],p);
	if(orient==0)return 0;
	if(orient==1)return -1;
	if(low==1 && a==0)return 0;
	if(high=int(pts.size()-1 && b==0))return 0;
	return 1;
}

#undef ptType

inline bool check(vector<pt> &a, vector<pt> &b){///Check if b lies strictly inside a
	for(pt &x:b){
		if(pointInConvexPolygon(a,x)!=1)return 0;
	}
	return 1;
}

struct HopcroftKarp{

    vector<vector<int> >graph;
    vector<int>matchL,matchR;
    vector<int>dist;
    int n;

    HopcroftKarp(int n):n(n),graph(n),matchL(n),matchR(n),dist(n){}

    void addEdge(int u, int v){
        graph[u].push_back(v);
    }

    bool bfs(){
        queue<int>q;
        for(int i=0; i<n; i++){
            if(matchL[i]==-1){
                dist[i]=0;
                q.push(i);
            }
            else dist[i]=-1;
        }
        bool flag=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v:graph[u]){
                if(matchR[v]==-1)flag=1;
                else if(dist[matchR[v]] == -1){
                    dist[matchR[v]] = dist[u]+1;
                    q.push(matchR[v]);
                }
            }
        }
        return flag;
    }

    bool dfs(int u){
        for(int v:graph[u]){
            if(matchR[v]==-1 || (dist[matchR[v]] == dist[u]+1 && dfs(matchR[v]))){
                matchR[v]=u;
                matchL[u]=v;
                return true;
            }
        }
        dist[u]=-1;
        return false;
    }

    int bpm(){
        int matching=0;
        for(int i=0; i<n; i++)matchL[i]=matchR[i]=-1;
        while(bfs()){
            for(int i=0; i<n; i++){
                if(matchL[i]==-1 && dfs(i))
                    matching++;
            }
        }
        return matching;
    }
};

void solve(int casenum){
	int n;
	si(n);
	vector<vector<pt> >polys(n);
	for(int i=0,v; i<n; i++){
		si(v);
		polys[i].resize(v);
		for(int j=v-1; j>=0; j--)sii(polys[i][j].x, polys[i][j].y);
	}
	
	HopcroftKarp hk(n+1);
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(check(polys[i],polys[j]))hk.addEdge(i,j);
			else if(check(polys[j],polys[i]))hk.addEdge(j,i);
		}
	}
	
	//pf("ans: ");
	pf("%d\n", n-hk.bpm());
}

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