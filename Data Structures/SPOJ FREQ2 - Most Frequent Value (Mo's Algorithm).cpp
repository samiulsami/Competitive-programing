#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
const int Div=1000;

struct query{
    int ind,l,r,x;
    query(){}
    query(int ind, int l, int r):ind(ind),l(l),r(r){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return ((x&1)?r<q.r:r>q.r);
    }
}queries[N];

pair<int,int>arr[N]; ///original, mapped
int counter[N]={0};
int xorsum=0;
map<int,int>mp;
int mpCnt=0;
int ans[N];

inline void Add(int x){
    int &cur = counter[arr[x].second];
    cur++;
    if(cur&1){
        if(cur>1)xorsum^=arr[x].first;
    }
    else{
        xorsum^=arr[x].first;
    }
}

inline void Remove(int x){
    int &cur = counter[arr[x].second];
    cur--;
    if(cur&1){
        xorsum^=arr[x].first;
    }
    else{
        if(cur>0)xorsum^=arr[x].first;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n,m;
    cin>>n;
   // Div=sqrt(n);

    for(int i=0; i<n; i++){
        cin>>arr[i].first;
        if(!mp.count(arr[i].first)){
            mp[arr[i].first]=mpCnt++;
        }
        arr[i].second=mp[arr[i].first];
    }

    cin>>m;
    for(int i=0,l,r; i<m; i++){
        cin>>l>>r;
        queries[i]=query(i,l-1,r-1);
        queries[i].x=l/Div;
    }

    sort(queries,queries+m);
    int l=0,r=-1;

    for(int i=0; i<m; i++){
        while(l<queries[i].l)Remove(l++);
        while(l>queries[i].l)Add(--l);
        while(r<queries[i].r)Add(++r);
        while(r>queries[i].r)Remove(r--);
        ans[queries[i].ind]=xorsum;
    }

    for(int i=0; i<m; i++)cout<<ans[i]<<"\n";

return 0;
}
