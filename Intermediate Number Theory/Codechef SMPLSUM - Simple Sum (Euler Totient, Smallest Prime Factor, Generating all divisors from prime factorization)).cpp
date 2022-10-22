#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;

const int N = 1e7+5;
int phi[N];
int spf[N];
int divisors[500];
int dCnt=0;

int main(){
	for(int i=1; i<N; i++){
		phi[i]=i;
		spf[i]=0;
	}
	spf[1]=1;
	for(int i=2; i<N; i++){
		if(spf[i]==0){
			for(int j=i; j<N; j+=i){
				if(spf[j]==0)spf[j]=i;
				phi[j] -= phi[j]/i;
			}
		}
	}
	
	int t,n,p,cnt,x,curSize,prevCount;
	long long ans;
	scanf("%d",&t);
	
	while(t--){
		scanf("%d",&n);
		ans=0;
		dCnt=0;
		
		while(n>1){
			p = spf[n];
			cnt = 0;
			x=1;
			while(n%p==0){
				cnt++;
				n/=p;
			}
			
			prevCount = dCnt;
			for(int j=0; j<cnt; j++){
				curSize = dCnt;
				for(int k=0; k<prevCount; k++){
					divisors[dCnt] = divisors[curSize - prevCount + k]*p;
					dCnt++;
				}
			}
			divisors[dCnt++]=p;
			for(int i=1; i<cnt; i++){
				divisors[dCnt] = divisors[dCnt-1]*p;
				dCnt++;
			}
		}
		
		divisors[dCnt++]=1;
		for(int i=0; i<dCnt; i++)ans += 1LL*divisors[i]*phi[divisors[i]];
		
		printf("%lld\n",ans);
	}
    
return 0;
}