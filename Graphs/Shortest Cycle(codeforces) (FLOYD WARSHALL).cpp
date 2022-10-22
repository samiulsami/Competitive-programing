#include<bits/stdc++.h>
using namespace std;

int main(){
    long long arr[100005],n;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>arr[i];
        if(!arr[i])i--,n--;
    }
    if(n>(3*64))cout<<"3",exit(0);
    long long ans=-1;
    int dist[n+1][n+1],distOLD[n+1][n+1];
    memset(dist,-1,sizeof(dist));
    memset(distOLD,-1,sizeof(distOLD));
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]&arr[j])dist[i][j]=dist[j][i]=distOLD[i][j]=distOLD[j][i]=1;
        }
    }
    for(int k=0; k<n; k++){
        for(int i=0; i<k; i++){
            for(int j=i+1; j<k; j++){
                if(distOLD[i][k]==-1 || distOLD[j][k]==-1 || dist[i][j]==-1)continue;
                if(ans==-1 || ans>distOLD[i][k]+distOLD[j][k]+dist[i][j])ans=distOLD[i][k]+distOLD[j][k]+dist[i][j];
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(dist[i][k]==-1 || dist[k][j]==-1)continue;
                if(dist[i][j]==-1 || dist[i][j]>dist[i][k]+dist[k][j])dist[i][j]=dist[i][k]+dist[k][j];
            }
        }
    }
    cout<<ans;
return 0;
}
