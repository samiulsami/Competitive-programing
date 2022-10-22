#include<bits/stdc++.h>
using namespace std;
/*
    Problem: UVA 10870 - Recurrences
    Verdict: AC
*/
int MOD = 1e9+7;

struct Matrix{

    vector<vector<int> >mat;
    int rows,cols;

    Matrix(){}
    Matrix(vector<vector<int> >val): mat(val), rows((int)val.size()), cols((int)val[0].size()){}

    Matrix operator*(const Matrix &mtrx)const{
        int cur_rows = rows;
        int cur_cols = mtrx.cols;
        assert(cols==mtrx.rows);

        vector<vector<int> >result(cur_rows, vector<int>(cur_cols, 0));

        for(int i=0; i<cur_rows; i++){
            for(int j=0; j<cur_cols; j++){
                    for(int k=0; k<cols; k++){
                        result[i][j] = (result[i][j] + (1LL * mat[i][k] * mtrx.mat[k][j])%MOD)%MOD;
                    }
            }
        }

        return Matrix(result);
    }

};

Matrix identity_matrix(int n){
    vector<vector<int> >val(n, vector<int>(n, 0));
    for(int i=0; i<n; i++)val[i][i]=1;
    return Matrix(val);
}

Matrix fast_exponentiation(Matrix m, long long p){
    assert(m.rows==m.cols);
    Matrix ret = identity_matrix(m.rows);
    while(p){
        if(p&1)ret = ret*m;
        m = m*m;
        p>>=1;
    }
    return ret;
}

int main(){

    long long d,n,m;

    while(cin>>d>>n>>m){

        if(d==0 && n==0 && m==0)break;
        MOD=m;

        vector<vector<int> >mat(1, vector<int>(d)), mat2(d, vector<int>(d,0));

        for(int i=0; i<d; i++)cin>>mat2[i][0];
        for(int i=d-1; i>=0; i--)cin>>mat[0][i];
        for(int i=0; i<d; i++){
            for(int j=1; j<d; j++){
                if(j-1==i)mat2[i][j]=1;
            }
        }

        Matrix initial_matrix(mat);
        Matrix M(mat2);


        if(n<=d)cout<<mat[0][n-d]%MOD<<endl;
        else{
            cout<<(initial_matrix*fast_exponentiation(M,n-d)).mat[0][0]%MOD<<endl;
        }


    }

return 0;
}
