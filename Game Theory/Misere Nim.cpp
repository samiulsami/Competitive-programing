#include<iostream>

using namespace std;

int main(){
long long int T, cases=0,k;
cin>>T;
while(T--){
    long long int x,y,xorsum=0;
    bool all1=1;
    cin>>k;
    for(int i=0; i<k; i++){
        cin>>x;
        if(x!=1)all1=0;
        xorsum^=x;
    }
    cout<<"Case "<<++cases<<": ";
    if(all1 && k%2)cout<<"Bob";
    else if(all1 && k%2==0)cout<<"Alice";
    else if(xorsum>0)cout<<"Alice";
    else cout<<"Bob";
    cout<<endl;
}

return 0;
}
