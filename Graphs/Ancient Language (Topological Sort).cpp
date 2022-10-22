#include<bits/stdc++.h>
/*
    Problem: Bubble Cup 13 - Finals [Codeforces Online Mirror, unrated, Div. 2] - M - Ancient Language
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
const int MAX = 1e5+5;

vector<string>pages[1004];
vector<int>graph[150];
int vis[150]={0};
stack<int>topoSort;

void dfs(int u){
    vis[u]=1;
    for(int v:graph[u]){
        if(vis[v]==2)continue;
        if(vis[v]==1){
            cout<<"IMPOSSIBLE";
            exit(0);
        }
        dfs(v);
    }
    topoSort.push(u);
    vis[u]=2;
}

inline void Solve(int Case){
    int n,k;
    string s;
    cin>>n>>k;
    int val=0;
    int abc[150]={0};
    FOR(i,n-1){
        int ind;
        cin>>ind;
        FOR(j,k-1){
            cin>>s;
            pages[ind].pb(s);
        }
    }
    vector<string>sorted;
    for(int i=0; i<n; i++){
        for(string page:pages[i]){
            sorted.pb(page);
            for(char c:page)abc[c]=1;
        }
    }

    int sz = sorted.size();
    for(int i=1; i<sz; i++){
        int asize = sorted[i-1].size();
        int bsize = sorted[i].size();
        int minsz = min(asize,bsize);
        bool flag=1;

        for(int j=0; j<minsz; j++){
            char x = sorted[i-1][j];
            char y = sorted[i][j];
            if(x!=y){
                graph[x].pb(y);
                flag=0;
                break;
            }
        }

        if(flag && asize>bsize){
            cout<<"IMPOSSIBLE";
            exit(0);
        }
    }

    for(int i='a'; i<='z'; i++){
        if(!vis[i] && abc[i])dfs(i);
    }

    while(!topoSort.empty()){
        int top=topoSort.top();
        topoSort.pop();
        cout<<(char)top;
    }

}

  //#define Multiple_Test_Cases
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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
