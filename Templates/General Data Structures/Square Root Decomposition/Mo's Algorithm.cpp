#include<bits/stdc++.h>
using namespace std;

///Problem: SPOJ - DQUERY
///Mo's Algorithm ~O(q*sqrt(n))

const int N=3e4+5;
const int M=2e5+5;
int K;

struct query{
    int index,l,r;
    query(){}
    query(int index, int l, int r):index(index),l(l),r(r){}
    bool operator<(const query &q)const{
        int a=l/K;
        int b=q.l/K;
        if(a^b)return a<b;
        return ((a&1)?r<q.r:r>q.r);
    }
}queries[M];

int arr[N];
int ans[M];
int inRange[int(1e6)+5]={0};
int distinct=0;

inline void Add(int x){
    if(++inRange[arr[x]]==1)distinct++;
}

inline void Remove(int x){
    if(--inRange[arr[x]]==0)distinct--;
}

int main(){
    int n,l,r,q;
    scanf("%d",&n);
    K=sqrt(n);

    for(int i=0; i<n; i++)scanf("%d",&arr[i]);

    scanf("%d",&q);
    for(int i=0; i<q; i++){
        scanf("%d%d",&queries[i].l,&queries[i].r);
        queries[i].index=i;
        queries[i].l--;
        queries[i].r--;
    }

    distinct=0;
    l=0;
    r=-1;
    sort(queries,queries+q);
    for(int i=0; i<q; i++){
        while(l>queries[i].l)Add(--l);
        while(r<queries[i].r)Add(++r);
        while(l<queries[i].l)Remove(l++);
        while(r>queries[i].r)Remove(r--);
        ans[queries[i].index]=distinct;
    }

    for(int i=0; i<q; i++)printf("%d\n",ans[i]);


return 0;
}
