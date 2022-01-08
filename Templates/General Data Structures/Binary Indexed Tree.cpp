#include<bits/stdc++.h>
using namespace std;

int BIT[100005];
int n;

void update(int ind, int val){
    while(ind<=n){
        BIT[ind]+=val;
        ind+=(ind&-ind);
    }
}

int query(int ind){
    int ret=0;
    while(ind>0){
        ret+=BIT[ind];
        ind-=(ind&-ind);
    }
    return ret;
}

void range_update(int l, int r, int val){
    update(l,val);
    update(r+1,-val);
}

int main(){

return 0;
}
