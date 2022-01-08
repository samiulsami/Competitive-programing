#include<bits/stdc++.h>
using namespace std;

/*
    light oj problem: 1080
    verdict: AC
*/

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
    //freopen("input.txt","r",stdin);
    int t,q,x,y,l,r;
    char s[100005],c;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        scanf("%s",&s);
        n=strlen(s);
        for(int i=0; i<=n; i++)BIT[i]=0;
        printf("Case %d:\n",cas);
        scanf("%d",&q);
        while(q--){
            scanf(" %c",&c);
            if(c=='I'){
                scanf("%d%d",&l,&r);
                range_update(l,r,1);
            }
            else{
                scanf("%d",&l);
                x=query(l)%2;
                y=s[l-1]-'0';
                printf("%d\n",y^x);
            }
        }
    }

return 0;
}
