#include<bits/stdc++.h>
/*
    Problem: SPOJ TAXI - Taxi
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
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
#define CHK cerr<<"----------------\nCAME HERE\n----------------\n";

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 8005;

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

inline void Solve(int Case){
    int p,t,s,c;
    sii(p,t);
    sii(s,c);

    HopcroftKarp hk(p+t);
    vector<pii>people,taxis;
    int xx,yy;

    FOR(i,p){
        sii(xx,yy);
        people.push_back({xx,yy});
    }

    FOR(i,t){
        sii(xx,yy);
        taxis.push_back({xx,yy});
    }

    for(int i=0; i<taxis.size(); i++){
        pii taxi = taxis[i];

        for(int j=0; j<people.size(); j++){
            pii person = people[j];

            int distance = abs(taxi.FF-person.FF) + abs(taxi.SS-person.SS);
            distance*=200;

            if(distance/s<=c)hk.addEdge(i,j+t);
        }
    }

    pf("%d\n",hk.bpm());

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
