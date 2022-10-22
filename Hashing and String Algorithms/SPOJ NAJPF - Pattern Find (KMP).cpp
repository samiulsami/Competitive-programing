#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s,p;
    int T;
    cin>>T;

    while(T--){
        cin>>s>>p;

        int n = p.length();
        vector<int>pi(n+1);

        for(int i=1,j; i<n; i++){
            j=pi[i-1];
            while(j>0 && p[i]!=p[j]){
                j=pi[j-1];
            }

            if(s[i]==s[j])pi[i]=j+1;
            else pi[i]=0;
        }

        vector<int>ans;
        for(int i=0,j=0,len=s.length(); i<len; i++){
            if(s[i]==p[j])j++;
            else {
                while(j>0 && s[i]!=p[j]){
                    j=pi[j-1];
                }
                if(s[i]==p[j])j++;
            }
            if(j==n){
                ans.push_back(i+1-n+1);
                j=pi[j-1];
            }
        }

        if((int)ans.size()>0){
            cout<<(int)ans.size()<<endl;
            for(int i:ans)cout<<i<<" ";
            cout<<endl;
        }
        else cout<<"Not Found\n";
    }

return 0;
}
