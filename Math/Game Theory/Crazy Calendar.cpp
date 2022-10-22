#include <bits/stdc++.h>

int main(){
int T,cases=0,length,tmp;
scanf("%d",&T);
while(T--){
    int r,c,xorsum=0;
    scanf("%d%d",&r,&c);
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            scanf("%d",&tmp);
            length = (r-i-1)+(c-j-1);
            if(length%2==0 ||(i==r-1 && j==c-1))continue;
            xorsum^=tmp;
        }
    }
    if(xorsum>0)printf("Case %d: win\n",++cases);
    else printf("Case %d: lose\n",++cases);
}
return 0;
}
