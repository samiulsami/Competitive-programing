#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
typedef long long ll;
char s[102];
ll dp[1002][102][2];
int pi[102];
int n,m;

ll f(int i,int j, bool done){
    if(i==n)return done||j==m;
    ll &ret = dp[i][j][done];
    if(~ret)return ret;
    ret=0;
    if(j==m)done=1;

    for(char c='A'; c<='Z'; c++){
        if(done)ret+=f(i+1,j,1);
        else{
            int newj=j;
            while(newj>0 && c!=s[newj])newj=pi[newj-1];
            if(c==s[newj])newj++;
            ret+=f(i+1,newj,0);
        }
        if(ret>=2LL*MOD*MOD)ret%=MOD;
    }
    return ret%MOD;
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    scanf(" %s",&s);
    m=strlen(s);

    pi[0]=0;
    for(int i=1,j; i<m; i++){
        j=pi[i-1];
        while(j>0 && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])pi[i]=j+1;
    }
    printf("%lld\n",f(0,0,0)%MOD);

return 0;
}
