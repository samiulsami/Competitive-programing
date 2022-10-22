#include<bits/stdc++.h>
using namespace std;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=1e5+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
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
            if(invSA[i]==n-1){k=0; continue;}
            int j=SA[invSA[i]+1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    s+="$";
    {
        using namespace SuffixArray;
        init(s);
        long long ans=0;
        for(int i=0; i<n; i++){
            ans+=n-SA[i]-LCP[i]-1;
        }
        cout<<ans<<endl;
    }
return 0;
}
