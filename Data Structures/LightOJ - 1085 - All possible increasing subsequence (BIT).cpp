#include<bits/stdc++.h>
using namespace std;

/*
    lightoj problem 1085;
    verdict: AC
*/

#define sf(x) scanf("%d",&x)
#define xx first
#define yy second
const int MOD=1000000007;
int n;
int BIT[100005];

void update(int ind, int val){
    while(ind<=n){
        BIT[ind]+=val;
        BIT[ind]%=MOD;
        ind+=(ind&-ind);
    }
}

int query(int ind){
    int ret=0;
    while(ind>0){
        ret+=BIT[ind];
        ret%=MOD;
        ind-=(ind&-ind);
    }
    return ret%MOD;
}

bool cmp(pair<int,int> &a, pair<int,int> &b){
    if(a.xx==b.xx)return a.yy>b.yy;
    else return a.xx<b.xx;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    pair<int,int>arr[100005];
    int t;
    sf(t);
    for(int cas=1; cas<=t; cas++){
        sf(n);
        for(int i=0; i<n; i++){
            sf(arr[i].xx);
            arr[i].yy=i;
        }
        memset(BIT,0,sizeof(int)*(n+1));
        sort(arr,arr+n,cmp);
        printf("Case %d: ",cas);
        for(int i=0; i<n; i++)
           update(arr[i].yy+1,(query(arr[i].yy)+1)%MOD);

        printf("%d\n",query(n)%MOD);
    }
return 0;
}
