#include<bits/stdc++.h>
using namespace std;
int g[10005];

void grundy(){
    set<int>se;
    for(int i=3,a,b,x,y,mex; i<=10000; i++){
        a=1;
        b=i-1;
        mex=0;
        se.clear();
        while(a<b){
           se.insert(g[a]^g[b]);
           a++;
           b--;
        }
        while(se.find(mex)!=se.end())mex++;
        g[i]=mex;
    }
}

int main(){
    memset(g, 0, sizeof(g));
    grundy();
    int t,n,pile,xorsum;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        scanf("%d",&n);
        xorsum=0;
        while(n--){
            scanf("%d",&pile);
            xorsum^=g[pile];
        }
        printf("Case %d: ",cas);
        if(xorsum)printf("Alice\n");
        else printf("Bob\n");
    }
return 0;
}
