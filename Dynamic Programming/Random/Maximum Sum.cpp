#include<bits/stdc++.h>
using namespace std;


int main(){
    //freopen("output.txt","w",stdout);
    int arr[105][105];
    int n,ans=INT_MIN;
    cin>>n;
    for(int i=0; i<n; i++)for(int j=0; j<n; j++)scanf("%d",&arr[i][j]);
    for(int l=0; l<n; l++){
        int tmp[n]={0};
        for(int r=l; r<n; r++){
            bool allNegative=1;
            for(int i=0; i<n; i++){
                    tmp[i]+=arr[i][r];
                    if(tmp[i]>=0)allNegative=0;
            }
            if(allNegative){
                    ans=max(ans,*max_element(tmp,tmp+n));
                    continue;
            }
            int sum=0;
            for(int i=0; i<n; i++){
                sum+=tmp[i];
                if(sum<0)sum=0;
                ans=max(ans,sum);
            }
        }
    }
    cout<<ans<<endl;
return 0;
}

