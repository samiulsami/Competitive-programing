#include<bits/stdc++.h>
/*
    Problem: LightOJ 1356 - Prime Independence
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
const int MAX = 40005;
const int primesN=500005;
bitset<primesN>status;
vector<int>primes;

void sieve(){///Generates prime numbers from [1,n] in O(nloglogn) (n=primesN)
    int sq=sqrt(primesN);
    status[0]=1;
    for(int i=3; i<=sq; i+=2)
        if(!status[i])
            for(int j=i*i; j<=primesN; j+=i+i)
                status[j]=1;
    primes.push_back(2);
    for(int i=3; i<=primesN; i+=2)if(!status[i])primes.push_back(i);
}

vector<int>graph[MAX],nums;
int match[MAX];
int dist[MAX];
int color[MAX];
int n;

void bicolor(int u, int col){
    color[u]=col;
    for(int v:graph[u]){
        if(v==u || color[v]!=-1)continue;
        bicolor(v,col^1);
    }
}

bool bfs(){
    queue<int>q;
    for(int i=0; i<n; i++){
        if(color[i])continue;
        if(match[i]==-1){
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
            if(color[i])continue;
            if(match[i]==-1 && dfs(i))
                matching++;
        }
    }
    return matching;
}

int numbers[500005];

inline void Solve(int Case){

    memset(numbers,-1,sizeof(numbers));
    memset(color,-1,sizeof(color));
    si(n);
    nums.clear();
    int low=INT_MAX,high=-1;
    FOR(i,n-1){
        int x;
        si(x);
        numbers[x]=i;
        nums.pb(x);
        low=min(low,x);
        high=max(high,x);
    }

    for(int i=0; i<=n; i++)graph[i].clear();

    for(int i=0; i<n; i++){
        int num = nums[i];
        for(int p:primes){
            if(num*p>high)break;
            int j = numbers[num*p];
            if(j!=-1){
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    for(int i=0; i<n; i++){
        if(color[i]==-1)bicolor(i,0);
    }

    pf("Case %d: %d\n",Case, n-hopcroft_karp());

}

  #define Multiple_Test_Cases
int main(){
    sieve();
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
