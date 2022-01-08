#include<bits/stdc++.h>
/*
    Problem: Codeforces Round #223 (Div.1) C. Sereja and Brackets
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define xx first
#define yy second
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
#define dbug(x) cerr<<"dbug: "<<x<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e6+5;

char s[MAX];
struct node{
    int unusedL,unusedR,total;
    node(){unusedL=unusedR=total=0;}
}Tree[2*MAX];
int n;

node combine(node &a, node &b){
    node ret;
    int t = min(a.unusedL,b.unusedR);
    ret.total = a.total + b.total + t;
    ret.unusedL = a.unusedL + b.unusedL - t;
    ret.unusedR = a.unusedR + b.unusedR - t;
    return ret;
}

void build(){
    for(int i=n-1; i>0; i--)Tree[i] = combine(Tree[i<<1],Tree[i<<1|1]);
}

node query(int l, int r){
    l+=n;
    r+=n+1;
    node nodeL,nodeR;
    for(;l<r; l>>=1,r>>=1){
        if(l&1)nodeL = combine(nodeL,Tree[l++]);
        if(r&1)nodeR = combine(Tree[--r],nodeR);
    }
    return combine(nodeL,nodeR);
}

inline void Solve(int Case){
    scanf("%s",&s);
    n=strlen(s);
    for(int i=0; i<n; i++){
        if(s[i]=='(')Tree[i+n].unusedL=1;
        else Tree[i+n].unusedR=1;
    }
    build();

    int m,l,r;
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&l,&r);
        l--,r--;
        printf("%d\n",2*query(l,r).total);
    }
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
