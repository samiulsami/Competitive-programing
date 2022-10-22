#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e6+5;
const int MOD = 1e9+7;
const ll lim = 8LL*MOD*MOD;

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
            	ll cur=0;
                for(int k=0; k<cols; k++){
                    cur += 1LL * mat[i][k] * mtrx.mat[k][j];
                    if(cur>=lim)cur%=MOD;
                }
                ret.mat[i][j] = cur%MOD;
            }
        }
        return ret;
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

inline void solve(int caseNum){
	int t;
	cin>>t;

	while(t--){
		int n;
		cin>>n;
		
		Matrix<int> M({{2, 1}, 
				       {1, 4}});

		// Matrix<int> res({{1,1},{0,0}});
		// for(int i=1; i<n; i++)res = res*M;
		Matrix<int> init({{1,1},{0,0}});
		M = init*fast_exponentiation(M,n-1);

		cout<<(M.mat[0][0]+M.mat[0][1])%MOD<<"\n";
	}

}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}