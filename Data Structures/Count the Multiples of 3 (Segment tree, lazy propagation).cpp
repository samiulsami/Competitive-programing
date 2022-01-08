#include<bits/stdc++.h>
/*
    Problem: LightOJ 1135 - Count the Multiples of 3
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

int Tree[4*MAX][3];
int lazy[4*MAX]={0};
int n;

void build(int node, int l, int r){
    lazy[node]=0;
    if(l==r){
        for(int i=0; i<3; i++)Tree[node][i] = (int)(i==0);
    }
    else{
        int mid = (l+r)/2;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        for(int i=0; i<3; i++)Tree[node][i] = Tree[node*2][i] + Tree[node*2+1][i];
    }
}

inline void push_update(int node, int l, int r){
    if(lazy[node]!=0){
        for(int i=0; i<lazy[node]; i++){
            Tree[node][0]=Tree[node][2];
            Tree[node][2]=Tree[node][1];
            Tree[node][1]=(r-l+1)-Tree[node][0]-Tree[node][2];
        }
        if(l!=r){
            lazy[node*2]+=lazy[node];
            lazy[node*2]%=3;
            lazy[node*2+1]+=lazy[node];
            lazy[node*2+1]%=3;
        }
        lazy[node]=0;
    }
}

void range_update(int node, int l, int r, int posl, int posr, int add){
    push_update(node,l,r);
    if(posl>r || posr<l)return;
    if(l>=posl && r<=posr){
            Tree[node][0]=Tree[node][2];
            Tree[node][2]=Tree[node][1];
            Tree[node][1]=(r-l+1)-Tree[node][0]-Tree[node][2];
            if(l!=r){
                lazy[node*2]+=add;
                lazy[node*2]%=3;
                lazy[node*2+1]+=add;
                lazy[node*2+1]%=3;
            }
    }
    else{
        int mid = (l+r)/2;
        range_update(node*2, l, mid, posl, posr, add);
        range_update(node*2+1, mid+1, r, posl, posr, add);
        for(int i=0; i<3; i++)Tree[node][i] = Tree[node*2][i] + Tree[node*2+1][i];
    }
}


int query(int node, int l, int r, int posl, int posr){
    push_update(node,l,r);
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return Tree[node][0];
    int mid = (l+r)/2;
    return query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr);
}


inline void Solve(int Case){
    int q,Q,x,y;
    sii(n,q);

    build(1,1,n);

    pf("Case %d:\n",Case);
    while(q--){
        siii(Q,x,y);
        x++;
        y++;
        if(Q==0){
            range_update(1,1,n,x,y,1);
        }
        else{
            pf("%d\n",query(1,1,n,x,y));
        }
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
