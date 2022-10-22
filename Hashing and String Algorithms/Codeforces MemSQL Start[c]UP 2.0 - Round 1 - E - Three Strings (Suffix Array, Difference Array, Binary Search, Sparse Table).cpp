#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=3e5+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    int Table[20][MAX_N];
    int cSum[3][MAX_N]={0};
    int lgval[MAX_N];

    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const string &s, int xx, int yy){
        int i,k,r;
        n=(int)s.size();
        for (i = 0; i < n; i++)RA[i] = s[i];
        for (i = 0; i < n; i++)SA[i] = i;
        for (k = 1; k < n; k <<= 1){
            countingSort(k);
            countingSort(0);
            invSA[SA[0]] = r = 0;
            for (i = 1; i < n; i++)invSA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
            for (i = 0; i < n; i++)RA[i] = invSA[i];
            if (RA[SA[n-1]] == n-1) break;
        }
        for(i=0; i<n; i++) {
                invSA[SA[i]]=i;
                int tmp;
                if(SA[i]<xx)tmp=0;
                else if(SA[i]<yy)tmp=1;
                else tmp=2;
                cSum[tmp][i]++;
                if(i){
                    for(int j=0; j<3; j++)
                        cSum[j][i]+=cSum[j][i-1];
                }
        }
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            int j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
            Table[0][invSA[i]]=k;
        }
        lgval[0]=lgval[1]=0;
        for(int i=2; i<MAX_N; i++)lgval[i]=lgval[i>>1]+1;
        for(int i=1; i<20; i++){
            for(int j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    inline int lcp(int l, int r){
        int lg = lgval[r-l+1];
        return min(Table[lg][l],Table[lg][r-(1<<lg)+1]);
    }

    int total(int l, int r){
        int ret=1;
        for(int i=0,tmp; i<3; i++){
            tmp=cSum[i][r];
            if(l)tmp-=cSum[i][l-1];
            ret = (1LL*ret*tmp)%MOD;
        }
        return ret%MOD;
    }

};

int arr[300005]={0};
int arr2[300005]={0};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s,a,b;
    cin>>s>>a>>b;
    int minn = min({s.length(),a.length(),b.length()});
    char c = '$';
    s+=c++;
    int xx=s.length();
    s+=a+c++;
    int yy=s.length();
    s+=b+c++;
    {
        using namespace SuffixArray;
        init(s,xx,yy);
        int offset,low,mid,high,rightmost;

        for(int i=0,cnt=0; i<n; i++){
            cnt+=arr2[i];
            offset=cnt;
            do{
                low=i+1,high=n-1;
                rightmost=-1;
                while(low<=high){
                    mid = (low+high)>>1;
                    if(lcp(i+1,mid)-offset>0){
                        low=mid+1;
                        rightmost=max(rightmost,mid);
                    }
                    else high=mid-1;
                }
                if(rightmost==-1)break;
                int val = total(i,rightmost);
                if(val<=0)break;
                int L = lcp(i+1,rightmost)-offset;
                arr2[i+1]+=L;
                arr2[rightmost+1]-=L;
                arr[offset] = (arr[offset]+val)%MOD;
                arr[offset+L] = (arr[offset+L]-val)%MOD;
                offset+=L;
            }while(rightmost!=-1);
        }

        int cnt=0;
        for(int i=0; i<minn; i++){
            cnt+=arr[i];
            cnt%=MOD;
            cout<<(cnt+MOD)%MOD<<" ";
        }
        cout<<endl;

    }
return 0;
}
