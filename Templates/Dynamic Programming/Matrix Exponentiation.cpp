#include<bits/stdc++.h>
using namespace std;

int MOD = 1e9+7;

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

int main(){
    long long n;

    Matrix<int> m({{1,1},
                   {1,0}});

    Matrix<int> initial_matrix({{1,1}});///F(1), F(0)

    ///UVA 10229 - Modular Fibonacci
    while(cin>>n>>MOD){
        if(n==0){
            cout<<0<<endl;
            continue;
        }
        MOD = (1<<MOD);
        //cout<<"Fibonnaci("<<n<<") mod "<<MOD<<" = ";
        cout<<(initial_matrix*fast_exponentiation(m, n-1)).mat[0][1]<<endl;
    }

return 0;
}
