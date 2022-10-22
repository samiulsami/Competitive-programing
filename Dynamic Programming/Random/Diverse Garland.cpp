#include<bits/stdc++.h>
using namespace std;

string s;
int len;
int dp[200005][4];
int dir[200005][4];

int solve(int i=0, int col=3){
    if(i==len)return 0;
    int &ret = dp[i][col];
    if(ret!=-1)return ret;
    int a,b,c;
    a=b=c=INT_MAX;
    if(col!=0)a = solve(i+1, 0)+(s[i]!='R');
    if(col!=1)b = solve(i+1, 1)+(s[i]!='G');
    if(col!=2)c = solve(i+1, 2)+(s[i]!='B');
    ret = min(a,min(b,c));
    if(a==ret)dir[i][col]=0;
    else if(b==ret)dir[i][col]=1;
    else dir[i][col]=2;
    return ret;
}

int main(){
    memset(dp,-1,sizeof(dp));
    memset(dir,-1,sizeof(dir));
    cin>>len>>s;
    cout<<solve()<<endl;
    int i=0,j=3;
    while(dir[i][j]!=-1 && i<len){
        int &direct = dir[i][j];
        if(direct==0)cout<<'R';
        else if(direct==1)cout<<'G';
        else cout<<'B';
        j=direct;
        i++;
    }
return 0;
}
