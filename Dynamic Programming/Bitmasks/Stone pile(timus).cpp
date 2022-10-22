#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[22],n;
    while(cin>>n){
        for(int i=0; i<n; i++)cin>>arr[i];
        int mask=1<<n;
        int ans=INT_MAX;
        while(mask){
            int cur=0;
            for(int i=0; i<n; i++){
                if((bool)(mask&(1<<i)))cur+=arr[i];
                else cur-=arr[i];
            }
            ans=min(ans,abs(cur));
            mask--;
        }
        cout<<ans<<endl;
    }
return 0;
}
