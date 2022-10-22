#include<iostream>

using namespace std;

int main(){
    long long int n,p;
    while(cin>>n){
    if(n==0)break;
    p=1;
    bool stan=0;
    while(true){
        stan=!stan;
        if(stan)p*=9;
        else p*=2;
        if(n<=p)break;
    }
    if(stan)cout<<"Stan wins."<<endl;
    else cout<<"Ollie wins."<<endl;
    }
return 0;
}
