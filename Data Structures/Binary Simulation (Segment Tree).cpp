#include<bits/stdc++.h>
using namespace std;
/**
    Problem LightoJ 1080 - Binary Simulation
    Verdict: AC
*/

const int MAX = 1e5+5;
int n;
int tree[2*MAX];
char s[MAX];

void build(){
    for(int i=n-1; i>0; i--)tree[i]=tree[i<<1] + tree[i<<1|1];
}

void range_update(int l, int r,int val){
    l+=n;
    r+=n+1;
    for(;l<r; l>>=1,r>>=1){
        if(l&1)tree[l++]+=val;
        if(r&1)tree[--r]+=val;
    }
}

int point_query(int ind){
    int ret=0;
    for(ind+=n; ind>0; ind>>=1)ret+=tree[ind];
    return ret;
}

int main(){

    int T;
    int q,x,l,r;
    char c;

    scanf("%d",&T);
    for(int cas=1; cas<=T; cas++){

        scanf("%s",&s);
        n=strlen(s);
        for(int i=0; i<n; i++)tree[i]=tree[i+n]=0;

        scanf("%d",&q);
        printf("Case %d:\n",cas);
        while(q--){
            scanf(" %c",&c);
            if(c=='I'){
                scanf("%d%d",&l,&r);
                l--,r--;
                range_update(l,r,1);
            }
            else{
                scanf("%d",&x);
                x--;
                printf("%d\n",(int(s[x])+point_query(x))%2);
            }
        }

    }

return 0;
}
