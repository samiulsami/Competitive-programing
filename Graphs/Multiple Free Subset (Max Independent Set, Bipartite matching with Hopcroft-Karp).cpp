#include<bits/stdc++.h>
/*
    Problem: LightOJ 1218 - Multiple Free Subset
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
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define eikhane cerr<<"Eikhane"<<endl

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
const int MAX = 205;

bool mark[MAX],tmpMark[MAX];
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
            if(mark[i])continue;
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
            if(mark[u])continue;
            for(int v:graph[u]){
                if(mark[v])continue;
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
        if(mark[u])return false;
        for(int v:graph[u]){
            if(mark[v])continue;
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
                if(mark[i])continue;
                if(matchL[i]==-1 && dfs(i))
                    matching++;
            }
        }
        return matching;
    }
};

inline void Solve(int Case){
    int n;
    vi arr;
    si(n);
    set<int>st;
    int x;
    FOR(i,n-1){
        si(x);
        st.insert(x);
    }

    for(int i:st)arr.pb(i);
    n=(int)arr.size();

    HopcroftKarp hk(n);

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[j]%arr[i]==0){
                hk.addEdge(i,j);
            }
        }
    }

    vi ans;
    memset(mark,0,sizeof(mark));
    int mx = n-hk.bpm();
    //dbug(mx);
    int marked=0;
    for(int i=n-1; i>=0; i--){
        mark[i]=1;
        marked++;
        if(n-marked-hk.bpm()!=mx){
            ans.pb(arr[i]);
            mark[i]=0;
            marked--;
        }
    }

    pf("Case %d:",Case);
    for(int i=mx-1; i>=0; i--)pf(" %d",ans[i]);
    nl;
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
