#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int K;
int arr[N];
int counter[N]={0};
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

int Merge(int L, int R){
    if(counter[L]>counter[R])return L;
    return R;
}

int Tree[4*N]={0};
void update(int node, int l, int r, int pos){
    if(l>r || l>pos || r<pos)return;
    if(l==pos && r==pos)Tree[node]=pos;
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(node*2, l, mid, pos);
        else update(node*2+1, mid+1, r, pos);
        Tree[node] = Merge(Tree[node*2], Tree[node*2+1]);
    }
}

int Query(int node, int l, int r, int posl, int posr){
    if(l>r || r<posl || l>posr)return 0;
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    return Merge(Query(node*2, l, mid, posl, posr), Query(node*2+1, mid+1, r, posl, posr));
}

void Add(int x){
    counter[arr[x]]++;
    update(1,1,mpCnt,arr[x]);
}

void Remove(int x){
    counter[arr[x]]--;
    update(1,1,mpCnt,arr[x]);
}


int main(){
    int m;
    scanf("%d%d",&n,&m);
    K=sqrt(n);

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

        int occurence = counter[Query(1,1,mpCnt,1,mpCnt)];
        //printf("%d\n",occurence);
        bool valid=0;
        if(occurence>(queries[i].r-queries[i].l+1)/2)valid=1;
        else valid=0;
        ans[queries[i].index]=valid;
    }

    for(int i=0; i<m; i++){
        if(ans[i])printf("usable\n");
        else printf("unusable\n");
    }

return 0;
}
