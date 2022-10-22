#include<bits/stdc++.h>
/*
    Problem: LightOJ 1254 - Prison Break
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define FF first
#define SS second
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define si2(x,y) scanf("%d%d",&x,&y)
#define si3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sl2(x,y) scanf("%lld%lld",&x,&y)
#define sl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
#define SZ(x) (int)x.size()
#define ALL(x) x.begin(),x.end()
#define PB emplace_back
#define CHK cerr<<"----------------\nCAME HERE\n----------------\n";

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
template<typename T>inline bool setmax(T &a, T &b){return b>a?a=b,1:0;}
template<typename T>inline bool setmin(T &a, T &b){return b<a?a=b,1:0;}

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e5+5;

int fuelPrice[105];
struct node{
    int u,cost,fuel;
    node(int u,int cost,int fuel):u(u),cost(cost),fuel(fuel){}
    bool operator<(const node &nd)const{
        //if(cost==nd.cost)return fuel<nd.fuel;
        return cost>nd.cost;
    }
};

vector<pii>graph[105];

inline void Solve(int Case){
    int n,m;
    si2(n,m);
    FOR(i,n){
        graph[i].clear();
        si(fuelPrice[i]);
    }

    int uu,vv,ww;
    FOR(i,m){
        si3(uu,vv,ww);
        if(uu==vv)continue;
        graph[uu].push_back({vv,ww});
        graph[vv].push_back({uu,ww});
    }

    int dist[105][105];
    int q,s,t,c;

    si(q);
    pf("Case %d:\n",Case);

    while(q--){
        si3(c,s,t);
        for(int i=0; i<=n; i++)for(int j=0; j<=c; j++)dist[i][j]=1e6;
        priority_queue<node>pq;
        node src(s,0,0);
        dist[s][0]=0;
        pq.push(src);

        while(!pq.empty()){
            node top = pq.top();
            pq.pop();

            if(top.u==t)break;
            if(dist[top.u][top.fuel]<top.cost)continue;

            for(pii edge:graph[top.u]){
                int u=top.u;
                int v=edge.first;
                int len=edge.second;
                int curfuel=top.fuel;
                int minfuel = (max(0,len-curfuel));

                for(int k=minfuel; k<=c; k++){
                    if(curfuel+k>c)break;
                    int newfuel = curfuel+k;
                    int cost = top.cost+k*fuelPrice[u];
                    if(cost<dist[v][newfuel-len]){
                        dist[v][newfuel-len]=cost;
                        pq.push(node(v,cost,newfuel-len));
                    }
                }
            }

        }

        int ans=1e6;
        for(int i=0; i<=c; i++){
            setmin(ans,dist[t][i]);
        }
        if(ans==1e6)pf("impossible\n");
        else pf("%d\n",ans);
    }
}

  #define Multiple_Test_Cases
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
