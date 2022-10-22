#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
int arr[N],ans[N];
int original[N];
const int Div=320;
int BlockSum[400]={0};
int cnt[N]={0};

struct query{
    int l,r,i,k,x;
    query(){}
    query(int i, int l, int r, int k):i(i),l(l),r(r),k(k){}
    bool operator<(const query &q)const{
        if(x^q.x)return x<q.x;
        return (x&1)?r<q.r:r>q.r;
    }
}queries[5002];

inline void Add(int x){
    BlockSum[arr[x]/Div]++;
    cnt[arr[x]]++;
}

inline void Remove(int x){
    BlockSum[arr[x]/Div]--;
    cnt[arr[x]]--;
}

inline int getAns(int k){
    int cur=0,ind=-1;
    for(int i=0; i<Div; i++){
        if(cur+BlockSum[i]>=k){
            ind=i;
            break;
        }
        cur+=BlockSum[i];
    }
    k-=cur;
    for(int i=ind*Div; ;i++){
        if(k-cnt[i]<=0)return i;
        k-=cnt[i];
    }
    return -1;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    map<int,int>mp;
    vector<int>tmp(n);
    for(int i=0; i<n; i++){
            scanf("%d",&arr[i]);
            tmp[i]=arr[i];
    }
    sort(tmp.begin(),tmp.end());
    tmp.erase(unique(tmp.begin(),tmp.end()), tmp.end());
    for(int i:tmp){
            original[1+(int)mp.size()]=i;
            mp[i]=1+(int)mp.size();
    }
    for(int i=0; i<n; i++)arr[i]=mp[arr[i]];

    for(int i=0,l,r,k; i<m; i++){
        scanf("%d%d%d",&l,&r,&k);
        queries[i]=query(i,l-1,r-1,k);
        queries[i].x=l/Div;
    }
    sort(queries,queries+m);

    int l=0,r=-1;
    for(int i=0; i<m; i++){
        while(r<queries[i].r)Add(++r);
        while(l>queries[i].l)Add(--l);
        while(r>queries[i].r)Remove(r--);
        while(l<queries[i].l)Remove(l++);

        ans[queries[i].i] = original[getAns(queries[i].k)];
    }

    for(int i=0; i<m; i++)printf("%d\n",ans[i]);
return 0;
}
