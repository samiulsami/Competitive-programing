#include<iostream>
#include<string>
using namespace std;

int main(){
string s;
int T,cases=0;
cin>>T;
while(T--){
    cin>>s;
    int len=s.length(),sum=0,multiples=0;
    bool no_moves=1;
    for(int i=0; i<len; i++){
        sum+=s[i]-48;
        if((s[i]-48)%3==0)multiples++;
    }
    for(int i=0; i<len; i++){
        if((sum-s[i]-48)%3==0){
            no_moves=0;
            if((s[i]-48)%3==0)multiples--;
            break;
        }
    }
    cout<<"Case "<<++cases<<": ";
    if(no_moves)cout<<"T\n";
    else if(multiples%2)cout<<"T\n";
    else cout<<"S\n";
}


return 0;
}
