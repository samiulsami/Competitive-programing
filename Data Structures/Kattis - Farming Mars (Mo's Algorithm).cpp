#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int K;
int arr[N];
int counter[N]={0};
int counterSum[N]={0};
int occurences=0;
bool ans[N];
int n;
map<double,int>mp;
int mpCnt=1;

struct query{
    int index,l,r;
    query(){}
    query(int index, int l, int r):index(index),l(l),r(r){}
    bool operator<(const query &q)const{
        int a=l/K,b=q.l/K;
        if(a!=b)return a<b;
        return ((a&1)?r<q.r:r>q.r);
    }
}queries[N];


void Add(int x){
    counterSum[counter[arr[x]]]--;
    counter[arr[x]]++;
    counterSum[counter[arr[x]]]++;
    if(counterSum[occurences+1]>0)occurences++;
}

void Remove(int x){
    counterSum[counter[arr[x]]]--;
    counter[arr[x]]--;
    counterSum[counter[arr[x]]]++;
    if(counterSum[occurences]==0)occurences--;
}


int main(){
    int m;
    scanf("%d%d",&n,&m);
    K=sqrt(n);
    counterSum[0]=n;
    for(int i=0; i<n; i++){
        double tmp;
        scanf("%lf",&tmp);
        if(!mp.count(tmp)){
            mp[tmp]=mpCnt++;
        }
        arr[i]=mp[tmp];
    }
    for(int i=0,l,r; i<m; i++){
        scanf("%d%d",&l,&r);
        l--;
        r--;
        queries[i]=query(i,l,r);
    }


    int l=0,r=-1;
    sort(queries,queries+m);
    for(int i=0; i<m; i++){
        while(l<queries[i].l)Remove(l++);
        while(r<queries[i].r)Add(++r);
        while(l>queries[i].l)Add(--l);
        while(r>queries[i].r)Remove(r--);

        //int occurence = counter[Query(1,1,mpCnt,1,mpCnt)];
        //printf("%d\n",occurences);
        bool valid=0;
        if(occurences>(queries[i].r-queries[i].l+1)/2)valid=1;
        else valid=0;
        ans[queries[i].index]=valid;
    }

    for(int i=0; i<m; i++){
        if(ans[i])printf("usable\n");
        else printf("unusable\n");
    }

return 0;
}
