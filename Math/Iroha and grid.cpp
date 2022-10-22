#include<bits/stdc++.h>
/*
    Problem: Atcoder Beginner contest 42 - D. Iroha and grid
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
#define si2(x,y) scanf("%d%d",&x,&y)
#define si3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sl2(x,y) scanf("%lld%lld",&x,&y)
#define sl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
#define SZ(x) (int)x.size()
#define ALL(x) x.begin(),x.end()
#define PB emplace_back
#define CHK cerr<<"----------------\nCAME HERE\n----------------\n";

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
template<typename T>inline bool setmax(T &a, T &b){return b>a?a=b,1:0;}
template<typename T>inline bool setmin(T &a, T &b){return b<a?a=b,1:0;}

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e5+5;

vector<ll>factorials({1,1}),numInv({1,1}),factorialsInv({1,1});

ll nCrmod(int n, int r){
    if(n<r || n<0 || r<0)return 0;
    if((int)factorials.size()<=n){
        for(ll i=(int)factorials.size(); i<=n+1; i++){
            numInv.push_back((numInv[MOD%i]*(MOD-(MOD/i)))%MOD);
            factorialsInv.push_back((numInv.back()*factorialsInv.back())%MOD);
            factorials.push_back((factorials.back()*i)%MOD);
        }
    }
    return ((factorials[n]*factorialsInv[r])%MOD * factorialsInv[n-r])%MOD;
}

inline void Solve(int Case){
    int h,w,a,b;
    si2(h,w);
    si2(a,b);

    ll ans=0;

    for(int i=b+1; i<=w; i++){
        int down1 = h-a-1;
        int right1 = i-1;
        int down2 = a-1;
        int right2 = w-i;
        ans = ans+(nCrmod(down1+right1,down1) * nCrmod(down2+right2,down2))%MOD;
        ans%=MOD;
    }

    pf("%lld\n",ans);

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
