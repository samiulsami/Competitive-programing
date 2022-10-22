#include<bits/stdc++.h>
using namespace std;

struct node{
    int depth,value;
}arr[100];

int t,w,n;
int dp[1005][100];
int out[1005][100];

int solve(int i=0, int time=t){
    if(time<=0 || i>=n)return 0;
    int &ret = dp[time][i];
    if(ret!=-1)return ret;
    int ttaken = 3*(w*arr[i].depth);
    int ret1=0, ret2=0;
    if(time-ttaken>=0)ret1 = solve(i+1, time-ttaken)+arr[i].value;
    ret2 = solve(i+1, time);
    if(ret1>ret2){
        out[time][i]=1;//take
        return ret = ret1;
    }
    out[time][i]=2;//don't take
    return ret = ret2;
}

int main(){
    //freopen("output.txt","w",stdout);
    bool first=1;
    while(scanf("%d%d",&t,&w)!=EOF){
        if(!first)cout<<endl;
        first=0;
        cin>>n;
        memset(out,-1,sizeof(out));
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<n; i++)cin>>arr[i].depth>>arr[i].value;
        cout<<solve(0,t)<<endl;
        int i=0,time=t;
        vector<int>output;
        while(out[time][i]!=-1 && i<n && time>0){
            if(out[time][i]==1){
                output.push_back(i);
                time-=3*(w*arr[i].depth);
            }
            i++;
        }
        cout<<output.size()<<endl;
        for(i=0; i<output.size(); i++)cout<<arr[output[i]].depth<<" "<<arr[output[i]].value<<endl;
    }

return 0;
}

