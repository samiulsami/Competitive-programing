#include<bits/stdc++.h>
using namespace std;

/*
    light oj problem: 1080
    verdict: AC
*/

vector<int>BIT;
int n;

void update(int ind, int val){
    while(ind<=n){
        BIT[ind]+=val;
        ind+=(ind&-ind);
    }
}

void range_update(int l, int r, int val){
    update(l,val);
    update(r+1,-val);
}

int query(int ind){
    int ret=0;
    while(ind>0){
        ret+=BIT[ind];
        ind-=(ind&-ind);
    }
    return ret;
}


int main(){
    int t;
    int q;
    char c;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        scanf("%d",&n);
        BIT.resize(n+1);
        getchar();
        int arr[n+1];
        char c;
        n=0;
        while(c=getchar()){
            if(c=='\n')break;
            update(++n,int(c-'0'));
            arr[n-1]=c-'0';
        }
        for(int i=0; i<n; i++)cout<<arr[i]<<" ";
        cout<<endl;
    }

return 0;
}
