#include<bits/stdc++.h>
using namespace std;

const int maxN=1220;
int status[(maxN>>5)+2];
int primes[maxN], pcounter=0;

bool check(int N, int pos){return (bool)(N&(1<<pos));}
int Set(int N, int pos){return N|=(1<<pos);}

void sieve(){
    int i,j,sqrtN,k;
    sqrtN = sqrt(maxN);
    for(i=3; i<=sqrtN; i+=2){
        if(check(status[i>>5],i&31)==0){
            for(j=i*i,k=(i<<1); j<=maxN; j+=k)
                status[j>>5]=Set(status[j>>5],j&31);
        }
    }
    primes[pcounter++]=2;
    for(i=3; i<=maxN; i+=2){
        if(check(status[i>>5], i&31)==0)
            primes[pcounter++]=i;
    }
}

int dp[1122][15][1122];
int n,k;

int solve(int i=0, int amount=n,int counter=0){
    if(counter==k)return amount==0;
    if(amount<0 ||primes[i]>amount)return 0;
    int &ret = dp[amount][counter][i];
    if(ret!=-1)return ret;
    return ret = solve(i+1,amount-primes[i],counter+1)+solve(i+1,amount,counter);
}

int main(){
    sieve();
    while(scanf("%d%d",&n,&k),n||k){
        memset(dp,-1,sizeof(dp));
        printf("%d\n",solve(0,n,0));
    }
return 0;
}
