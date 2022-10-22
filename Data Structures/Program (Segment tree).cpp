#include<bits/stdc++.h>
/*
    Problem: Educational Codeforces Round 102 (Rated for Div. 2) - D. Program
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

struct Node{
    int x,y;
    Node(){}
    Node(int x, int y):x(x),y(y){}
}Tree[4*MAX];
int arr[MAX];

inline Node Combine(Node a, Node b){
    return Node(max(a.x, b.x), min(a.y, b.y));
}

void build(int node, int l, int r){
    if(l==r)Tree[node].x=Tree[node].y=arr[l];
    else{
        int mid = (l+r)/2;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Tree[node] = Combine(Tree[node*2], Tree[node*2+1]);
    }
}

Node query(int node, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r)return Node(-2e6,2e6);
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)/2;
    return Combine(query(node*2, l, mid, posl, posr), query(node*2+1, mid+1, r, posl, posr));
}

inline void Solve(int Case){
    int n,q;
    cin>>n>>q;

    arr[0]=0;
    arr[1]=0;
    string s;
    cin>>s;
    int ind=2;
    for(int i=0; i<n; i++,ind++){
        if(s[i]=='+')arr[ind]=arr[ind-1]+1;
        else arr[ind]=arr[ind-1]-1;
    }

    n++;
    build(1,1,n);
    while(q--){
        int x,y;
        cin>>x>>y;
        x++;
        y++;
        int diff = arr[y]-arr[x-1];
        int minn = min(query(1,1,n,1,x-1).y, query(1,1,n,y+1,n).y-diff);
        int maxx = max(query(1,1,n,1,x-1).x, query(1,1,n,y+1,n).x-diff);
        maxx=max(0,maxx);
        minn=min(0,minn);

        //dbug(maxx);
        //dbug(minn);
        cout<<maxx-minn+1<<endl;
    }

}

  #define Multiple_Test_Cases
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        cin>>T;
        //si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
