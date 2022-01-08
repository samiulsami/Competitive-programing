#include<bits/stdc++.h>
using namespace std;

struct BIT{
    vector<int>tree;
    int n;
    void BIT_init(int n){this->n=n,tree.resize(n+1);}
    void update(int idx, int val){
        while(idx<=n){
            tree[idx]+=val;
            idx+=(idx&-idx);
        }
    }
    int query(int idx){
        int ret=0;
        while(idx>0){
            ret+=tree[idx];
            idx-=(idx&-idx);
        }
        return ret;
    }
}find_char[26];

int main(){
    string s;
    int q,n,x,l,r;
    char c;
    cin>>s;
    n=s.length();
    for(int i=0; i<26; i++)find_char[i].BIT_init(n);
    for(int i=0; i<n; i++)find_char[int(s[i]-'a')].update(i+1,1);
    cin>>q;
    while(q--){
        cin>>x;
        if(x==1){
            cin>>l>>c;
            find_char[int(s[l-1]-'a')].update(l,-1);
            find_char[int(c-'a')].update(l,1);
            s[l-1]=c;
        }
        else {
            cin>>l>>r;
            int cnt=0;
            for(int i=0; i<26; i++)
                cnt+=(bool)(find_char[i].query(r)-find_char[i].query(l-1));
            cout<<cnt<<endl;
        }
    }
return 0;
}
