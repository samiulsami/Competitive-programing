#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int n;
    int in;
    while(cin>>n,n){
        int ans=0,cur=0;
        for(int i=0; i<n; i++){
            cin>>in;
            cur+=in;
            ans=max(ans,cur);
            if(cur<0)cur=0;
        }
        if(ans)cout<<"The maximum winning streak is "<<ans<<"."<<endl;
        else cout<<"Losing streak."<<endl;
    }
return 0;
}

