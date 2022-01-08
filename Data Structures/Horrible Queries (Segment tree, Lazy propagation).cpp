#include<bits/stdc++.h>
/*
    Problem: LightOJ 1164 - Horrible Queries
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

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e5+5;

template<typename T>
struct segTreeLazy{
    struct TreeNode{
        T data,lazy;
    };
    vector<TreeNode>Tree;

    segTreeLazy(){}
    segTreeLazy(int n):Tree(4*n){}
    void build(int node, int l, int r){
        if(l==r){
                Tree[node].data=0;
                Tree[node].lazy=0;
        }
        else{
            int mid = (l+r)>>1;
            build(node*2,l,mid);
            build(node*2+1,mid+1,r);
            Tree[node].data = Tree[node*2].data + Tree[node*2+1].data;
        }
    }

    inline void push_update(int node, int l, int r){
        if(Tree[node].lazy!=0){
            Tree[node].data += T(r-l+1)*Tree[node].lazy;
            if(l!=r){
                Tree[node*2].lazy+=Tree[node].lazy;
                Tree[node*2+1].lazy+=Tree[node].lazy;
            }
            Tree[node].lazy=0;
        }
    }

    void range_update(int node, int l, int r, int posl ,int posr, T val){
        push_update(node,l,r);
        if(posl>r || posr<l || l>r)return;
        if(l>=posl && r<=posr){
            Tree[node].lazy+=val;
            push_update(node,l,r);
        }
        else{
            int mid = (l+r)>>1;
            range_update(node*2, l, mid, posl, posr, val);
            range_update(node*2+1, mid+1, r, posl, posr, val);
            Tree[node].data = Tree[node*2].data + Tree[node*2+1].data;
        }
    }

    T query(int node, int l, int r, int posl, int posr){
        push_update(node,l,r);
        if(l>posr || r<posl || l>r)return 0;
        if(l>=posl && r<=posr)return Tree[node].data;
        int mid = (l+r)>>1;
        return query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr);
    }
};
segTreeLazy<ll> segTree(MAX);

inline void Solve(int Case){
    int n,q;
    sii(n,q);
    for(int i=0; i<=4*n; i++)segTree.Tree[i].data=segTree.Tree[i].lazy=0;
    pf("Case %d:\n",Case);
    while(q--){
        int Q,x,y,v;
        si(Q);
        if(Q==0){
            siii(x,y,v);
            x++,y++;
            segTree.range_update(1,1,n,x,y,v);
        }
        else{
            sii(x,y);
            x++,y++;
            pf("%lld\n",segTree.query(1,1,n,x,y));
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
