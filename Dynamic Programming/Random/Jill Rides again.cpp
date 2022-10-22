#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int t,n;
    int arr[100005];
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n;
        for(int i=2; i<=n; i++)cin>>arr[i];
        int be=-1,en=-1,maxsum=0,cursum=0,betmp=1;
        for(int i=2; i<=n; i++){
            cursum+=arr[i];
            if(cursum<0){
                cursum=0;
                betmp=i;
            }
            if(cursum>maxsum || (cursum==maxsum && i-betmp>en-be)){
                maxsum=cursum;
                be=betmp;
                en=i;
            }
        }
        if(en==-1)cout<<"Route "<<cas<<" has no nice parts"<<endl;
        else cout<<"The nicest part of route "<<cas<<" is between stops "<<be<<" and "<<en<<endl;
    }
return 0;
}
