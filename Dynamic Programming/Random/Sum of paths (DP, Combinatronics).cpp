#include<bits/stdc++.h>
/*
    Problem: Codeforces Round #695 (Div. 2) - D. Sum of Paths
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
const int MAX = 1e5+5;

ll dp[5002][5002];
ll dp1[5002][5002];
ll cnt[5002]={0};
ll arr[5002];
int n,k,q;

ll f1(int i, int len){
    if(len==k)return 1;
    ll &ret = dp1[i][len];
    if(~ret)return ret;

    ret=0;
    if(i>0)ret = (ret+f1(i-1,len+1))%MOD;
    if(i<n-1)ret = (ret+f1(i+1,len+1))%MOD;
    return ret;
}

ll f(int i, int len){
    if(len==0)return 1;
    ll &ret = dp[i][len];
    if(~ret)return ret;

    ret=0;
    if(i>0)ret = (ret+f(i-1,len-1))%MOD;
    if(i<n-1)ret = (ret+f(i+1,len-1))%MOD;
    return ret;
}

inline void Solve(int Case){
    memset(dp,-1,sizeof(dp));
    memset(dp1,-1,sizeof(dp1));

    siii(n,k,q);
    ll ans=0;

    for(int i=0; i<n; i++){
        si(arr[i]);
        for(int j=0; j<=k; j++)
            cnt[i] = (cnt[i]+(f(i,j)*f1(i,j)%MOD))%MOD;

        ans = (ans+(cnt[i]*arr[i])%MOD)%MOD;
    }

    int a,b;
    while(q--){
        sii(a,b);
        a--;
        ans-=(cnt[a]*arr[a])%MOD;
        ans+=MOD;
        ans%=MOD;

        arr[a]=b;
        ans+=(cnt[a]*arr[a])%MOD;
        ans%=MOD;
        pf("%lld\n",ans);
    }

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
