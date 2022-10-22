#include<bits/stdc++.h>
/*
    Problem: Codeforces Round #693 (Div. 3) - E. Correct Placement
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
const int MAX = 2e5+5;

struct node{
    int h,w,ind;
    node(){}
    bool operator<(const node &nd)const{
        if(h==nd.h)return w<nd.w;
        return h<nd.h;
    }
}arr[MAX];

pii Tree[4*MAX];
int n;

void build(int node, int l, int r){
    if(l==r)Tree[node] = {arr[l].w, arr[l].ind};
    else{
        int mid = (l+r)/2;
        build(node*2,l,mid);
        build(node*2+1,mid+1,r);
        Tree[node] = min(Tree[node*2],Tree[node*2+1]);
    }
}

pii query(int node, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r)return {INT_MAX, INT_MAX};
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)/2;
    return min(query(node*2, l, mid, posl, posr), query(node*2+1, mid+1, r, posl, posr));
}

int check(int h, int w){
    if(arr[1].h>=h)return -1;

    int low=1,high=n,mid;
    int maxind=-1;

    while(low<=high){
        mid=(low+high)/2;
        if(arr[mid].h>=h)high=mid-1;
        else {
            maxind=max(mid,maxind);
            low=mid+1;
        }
    }

    pii q = query(1,1,n,1,maxind);

    if(q.FF<w)return q.SS;
    return -1;
}

inline void Solve(int Case){
    si(n);
    FOR(i,n){
        sii(arr[i+1].h,arr[i+1].w);
        arr[i+1].ind=i+1;
    }

    sort(arr+1,arr+n+1);
    //for(int i=0; i<n; i++)cout<<pii(arr[i].h,arr[i].w)<<endl;
    build(1,1,n);
    vi ans(n+1);

    fill(ans.begin(),ans.end(),-1);

    FOR(i,n){
        ans[arr[i+1].ind]=check(arr[i+1].h,arr[i+1].w);
        if(ans[arr[i+1].ind]==-1)ans[arr[i+1].ind]=check(arr[i+1].w,arr[i+1].h);
    }

    FOR(i,n)pf("%d ",ans[i+1]);
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
