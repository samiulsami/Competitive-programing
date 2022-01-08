#include<bits/stdc++.h>
using namespace std;

struct node{
    node *nxt[2];
    node(){nxt[0]=nxt[1]=NULL;}
};

void add(node *root, long long val){
    node *cur=root;
    for(int i=62; i>=0; i--){
        bool bit=0;
        if(bool(val&(1LL<<i)))bit=1;
        if(cur->nxt[bit]==NULL)cur->nxt[bit] = new node();
        cur = cur->nxt[bit];
    }
}

long long get(node *root, long long val){
    node *cur=root;
    long long ret=0;
    for(int i=62; i>=0; i--){
        bool bit=0;
        if(bool(val&(1LL<<i)))bit=1;
        if(cur->nxt[bit^1]!=NULL){
            cur = cur->nxt[bit^1];
            ret+=(1LL<<i);
        }
        else cur = cur->nxt[bit];
    }
    return ret;
}

long long pref[100004],suff[100004],arr[100004];
int n;

int main(){
    cin>>n;
    pref[0]=0;
    suff[n+1]=0;
    for(int i=1; i<=n; i++){
        cin>>arr[i];
        pref[i] = pref[i-1]^arr[i];
    }

    long long ans=0;
    for(int i=n; i>=1; i--){
            suff[i] = suff[i+1]^arr[i];
            ans = max({ans, pref[i], suff[i]});
    }

    node *root = new node();
    for(int i=1; i<n; i++){
        add(root,pref[i]);
        ans = max(ans, get(root, suff[i+1]));
    }

    cout<<ans<<endl;

return 0;
}
