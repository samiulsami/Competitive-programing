#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
const int Div=1000;

struct query{
    int ind,l,r;
    query(){}
    query(int ind, int l, int r):ind(ind),l(l),r(r){}
    bool operator<(const query &q)const{
        return r<q.r;
    }
}queries[N];


struct node{
    int data;
    node *left,*right;
    node(){
        left=right=this;
        data=0;
    }
}Tree[2*N];
int nodeCnt=0;

inline node *newNode(int data=0){
    node *ret = &Tree[nodeCnt++];
    ret->data=data;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r)cur->data=0;
    else{
        int mid = (l+r)>>1;
        cur->left = newNode();
        cur->right = newNode();
        build(cur->left,l,mid);
        build(cur->right,mid+1,r);
    }
}

void update(node *cur, int l, int r, int pos, int val){
    if(pos>r || pos<l || l>r)return;
    if(l==pos && r==pos)cur->data=val;
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(cur->left, l, mid, pos, val);
        else update(cur->right, mid+1, r, pos, val);
        cur->data = cur->left->data ^ cur->right->data;
    }
}

int Query(node *cur, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return Query(cur->left, l, mid, posl, posr) ^ Query(cur->right, mid+1, r, posl, posr);
}

pair<int,int>arr[N]; ///original, mapped
int prevPos[N];
int xorsum[N]={0};
map<int,int>mp;
int mpCnt=0;
int ans[N];


int main(){
    memset(prevPos,-1,sizeof(prevPos));
    int n,m;
    scanf("%d",&n);

    for(int i=1; i<=n; i++){
        scanf("%d",&arr[i].first);
        if(!mp.count(arr[i].first)){
            mp[arr[i].first]=++mpCnt;
        }
        arr[i].second=mp[arr[i].first];
        xorsum[i]=arr[i].first^xorsum[i-1];
    }

    scanf("%d",&m);

    for(int i=0,l,r; i<m; i++){
        scanf("%d%d",&l,&r);
        queries[i]=query(i,l,r);
    }
    node *root = newNode();
    build(root,1,n);
    sort(queries,queries+m);
    int maxR=1;
    for(int i=0; i<m; i++){
        query &q = queries[i];
        int l=q.l;
        int r=q.r;
        //printf("%d %d\n",l,r);

        for(;maxR<=r;maxR++){
            if(prevPos[arr[maxR].second]!=-1)update(root,1,n,prevPos[arr[maxR].second],0);
            update(root,1,n,maxR,arr[maxR].first);
            prevPos[arr[maxR].second]=maxR;
        }
        ans[q.ind]=Query(root,1,n,l,r)^(xorsum[r]^xorsum[l-1]);
    }

    for(int i=0; i<m; i++)printf("%d\n",ans[i]);

return 0;
}
