#include<bits/stdc++.h>
/*
    Problem: 2020 ICPC Gran Premio de Mexico 3ra Fecha - G. Gold Fever
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

int Tree[4*MAX];
struct node{
    int val,x,y;
}arr[MAX];
int n;

void build(int node, int l, int r){
    if(l==r)Tree[node]=0;
    else{
        int mid = (l+r)/2;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Tree[node] = max(Tree[node*2], Tree[node*2+1]);
    }
}

void update(int node, int l, int r, int pos, int newval){
    if(pos>r || pos<l || l>r)return;
    if(l==pos && r==pos)Tree[node]=newval;
    else{
        int mid = (l+r)/2;
        if(pos<=mid)update(node*2, l, mid, pos, newval);
        else update(node*2+1, mid+1, r, pos, newval);
        Tree[node] = max(Tree[node*2], Tree[node*2+1]);
    }
}

int query(int node, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r)return 0;
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)/2;
    return max(query(node*2, l, mid, posl, posr), query(node*2+1, mid+1, r, posl, posr));
}

inline void Solve(int Case){
    int n;
    si(n);
    build(1,1,n);
    for(int i=1; i<=n; i++)siii(arr[i].val,arr[i].x,arr[i].y);

    for(int i=n; i>0; i--){
        int newx=arr[i].x+i;
        int newy=arr[i].y+i;
        if(newx>n)update(1,1,n,i,arr[i].val);
        else{
            newy=min(n,newy);
            update(1,1,n,i,query(1,1,n,newx,newy)+arr[i].val);
        }
    }

    pf("%d\n",query(1,1,n,1,n));

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
