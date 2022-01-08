#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int main(){
    //freopen("output.txt","w",stdout);
    LL a,b,c;
    LL t;
    cin>>t;
    while(t--){
        LL arr[22][22][22]={0};
        cin>>a>>b>>c;
        for(int i=1; i<=a; i++)
            for(int j=1; j<=b; j++)
                for(int k=1; k<=c; k++){
                        LL x;
                        cin>>x;
                        x+=arr[i-1][j][k];
                        x+=arr[i][j-1][k];
                        x+=arr[i][j][k-1];
                        x+=arr[i-1][j-1][k-1];
                        x-=arr[i-1][j-1][k];
                        x-=arr[i-1][j][k-1];
                        x-=arr[i][j-1][k-1];
                        arr[i][j][k]=x;
                }
        LL ans=INT_MIN;
        for(int i=1; i<=a; i++)for(int j=1; j<=b; j++)for(int k=1; k<=c; k++)
            for(int x=i; x<=a; x++)for(int y=j; y<=b; y++)for(int z=k; z<=c; z++){
                LL tmp=arr[x][y][z];
                tmp-=(arr[i-1][y][z]+arr[x][j-1][z]+arr[x][y][k-1]+arr[i-1][j-1][k-1]);
                tmp+=(arr[i-1][j-1][z]+arr[i-1][y][k-1]+arr[x][j-1][k-1]);
                ans=max(ans,tmp);
            }
        cout<<ans<<endl;
        if(t)cout<<endl;
    }
return 0;
}

