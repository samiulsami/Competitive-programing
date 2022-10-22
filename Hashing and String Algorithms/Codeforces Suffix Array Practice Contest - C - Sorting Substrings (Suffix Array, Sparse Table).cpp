#include<bits/stdc++.h>
using namespace std;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=4e5+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    int Table[20][MAX_N];
    int lgval[MAX_N];
    inline void countingSort(int k){
        int i, sum, maxi = max(130, n),t;
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
        for(int i=1; i<20; i++){
            for(int j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }
    inline int lcp(int l, int r){
        l=invSA[l];
        r=invSA[r];
        if(l>r)swap(l,r);
        l++;
        int lg=lgval[r-l+1];
        return min(Table[lg][l], Table[lg][r-(1<<lg)+1]);
    }

};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    s+=char(30);
    {
        using namespace SuffixArray;
        init(s);
        int x;
        cin>>x;
        vector<pair<int,int> >arr(x);
        for(int i=0,l,r; i<x; i++){
            cin>>l>>r;
            arr[i]={l-1,r-1};
        }

        sort(arr.begin(),arr.end(), [&](auto a, auto b)->bool{
            if(a.first==b.first)return a.second<b.second;
            int L = lcp(a.first,b.first);
            int lena=a.second-a.first+1,lenb=b.second-b.first+1;
            if(L>=min(lena,lenb)){
                    if(lena==lenb)return a<b;
                    return lena<lenb;
            }
            if(s[a.first+L]==s[b.first+L])return a<b;
            return s[a.first+L]<s[b.first+L];
        });
        //cout<<endl;
        for(auto xx:arr){
                cout<<xx.first+1<<" "<<xx.second+1<<endl;
               // cout<<s.substr(x.first,x.second-x.first+1)<<endl;
        }
    }
return 0;
}
