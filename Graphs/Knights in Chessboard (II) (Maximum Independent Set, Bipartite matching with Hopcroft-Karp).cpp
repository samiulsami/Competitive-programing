#include<bits/stdc++.h>
/*
    Problem: LightOJ 1171 - Knights in Chessboard (II)
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<=n; i++)
#define FORR(i,l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl
#define eikhane cout<<"Eikhane"<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 210;

bool bw[210][210];
bool blocked[210][210];

int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int n,m,k;

inline int calc(int i, int j){
    return (i*m)+j;
}

vector<int>graph[MAX*MAX];
int match[MAX*MAX];
int dist[MAX*MAX];

bool bfs(){
    queue<int>q;
    for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!bw[i][j])continue;
                int val = calc(i,j);

                if(match[val]==-1){
                    dist[val]=0;
                    q.push(val);
                }
                else dist[val]=-1;
            }
    }
    bool flag=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int v:graph[u]){
            if(match[v]==-1)flag=1;
            else if(dist[match[v]] == -1){
                dist[match[v]] = dist[u]+1;
                q.push(match[v]);
            }
        }
    }
    return flag;
}

bool dfs(int u){
    for(int v:graph[u]){
        if(match[v]==-1 || (dist[match[v]] == dist[u]+1 && dfs(match[v]))){
                match[v]=u;
                match[u]=v;
                return true;
        }
    }
    dist[u]=-1;
    return false;
}

int hopcroft_karp(){
    int matching=0;
    memset(match,-1,sizeof(match));
    while(bfs()){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!bw[i][j])continue;
                int val = calc(i,j);
                if(match[val]==-1 && dfs(val))
                    matching++;
            }
        }
    }
    return matching;
}

inline void Solve(int Case){

    siii(n,m,k);
    memset(blocked,0,sizeof(blocked));
    FOR(i,n*m+5){
        graph[i].clear();
    }

    FOR(i,k-1){
        int x,y;
        sii(x,y);
        blocked[x-1][y-1]=1;
    }

    FOR(i,n-1){
        FOR(j,m-1){
            if(blocked[i][j])continue;

            if(bw[i][j]){
                    FOR(k,7){
                        int newi=i+dx[k];
                        int newj=j+dy[k];

                        if(!(newi>=0 && newi<n) || !(newj>=0 && newj<m))continue;
                        if(blocked[newi][newj])continue;

                        graph[calc(i,j)].push_back(calc(newi,newj));
                    }
            }

        }
    }
    pf("Case %d: %d\n",Case, (n*m)-k-hopcroft_karp());

}

  #define Multiple_Test_Cases

int main(){
    FOR(i,207)
        FOR(j,207)
            bw[i][j]=(i+j)%2;

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
