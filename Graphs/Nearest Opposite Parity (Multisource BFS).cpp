#include<bits/stdc++.h>
using namespace std;

/*
    1272E - Nearest Opposite Parity
*/

int main(){
    int n;
    int arr[200005];
    cin>>n;
    for(int i=0; i<n; i++)cin>>arr[i];

    vector<int>graph[n];
    int lvl[n];
    for(int i=0; i<n; i++)lvl[i]=(int)1e8;
    queue<int>q;
    bool vis[n]={0};

    for(int i=0; i<n; i++){
        int l=i-arr[i];
        int r=i+arr[i];
        if(l>=0){
            if(arr[i]%2!=arr[l]%2)lvl[i]=1,q.push(i);
            else graph[l].push_back(i);
        }
        if(r<n){
            if(arr[i]%2!=arr[r]%2)lvl[i]=1,q.push(i);
            else graph[r].push_back(i);
        }
    }

    while(!q.empty()){
        int top=q.front();
        q.pop();
        vis[top]=1;
        for(auto x : graph[top]){
            if(vis[x])continue;
            lvl[x]=min(lvl[x],lvl[top]+1);
            vis[x]=1;
            q.push(x);
        }
    }
    for(int i=0; i<n; i++)cout<<(lvl[i]==(int)1e8?-1:lvl[i])<<" ";

return 0;
}

