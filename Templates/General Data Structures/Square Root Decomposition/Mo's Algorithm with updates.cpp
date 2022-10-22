#include<bits/stdc++.h>
/// SPOJ - HRSIAM - Angry Siam
using namespace std;

typedef long long ll;
const int N = 1e5+5;
const int Div = 2150; ///n^(2/3)
ll arr[N],Angry[N]={0};

struct query{
    int i,l,r,t;
    query(){}
    query(int i, int l, int r, int t):i(i),l(l),r(r),t(t){}
    bool operator<(const query &q)const{
        int thisL=l/Div,thisR=r/Div, otherL=q.l/Div,otherR=q.r/Div;
        if(thisL^otherL)return thisL<otherL;
        if(thisR^otherR)return thisR<otherR;
        return t<q.t;
    }
}queries[N];

struct update{
    int i,prev,nxt;
    update(){}
    update(int i, int prev, int nxt):i(i),prev(prev),nxt(nxt){}
}updates[N];

int vis[N]={0};
ll curAngry=0;
ll ans[N];
int L=0,R=-1;

inline void Add(int x){
    curAngry+=Angry[++vis[arr[x]]]*arr[x];
}

inline void Remove(int x){
    curAngry-=Angry[vis[arr[x]]--]*arr[x];
}

inline void Apply(int x, int val){
    if(x>=L && x<=R){
        Remove(x);
        arr[x]=val;
        Add(x);
    }
    else arr[x]=val;
}

inline void Solve(int Case){
    int n,q;
    scanf("%d",&n);
    for(int i=0; i<n; i++)scanf("%lld",&arr[i]);
    for(int i=0; i<n; i++)scanf("%lld",&Angry[i+1]);

    scanf("%d",&q);
    int queryCnt=0,updateCnt=0;
    for(int i=0,t,l,r; i<q; i++){
        scanf("%d%d%d",&t,&l,&r);
        if(t==1){///query
            l--,r--;
            queries[queryCnt] = query(queryCnt,l,r,updateCnt);
            queryCnt++;
        }
        else{///update
            l--;
            updates[updateCnt++] = update(l,arr[l],r);
            arr[l]=r;
        }
    }

    sort(queries,queries+queryCnt);
    for(int i=0; i<queryCnt; i++){
        while(updateCnt<queries[i].t){
            Apply(updates[updateCnt].i, updates[updateCnt].nxt);
            updateCnt++;
        }
        while(updateCnt>queries[i].t){
            updateCnt--;
            Apply(updates[updateCnt].i, updates[updateCnt].prev);
        }
        while(L>queries[i].l)Add(--L);
        while(R<queries[i].r)Add(++R);
        while(L<queries[i].l)Remove(L++);
        while(R>queries[i].r)Remove(R--);
        ans[queries[i].i]=curAngry;
    }


    for(int i=0; i<queryCnt; i++)printf("%lld\n",ans[i]);

}

int main(){

    Solve(0);

return 0;
}
