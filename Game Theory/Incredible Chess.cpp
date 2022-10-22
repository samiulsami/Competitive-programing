#include<iostream>

using namespace std;

int main(){
int T,cases=0,n,b[101],w[101];
cin>>T;
while(T--){
    cin>>n;
    for(int i=0; i<n; i++)cin>>w[i];
    for(int i=0; i<n; i++)cin>>b[i];
    int x=b[0]-w[0]-1;
    for(int i=1; i<n; i++){
        x^=(b[i]-w[i]-1);
    }
    cout<<"Case "<<++cases<<": ";
    if(x>0)cout<<"white wins"<<endl;
    else cout<<"black wins"<<endl;
}
return 0;
}
