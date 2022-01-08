#include<bits/stdc++.h>
using namespace std;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=1e5+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    int lgval[MAX_N];
    int Table[18][MAX_N]={0};

    inline void countingSort(int k){
        int i, sum, maxi = max(150, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const string &s){
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
        for(i=0; i<n; i++) invSA[SA[i]]=i;
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            int j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
            Table[0][invSA[i]]=k;
        }
        lgval[0]=lgval[1]=0;
        for(int i=2; i<MAX_N; i++)lgval[i]=lgval[i>>1]+1;
        for(int i=1; i<18; i++){
            for(int j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    inline int lcp(int i, int j){
        int lg = lgval[j-i+1];
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }
};

int arr[100005]={0};

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    long long k;
    cin>>s>>k;
    long long tmp=(int)s.size();
    if((tmp*(tmp+1))/2 <k){
        cout<<"No such line."<<endl;
        return 0;
    }
    s+="$";
    {
        using namespace SuffixArray;
        init(s);
       /* for(int i=0; i<n; i++){
            printf("LCP: %d, suff: ",LCP[i]);
            cout<<s.substr(SA[i])<<endl;
        }*/
        long long substrings=0;

        for(int i=0,cnt=0,low,high,mid,offset,rightmost; i<n; i++){
            cnt+=arr[i];
            offset=cnt;
            do{
                rightmost=-1;
                low=i+1,high=n-1;
                while(low<=high){
                    mid=(low+high)>>1;
                    if(lcp(i+1,mid)-offset>0){
                        rightmost=max(rightmost,mid);
                        low=mid+1;
                    }
                    else high=mid-1;
                }
                if(rightmost==-1)break;

                int L = lcp(i+1,rightmost)-offset;
                long long len=rightmost-i+1;
                arr[i+1]+=L;
                arr[rightmost+1]-=L;
                long long newval = substrings+1LL*L*len;

                if(newval>=k){
                    long long tmpk=k-substrings;
                    long long x = (tmpk+len-1)/len;
                    cout<<s.substr(SA[i],offset+x)<<endl;
                    //cout<<"L: "<<L<<", offset: "<<offset<<",len: "<<len<<", newval: "<<newval<<", x: "<<x<<endl;
                    return 0;
                }
                substrings = newval;
                offset+=L;
            }while(rightmost!=-1 && substrings<k);

            int len=n-SA[i]-1-offset;
            if(substrings+len>=k){
                cout<<s.substr(SA[i],k-substrings+offset)<<endl;
                return 0;
            }
            substrings+=len;
        }

    }
return 0;
}
