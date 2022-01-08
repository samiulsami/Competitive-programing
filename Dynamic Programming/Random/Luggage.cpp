#include<bits/stdc++.h>
using namespace std;

int n;
bool dfs(int i, int sum, int *arr){
    if(i==n)return sum==0;
    return dfs(i+1,sum+arr[i],arr)|dfs(i+1,sum-arr[i],arr);
}

int main(){
    int t;
    string s;
    cin>>t;
    cin.ignore();
    while(t--){
        getline(cin,s);
        int arr[25]={0};
        n=0;
        for(int i=0,len=s.length(); i<len; i++){
            if(s[i]==' ')i++,arr[n]/=10,n++;
            arr[n]+=s[i]-48;
            arr[n]*=10;
        }
        arr[n++]/=10;
        if(dfs(0,0,arr))cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
return 0;
}
