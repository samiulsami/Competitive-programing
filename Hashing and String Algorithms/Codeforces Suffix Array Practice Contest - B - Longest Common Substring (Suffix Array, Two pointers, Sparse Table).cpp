#include<bits/stdc++.h>
using namespace std;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=2e5+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    int Table[20][MAX_N];
    int lgval[MAX_N];
    int LOG,lft;

    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }

    void init(const string &s, int x){
        lft=x-1;
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

    inline int lcp(int i, int j){
        int lg = lgval[j-i+1];
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }

    int cur=0,a=0,b=0;

    inline void Add(int x){
        x=SA[x];
        if(x<=lft)a++;
        else b++;
        if(a&&b)cur=2;
        else if(a||b)cur=1;
        else cur=0;
    }

    inline void Remove(int x){
        x=SA[x];
        if(x<=lft)a--;
        else b--;
        if(a&&b)cur=2;
        else if(a||b)cur=1;
        else cur=0;
    }


};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s,t;
    cin>>s>>t;
    s+="$";
    int x = s.length();
    s+=t;
    s+="#";
    {
        using namespace SuffixArray;
        init(s,x);

        int l=0,curmx=-1,curind=-1;
        int curlcp;
        for(int i=0; i<n; i++){
            Add(i);
            while(l<i && cur==2){
                curlcp=lcp(l+1,i);
                if(curlcp>curmx){
                    curmx=curlcp;
                    curind=SA[l];
                }
                Remove(l++);
            }
        }

        if(curmx!=-1){
            cout<<s.substr(curind,curmx);
        }
        cout<<endl;

    }
return 0;
}
