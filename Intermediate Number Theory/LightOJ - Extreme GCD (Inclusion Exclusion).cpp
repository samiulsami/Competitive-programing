#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll f[10005];

ll ncr4(ll a){
	return (a*(a-1LL)*(a-2LL)*(a-3LL))/24LL;
}

int main(){

    int t;
    scanf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        int n;
        scanf("%d",&n);
        memset(f,0,sizeof(f));
		
		for(int i=0,x; i<n; i++){
			scanf("%d",&x);
			for(int j=1; j*j<=x; j++){
				if(x%j==0){
					f[j]++;
					if(j*j!=x)f[x/j]++;
				}
			}
		}
		
		for(int i=10000; i>=1; i--){
			f[i] = ncr4(f[i]);
			for(int j=i+i; j<=10000; j+=i)
				f[i] -= f[j];
		}
		

        printf("Case %d: %lld\n",cas,f[1]);
    }

    return 0;
}