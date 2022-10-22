#include<iostream>

using namespace std;

int main(){
long long int T,cases=0,n;
cin>>T;
while(T--){
    int a,b,x;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>a>>b;
        if(i==0)x = b-a-1;
        else x^=(b-a-1);
    }
    cout<<"Case "<<++cases<<": ";
    if(x>0)cout<<"Alice"<<endl;
    else cout<<"Bob"<<endl;


}

return 0;
}
