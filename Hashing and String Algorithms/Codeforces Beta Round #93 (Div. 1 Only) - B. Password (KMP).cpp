#include<bits/stdc++.h>
using namespace std;
/*
    Problem:  Codeforces Beta Round #93 (Div. 1 Only) - B. Password
    Verdict: AC
*/

/// aaaaaaaslkdfslkdjflkjaaaasdlkfjsdklfjklsdjfaaaaaaaa
int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin>>s;
    int n=(int)s.length();

    vector<int>pi(n+1);
    for(int i=1,j; i<n; i++){
        j=pi[i-1];
        while(j>0 && s[i]!=s[j])
            j=pi[j-1];

        if(s[i]==s[j])pi[i]=j+1;
        else pi[i]=0;
    }

    int x=0;
    vector<bool>valid(n+1);
    x=pi[n-1];
    while(x>0){
        valid[x]=1;
        x=pi[x-1];
    }

    int ans=0;
    for(int i=1; i<n-1; i++){
        if(valid[pi[i]])ans=max(ans,pi[i]);
    }

    if(ans>0){
        cout<<s.substr(0,ans)<<endl;
    }
    else cout<<"Just a legend\n";


return 0;
}
