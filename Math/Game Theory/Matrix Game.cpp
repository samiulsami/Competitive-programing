#include<iostream>

using namespace std;

int main(){
long long int T,cases=0,m,n,tmp;
cin>>T;
while(T--){
    cin>>m>>n;
    long long int x[m+1];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin>>tmp;
            if(j==0)x[i]=tmp;
            else x[i]+=tmp;
        }
    }
    x[m]=x[0];
    for(int i=1; i<m; i++)x[m]^=x[i];
    if(x[m]>0)cout<<"Case "<<++cases<<": Alice"<<endl;
    else cout<<"Case "<<++cases<<": Bob"<<endl;
}
return 0;
}
