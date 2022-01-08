#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=2e5+5;
    int SA[MAX_N],LCP[MAX_N]={0},invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    inline void countingSort(int k){
        int i, sum, maxi = max(60, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const vector<int> &s){
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

int L[200005];
int R[200005];
stack<int>st;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<int>arr(n+1);
    for(int i=0; i<n; i++){
            cin>>arr[i];
            arr[i]+=48;
    }
    arr[n]='$';
    n++;
    {
        using namespace SuffixArray;
        init(arr);
        ll maxprod=0,len,ind;

        for(int i=0; i<n; i++){
            while(!st.empty() && LCP[st.top()]>=LCP[i])st.pop();
            if(st.empty())L[i]=i+1;
            else L[i]=i-st.top();
            st.push(i);
        }
        while(!st.empty())st.pop();

        for(int i=n-1; i>=0; i--){
            while(!st.empty() && LCP[st.top()]>=LCP[i])st.pop();
            if(st.empty())R[i]=n-i;
            else R[i]=st.top()-i;
            st.push(i);
        }

        for(int i=0; i<n; i++){
            ll clen = (R[i]+L[i]);
            ll lcp = LCP[i];
            if(clen*lcp > maxprod){
                maxprod=clen*lcp;
                ind=SA[i];
                len=lcp;
            }
        }

        if(maxprod<n-1){
            cout<<n-1<<endl<<n-1<<endl;
            for(int i=0; i<n-1; i++)cout<<arr[i]-48<<" ";
            cout<<endl;
            return 0;
        }
        cout<<maxprod<<endl<<len<<endl;
        for(int i=0; i<len; i++)cout<<arr[i+ind]-48<<" ";
        cout<<endl;
    }
return 0;
}
