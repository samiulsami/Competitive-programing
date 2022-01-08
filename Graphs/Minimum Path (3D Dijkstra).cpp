#include<bits/stdc++.h>
/*
    Problem: Educational Codeforces Round 102 (Rated for Div. 2) - E. Minimum Path
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
const int MAX = 2e5+5;

struct node{
    bool mintaken,maxtaken;
    ll v,weight;
    node(){
        mintaken=0;
        maxtaken=0;
    }
    bool operator<(const node &nd)const{
        return weight>nd.weight;
    }
};

ll dist[MAX][2][2];
vector<node>graph[MAX];

inline void Solve(int Case){
    int n,m;
    sii(n,m);

    for(int i=0; i<=n; i++){
        for(int j=0; j<2; j++){
            for(int k=0; k<2; k++){
                     dist[i][j][k]=1e18;
            }
        }
    }

    for(int i=0,u,v,w; i<m; i++){
        siii(u,v,w);
        node newnode;
        newnode.v=v;
        newnode.weight=w;
        graph[u].emplace_back(newnode);
        newnode.v=u;
        graph[v].emplace_back(newnode);
    }

    priority_queue<node>pq;
    node src;
    src.v=1;
    src.mintaken=0;
    src.maxtaken=0;
    src.weight=0;
    dist[1][0][0]=0;
    pq.push(src);

    while(!pq.empty()){
        node top = pq.top();
        pq.pop();

        if(dist[top.v][top.mintaken][top.maxtaken]<top.weight)continue;
        for(node &edge:graph[top.v]){
            int vv=edge.v;

            ll weight=top.weight+edge.weight;

            if(dist[vv][top.mintaken][top.maxtaken]>weight){
                dist[vv][top.mintaken][top.maxtaken]=weight;
                node nxt = top;
                nxt.v=vv;
                nxt.weight=weight;
                pq.emplace(nxt);
            }

            if(!top.maxtaken){
                ll tmp = top.weight;
                if(dist[vv][top.mintaken][1]>tmp){
                    dist[vv][top.mintaken][1]=tmp;
                    node nxt;
                    nxt.v=vv;
                    nxt.weight = tmp;
                    nxt.maxtaken=1;
                    nxt.mintaken=top.mintaken;
                    pq.emplace(nxt);
                }
            }

            if(!top.mintaken){
                ll tmp = top.weight+2*edge.weight;
                if(dist[vv][1][top.maxtaken]>tmp){
                    dist[vv][1][top.maxtaken]=tmp;
                    node nxt;
                    nxt.v=vv;
                    nxt.weight=tmp;
                    nxt.mintaken=1;
                    nxt.maxtaken=top.maxtaken;
                    pq.emplace(nxt);
                }
            }

            if(!top.mintaken && !top.maxtaken){
                ll tmp = top.weight+edge.weight;
                if(dist[vv][1][1]>tmp){
                    dist[vv][1][1]=tmp;
                    node nxt;
                    nxt.v=vv;
                    nxt.weight=tmp;
                    nxt.mintaken=1;
                    nxt.maxtaken=1;
                    pq.emplace(nxt);
                }
            }

        }

    }

    for(int i=2; i<=n; i++)pf("%lld ",dist[i][1][1]);

}

  //#define Multiple_Test_Cases
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
