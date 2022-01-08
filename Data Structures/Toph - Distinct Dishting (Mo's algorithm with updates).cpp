#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const int N = 1e5+5;
int n,q;
pii arr[N];
const int Div=2200;


struct update{
    int ind;
    pii prev,nxt; ///original, mapped
    update(){}
    update(int ind, pii prev, pii nxt):ind(ind),nxt(nxt),prev(prev){}
}updates[N];

struct query{
    int ind, l, r, t;
    query(){}
    query(int ind, int l, int r, int t):ind(ind),l(l),r(r),t(t){}
    bool operator<(const query &q)const{
        int curl=l/Div, otherl = q.l/Div, curr=r/Div,otherr=q.r/Div;
        if(curl^otherl)return curl<otherl;
        if(curr^otherr)return curr<otherr;
        return t<q.t;
    }
}queries[N];

int L=0,R=-1;
long long ans[N];
int visCnt[N+N]={0};
long long cur=0;

inline void Add(int x){
    if(++visCnt[arr[x].second]==1){
        if(arr[x].first%3==0)cur+=1LL*arr[x].first;
    }
}

inline void Remove(int x){

    if(--visCnt[arr[x].second]==0){
        if(arr[x].first%3==0)cur-=1LL*arr[x].first;
    }
}

inline void Apply(int x, pii val){
    if(L<=x && R>=x){
        Remove(x);
        arr[x]=val;
        Add(x);
    }
    else{
        arr[x] = val;
    }
}

int main(){
    scanf("%d%d",&n,&q);
    set<int>st;
    for(int i=0; i<n; i++)scanf("%d",&arr[i].first),st.insert(arr[i].first);
    map<int,int>mp;
    int mpCnt=1;
    for(int i:st){
        mp[i]=mpCnt++;
    }
    for(int i=0; i<n; i++)arr[i].second = mp[arr[i].first];

    int updateCnt=0;
    int queryCnt=0;
    for(int i=0,l,r,qt; i<q; i++){
        scanf("%d%d%d",&qt,&l,&r);
        if(qt==0){
            if(!mp.count(r))mp[r]=mpCnt++;
            updates[updateCnt++]=update(l-1,make_pair(arr[l-1].first,arr[l-1].second), make_pair(r,mp[r]));
            arr[l-1] = make_pair(r,mp[r]);
        }
        else{
            queries[queryCnt] = query(queryCnt,l-1,r-1,updateCnt);
            queryCnt++;
        }
    }


    sort(queries,queries+queryCnt);
    for(int i=0; i<queryCnt; i++){
        //for(int j=0; j<n; j++)printf("%d ",arr[j].first);
        //printf("\n ql-qr = %d %d\n L-R = %d %d\n",queries[i].l, queries[i].r,L,R);

        while(updateCnt<queries[i].t){
            Apply(updates[updateCnt].ind, updates[updateCnt].nxt);
            updateCnt++;
        }
        while(updateCnt>queries[i].t){
            updateCnt--;
            Apply(updates[updateCnt].ind, updates[updateCnt].prev);
        }
        while(L<queries[i].l)Remove(L++);
        while(L>queries[i].l)Add(--L);
        while(R<queries[i].r)Add(++R);
        while(R>queries[i].r)Remove(R--);
        ans[queries[i].ind]=cur;

    }

    for(int i=0; i<queryCnt; i++)printf("%lld\n",ans[i]);



return 0;
}
