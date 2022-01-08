#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5+5;
int Div;
ll K[int(1e6)+5]={0};
ll arr[N];
ll sum=0;
ll ans[N];

struct query{
    int index,l,r;
    query(){}
    query(int index, int l, int r):index(index),l(l),r(r){}
    bool operator<(const query &q)const{
        int a=l/Div,b=q.l/Div;
        if(a^b)return a<b;
        return ((a&1)?r<q.r:r>q.r);
    }
}queries[N];

inline void Add(int x){
    sum-=(K[arr[x]]*K[arr[x]]*arr[x]);
    K[arr[x]]++;
    sum+=(K[arr[x]]*K[arr[x]]*arr[x]);
}

inline void Remove(int x){
    sum-=(K[arr[x]]*K[arr[x]]*arr[x]);
    K[arr[x]]--;
    sum+=(K[arr[x]]*K[arr[x]]*arr[x]);
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    Div=sqrt(n);
    for(int i=0; i<n; i++)scanf("%I64d",&arr[i]);

    for(int i=0,l,r; i<m; i++){
        scanf("%d%d",&l,&r);
        queries[i]=query(i,l-1,r-1);
    }
    sort(queries,queries+m);

    int l=0,r=-1;
    for(int i=0; i<m; i++){
        while(l<queries[i].l)Remove(l++);
        while(r<queries[i].r)Add(++r);
        while(l>queries[i].l)Add(--l);
        while(r>queries[i].r)Remove(r--);
        ans[queries[i].index]=sum;
    }

    for(int i=0; i<m; i++)printf("%I64d\n",ans[i]);
return 0;
}
