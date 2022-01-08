#include<bits/stdc++.h>
/*
    Problem: UVA 10754 - Fantastic Sequence
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
ll MOD = 1e9+7;
const int MAX = 1e5+5;

template<typename T>
struct Matrix{
    vector<vector<T> >mat;
    int rows,cols;

    Matrix(){}
    Matrix(int rows, int cols):rows(rows),cols(cols),mat(rows, vector<T>(cols,0)){}
    Matrix(vector<vector<T> >val): mat(val), rows((int)val.size()), cols((int)val[0].size()){}

    Matrix operator*(const Matrix &mtrx)const{
        Matrix ret(rows,mtrx.cols);
        for(int i=0; i<rows; i++){
            for(int j=0; j<mtrx.cols; j++){
                    for(int k=0; k<cols; k++){
                        ret.mat[i][j] = (ret.mat[i][j] + (1LL * mat[i][k] * mtrx.mat[k][j])%MOD)%MOD;
                    }
            }
        }
        return ret;
    }

    void printMat(){
        FOR(i,rows){
            FOR(j,cols)pf("%lld ",mat[i][j]);
            nl;
        }
    }
};

template<typename T>
Matrix<T> fast_exponentiation(Matrix<T> m, long long p){
    Matrix<T> ret(m.rows,m.rows);
    for(int i=0; i<ret.rows; i++)ret.mat[i][i]=1;
    while(p){
        if(p&1)ret = ret*m;
        m = m*m;
        p>>=1;
    }
    return ret;
}

ll C[30];
ll arr[30];
bool first=1;

inline void Solve(int Case){
    if(first)first=0;
    else nl;

    ll k,n;
    slll(k,MOD,n);

    Matrix<ll> initial(1,k+k+1), M(k+k+1,k+k+1);
    FOR(i,k+1){
        sl(C[i]);
        C[i]+=MOD;
        C[i]%=MOD;
    }

    FOR(i,k){
        sl(arr[i]);
        arr[i]+=MOD;
        arr[i]%=MOD;

    }

    for(int i=k-1; i>=0; i--)initial.mat[0][i]=arr[k-i-1];
    for(int i=k; i<k+k+1; i++)initial.mat[0][i]=C[i-k];


    for(int j=0; j<k; j++)M.mat[j][0]=C[j];
    M.mat[k+k][0]=1;

    for(int i=1; i<k; i++)M.mat[i-1][i]=1;
    for(int i=k; i<k+k+1; i++)M.mat[i][i]=1;

    ll ans;
    if(n<k)ans=arr[n];
    else ans = (initial*fast_exponentiation(M,n-k+1)).mat[0][0];

    ans%=MOD;
    pf("%lld\n",ans);
}
/*
2
2 423 3
3 4 5
6 7

*/
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
