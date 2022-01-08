#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;

/*
    problem: LightOJ 1316 - A Wedding Party
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

inline bool Check(int n, int pos){return bool(n&(1<<pos));}
inline int Set(int n, int pos){return n|(1<<pos);}
inline int unSet(int n, int pos){return n&(~(1<<pos));}

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

const int MAX   = 505;
const int MOD   = 1e9 + 7;
const double EPS   = 1e-10;
const double PI = acos(-1.0);

#define Multiple_test_cases
vector<pii>graph[MAX],Compressed[23];
vector<int>shops;
map<int,int>shopMap;

int dist[MAX][MAX];
pii dp[18][(1<<17)+5];
int goal;
int n,m,s,S,T;
int counter=0;

void dijkstra1(int source){

    dist[source][source]=0;
    priority_queue<pii,vector<pii>,greater<pii> >pq;

    pq.push({0,source});

    while(!pq.empty()){
        pii top=pq.top();
        pq.pop();

        int u=top.yy;
        int u_cst=top.xx;

        if(dist[source][u]<u_cst)continue;

        for(pii edge:graph[u]){
            int v=edge.yy;
            int v_cst=edge.xx;

            if(dist[source][v]==-1 || dist[source][v]>u_cst+v_cst){
                dist[source][v]=u_cst+v_cst;
                pq.push({dist[source][v],v});
            }

        }
    }
}



pii dfs(int u, int mask){
    if(u==T){
        //cout<<"mask: "<<__builtin_popcount(mask)<<endl;
        return {__builtin_popcount(mask), 0};
    }
    pii &ret = dp[u][mask];
    if(ret.xx!=-1)return ret;
    ret={0,999999};

    for(pii v:Compressed[u]){
        if(Check(mask,v.yy))continue;
        pii tmp = dfs(v.yy, Set(mask,v.yy));
        tmp.yy+=v.xx;
        if(tmp.xx>ret.xx)ret=tmp;
        else if(tmp.xx==ret.xx && ret.yy>tmp.yy)ret=tmp;
    }
    return ret;
}


void solve(int cases){
    siii(n,m,s);

    shops.clear();
    shopMap.clear();
    counter=0;
    int ans1=0;
    shopMap[0]=counter++;

    for(int i=0,mx=(1<<(s+2))+2; i<=s; i++){
        for(int j=0; j<=mx; j++)dp[i][j]={-1,-1};
    }

    for(int i=0; i<=n+1; i++){
            graph[i].clear();
            for(int j=0; j<=n+1; j++)dist[i][j]=-1;
    }

    for(int i=0; i<=21; i++){
        Compressed[i].clear();
    }

    int ff=0,ll=0;
    for(int i=0,shop; i<s; i++){
        si(shop);
        if(shop==0)ans1++;
        else if(shop==n-1)ans1++;
        else {
            shopMap[shop]=counter++;
            shops.push_back(shop);
        }
    }

    shopMap[n-1]=counter++;

    for(int i=0,u,v,w; i<m; i++){
        siii(u,v,w);
        graph[u].push_back({w,v});
    }

    for(int shop:shops)dijkstra1(shop);
    dijkstra1(0);
    shops.push_back(0);
    shops.push_back(n-1);

    int len=(int)shops.size();
    S=shopMap[0];
    T=shopMap[n-1];

    for(int i=0; i<len; i++){
        int u=shops[i];
        for(int j=0; j<len; j++){
            if(i==j)continue;
            int v=shops[j];
            int mpv=shopMap[v];
            int mpu=shopMap[u];
            //cout<<mpu<<" "<<mpv<<endl;
            if(dist[u][v]!=-1){
                    Compressed[mpu].push_back({dist[u][v],mpv});
                    //cout<<u<<" "<<v<<endl;
            }
        }
    }

    //cout<<"goal: "<<T<<endl;
    //cout<<"Source: "<<S<<endl;

    pii ans=dfs(S,(1<<S));

    pf("Case %d: ",cases);
    if(ans.xx>0)pf("%d %d\n",ans.xx-(2-ans1),ans.yy);
    else if(dist[0][n-1]!=-1){
            //pf("came here\n");
            pf("%d %d\n",ans1,dist[0][n-1]);
    }
    else pf("Impossible\n");


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
