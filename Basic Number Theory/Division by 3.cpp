#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;

/*
    problem: LightOJ 1136 - Division by 3
    verdict: AC
*/

///----------------------------------TEMPLATE START------------------------------------------------------------------------------------------

typedef long long ll;
typedef long double ld;
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
#define sl(s) scanf("%lld",&x)
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

/// Sieve start
/*
const int primesN=400000;
bool status[(primesN>>1)+2]={0};
vector<int>primes;
void sieve(){
    int sq=sqrt(primesN);
    status[0]=1;
    for(int i=3; i<=sq; i+=2)
        if(!status[i>>1])
            for(int j=i*i; j<=primesN; j+=i+i)
                status[j>>1]=1;
    primes.push_back(2);
    for(int i=3; i<=primesN; i+=2)if(!status[i>>1])primes.push_back(i);
}
*/
/// Sieve end

bool isPrime(int n){
    if(n==2)return 1;
    if(n%2==0 || n==1)return 0;

    //if(n<=primesN)return !status[n>>1];
    //for(int i:primes) if(n%i==0)return 0;
    //return 1;

    //without sieve
    for(int i=3; i*i<=n; i+=2)if(n%i==0)return 0;
    return 1;
}

///----------------------------------TEMPLATE END/CODE START----------------------------------------------------------------------------------------

const int MAX   = 1e5 + 5;
const int MOD   = 1e9 + 7;
const double EPS   = 1e-10;
const double PI = acos(-1.0);

/*string its(int val){
    string ret;
    while(val>0){
        ret+=(char)(val%10 + '0');
        val/=10;
    }

    reverse(ret.begin(),ret.end());
    return ret;
}

ll f(int n){
    string s;
    for(int i=1; i<=n; i++){
            s=s+its(i);
    }
    ll ret=0;
    ll power=1;
    for(int i=0,len=s.length(); i<len; i++){
        ret+=s[i]-'0';
        ret*=10;
    }
    return ret/10;
}*/

int f(int n){
    if(n<=0)return 0;
    return (n/3)*2 + (n%3==2);
}

void solve(int cases){
    /*for(int i=1; i<=20; i++){
        //cout<<"val: "<<f(i)<<endl;
        cout<<i<<": "<<f(i)%3LL<<endl;
    }*/
    int a,b;
    cin>>a>>b;
    cout<<"Case "<<cases<<": "<<f(b)-f(a-1)<<endl;
}

int main(){
    #ifndef ONLINE_JUDGE
        double start = clock();
        //READ;
        //WRITE;
    #endif
    ///fastio;
    ///sieve();
    if(1){
        int T;
        scanf("%d", &T);
        for (int cases = 1; cases <= T; cases++) {
            solve(cases);
        }
    }
	else {
		solve(0);
	}

    #ifndef ONLINE_JUDGE
        double tim = (clock() - start)/CLOCKS_PER_SEC;
        cerr<<"Running Time : "<<tim<<" \n";
    #endif
return 0;
}
