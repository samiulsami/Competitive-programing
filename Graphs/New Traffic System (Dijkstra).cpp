#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;

/*
    problem: LightOJ 1281 - New Traffic System
    verdict: AC
*/

///----------------------------------TEMPLATE START------------------------------------------------------------------------------------------

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;

///using namespace __gnu_pbds;
///typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
///typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;
///typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> Trie;

///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'


#define xx first
#define yy second
#define sf scanf
#define pf printf
#define pb push_back
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define nl printf("\n")
#define FOR(n) for(int i=0; i<n; i++)
int dbugtimes=0;
#define dbug printf("GOT HERE %d time(s)\n",++dbugtimes)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define READ  freopen("input.txt","r",stdin)
#define WRITE freopen("output.txt","w",stdout)

inline bool checkBit(int n, int pos){return bool(n&(1<<pos));}
inline int setBit(int n, int pos){return n|(1<<pos);}
inline int toggleBit(int n, int pos){return n^(1<<pos);}

ll modMul(ll a, ll b, ll mod){///(a*b)%mod
    ll ret=0;
    a%=mod;
    while(b>0){
        if(b&1)ret=(ret+a)%mod;
        b>>=1;
        a=(a<<1)%mod;
    }
    return ret%mod;
}

ll bigMod(ll a, ll b, ll mod){///(a^b)%mod
    if(a==0)return 0;
    ll ret=1;
    a%=mod;
    while(b>0){
        if(b&1)ret=(ret*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ret%mod;
}

ll lcm(ll a, ll b ){return ((a/__gcd(a,b))*b);}

///--------------------Define to enable sieve---------------------------------
    //#define Enable_Sieve

#ifdef Enable_Sieve
const int primesN=400000;
bitset<primesN>status;
vector<int>primes;
void sieve(){
    int sq=sqrt(primesN);
    status[0]=1;
    for(int i=3; i<=sq; i+=2)
        if(!status[i])
            for(int j=i*i; j<=primesN; j+=i+i)
                status[j]=1;
    primes.push_back(2);
    for(int i=3; i<=primesN; i+=2)if(!status[i])primes.push_back(i);
}
#endif


bool isPrime(int n){
    if(n==2)return 1;
    if(n%2==0 || n==1)return 0;

    #ifdef Enable_Sieve
        if(n<=primesN)return !status[n];
        for(int i:primes) if(n%i==0)return 0;
        return 1;
    #else
        for(int i=3; i*i<=n; i+=2)if(n%i==0)return 0;
    #endif

    return 1;
}

///----------------------------------TEMPLATE END/CODE START----------------------------------------------------------------------------------------

const int MAX   = 1e4 + 5;
const int MOD   = 1e9 + 7;
const double EPS   = 1e-10;
const double PI = acos(-1.0);

#define Multiple_test_cases

struct edge{
    int v,w;
    bool proposed=0;
    int proposed_edge_count=0;
    edge(){}
    edge(int v, int w, bool proposed){
        this->v=v;
        this->w=w;
        this->proposed=proposed;
        this->proposed_edge_count=0;
    }
    bool operator<(const edge &a)const{
        if(w==a.w)return proposed_edge_count>a.proposed_edge_count;
        return w>a.w;
    }
};

vector<edge>graph[MAX];
int dist[MAX][12];

void solve(int cases){
    int n,m,k,d,S,T;
    sf("%d%d%d%d",&n,&m,&k,&d);

    for(int i=0; i<=n+1; i++){
        graph[i].clear();
        for(int j=0; j<=d; j++)dist[i][j]=-1;
    }

    S=0;
    T=n-1;
    dist[S][0]=0;

    for(int i=0,u,v,w; i<m; i++){
        siii(u,v,w);
        graph[u].push_back(edge(v,w,0));
    }

    for(int i=0,u,v,w; i<k; i++){
        siii(u,v,w);
        graph[u].push_back(edge(v,w,1));
    }

    priority_queue<edge>pq;
    pq.push(edge(0,0,0));

    while(!pq.empty()){
        edge top=pq.top();
        pq.pop();
        int u=top.v;
        int u_cst=top.w;
        int u_proposed_count=top.proposed_edge_count;

        //if(dist[u][u_proposed_count]<u_cst)continue;

        for(edge e:graph[u]){
            if(u_proposed_count+e.proposed>d)continue;

            int v=e.v;
            int v_cst=e.w;
            int newProposed_count=u_proposed_count+e.proposed;

           if(dist[v][newProposed_count]==-1 || (dist[v][newProposed_count]>u_cst+v_cst)){
                edge newEdge(v,v_cst+u_cst,0);
                newEdge.proposed_edge_count = newProposed_count;
                dist[v][newProposed_count]=v_cst+u_cst;
                pq.push(newEdge);
            }


        }

    }
    int cst=INT_MAX;
    for(int i=0; i<=d; i++){
        if(dist[T][i]!=-1)cst=min(cst,dist[T][i]);
    }

    pf("Case %d: ",cases);
    if(cst==INT_MAX)pf("Impossible\n");
    else pf("%d\n",cst);

}


int main(){
    #ifndef ONLINE_JUDGE
        double start = clock();
        //READ;
        //WRITE;
    #endif

    #ifdef Enable_Sieve
        sieve();
    #endif
    ///fastio;


    #ifdef Multiple_test_cases
        int T;
        scanf("%d", &T);
        for (int cases = 1; cases <= T; cases++) {
            solve(cases);
        }
	#else
		solve(0);
	#endif

    #ifndef ONLINE_JUDGE
        double tim = (clock() - start)/CLOCKS_PER_SEC;
        cerr<<"\n\nRunning Time : "<<tim<<" \n";
    #endif
return 0;
}
