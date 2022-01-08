#include<bits/stdc++.h>
/*
    Problem: https://codeforces.com/gym/102644/ - H. String Mood Updates
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

template<typename T>
struct Matrix{
    T mat[2][2];
    int rows,cols;

    Matrix(){
        rows=2;
        cols=2;
        FOR(i,2)FOR(j,2)mat[i][j]=0;
    }

    Matrix operator*(const Matrix &mtrx)const{
        Matrix ret;
        for(int i=0; i<rows; i++){
            for(int j=0; j<mtrx.cols; j++){
                    for(int k=0; k<cols; k++){
                        ret.mat[i][j] = (ret.mat[i][j] + (1LL * mat[i][k] * mtrx.mat[k][j]))%MOD;
                    }
            }
        }
        return ret;
    }

    void Set(char c){

        ///0=happy, 1=sad
        if(c=='?'){
                mat[0][0]=19;
                mat[0][1]=7;
                mat[1][0]=6;
                mat[1][1]=20;
        }
        else{
                FOR(i,2)FOR(j,2)mat[i][j]=0;
                if(c=='H'){
                    mat[0][0]++;
                    mat[1][0]++;
                }
                else if(c=='S' || c=='D'){
                    mat[1][1]++;
                    mat[0][1]++;
                }
                else if(c=='A' || c=='E' || c=='I' || c=='O' || c=='U'){
                    mat[0][1]++;
                    mat[1][0]++;
                }
                else{
                    mat[1][1]++;
                    mat[0][0]++;
                }
        }


    }
};


Matrix<int> Tree[4*MAX];
char s[MAX];

void build(int node, int l, int r){
    if(l==r){
        Tree[node].Set(s[l-1]);
    }
    else{
        int mid = (l+r)/2;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Tree[node] = Tree[node*2] * Tree[node*2+1];
    }
}

void update(int node, int l, int r, int pos, char newval){
    if(pos>r || pos<l || l>r)return;
    if(l==pos && r==pos)Tree[node].Set(newval);
    else{
        int mid = (l+r)/2;
        if(pos<=mid)update(node*2, l, mid, pos, newval);
        else update(node*2+1, mid+1, r, pos, newval);
        Tree[node] = Tree[node*2] * Tree[node*2+1];
    }
}

Matrix<int> query(int node, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r){
            Matrix<int> ret;
            ret.mat[0][0]=ret.mat[1][1]=1;
            return ret;
    }
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)/2;
    return query(node*2, l, mid, posl, posr) * query(node*2+1, mid+1, r, posl, posr);
}

inline void Solve(int Case){
    int n,q;
    int x;
    char c;
    sii(n,q);
    sf(" %s",&s);
    build(1,1,n);
    //pf("%s",s);
    Matrix<int> Initial;
    Initial.mat[0][0]=1;
    pf("%d\n",(Initial*query(1,1,n,1,n)).mat[0][0]);

    while(q--){
        sf("%d %c",&x,&c);
        //cout<<x<<" "<<c<<" ---- dbug"<<endl;
        update(1,1,n,x,c);
        pf("%d\n",(Initial*query(1,1,n,1,n)).mat[0][0]);
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
