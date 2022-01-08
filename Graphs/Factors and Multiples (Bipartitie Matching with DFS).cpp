#include<bits/stdc++.h>
/*
    Problem: LightOJ 1149 - Factors and Multiples
    verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%d",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(n) for(int i=0; i<=n; i++)
#define FORR(l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const int MAX = 400;
const double PI = 2*acos(0.0);

bool vis[MAX];
vector<int>graph[MAX];
int matchR[MAX];

bool match(int lft){
    if(vis[lft])return 0;
    vis[lft]=1;

    for(int r:graph[lft]){
        if(matchR[r]==-1 && !vis[r]){
            matchR[r]=lft;
            return 1;
        }
    }

    for(int r:graph[lft]){
        if(match(matchR[r])){
            matchR[r]=lft;
            return 1;
        }
    }

    return 0;
}

int bpm(int n){
    int ans=0;
    for(int i=0; i<n; i++){
         memset(vis,0,sizeof(vis));
         if(match(i))ans++;
    }
    return ans;
}

int setA[105],setB[105];

inline void Solve(int Case){
    int n,m,i;

    for(si(n),i=0; i<n; i++)si(setA[i]);
    for(si(m),i=0; i<m; i++)si(setB[i]);

    for(int i=0; i<=n+m+5; i++){
        graph[i].clear();
        matchR[i]=-1;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(setB[j]%setA[i]==0)graph[i].push_back(j+n);
        }
    }

    printf("Case %d: %d\n",Case, bpm(n));
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
