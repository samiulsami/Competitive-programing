#include<bits/stdc++.h>
using namespace std;

const int N=2e5+50;
int Tree[4*N]={0};

void update(int node, int l, int r, int pos, int val){
    if(l>pos || r<pos || l>r)return;
    if(l==r)Tree[node]=val;
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(node*2, l, mid, pos, val);
        else update(node*2+1, mid+1, r, pos, val);
        Tree[node] = Tree[node*2] + Tree[node*2+1];
    }
}

int query(int node, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r || posl>posr)return 0;
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr)+query(node*2+1, mid+1, r, posl, posr);
}

int Search(int node, int l, int r, int k){///K'th element
    if(l==r)return l;
    int mid = (l+r)>>1;
    int cnt = Tree[node*2];
    if(cnt>=k)return Search(node*2, l, mid, k);
    return Search(node*2+1, mid+1, r, k-cnt);
}

struct Query{
    /**
    0 - insert x
    1 - delete x
    2 - kth number
    3 - count number of elements less than x
    */
    int qType,x;
    Query(){}
    Query(int qType, int x):qType(qType),x(x){}
};

int main(){
    int q;
    scanf("%d",&q);
    vector<Query>queries(q);
    vector<int>arr;

    char c;
    int x;
    for(int i=0; i<q; i++){
        scanf(" %c",&c);
        if(c=='I'){
                scanf("%d",&x);
                queries[i]=Query(0,x);
        }
        else if(c=='D'){
                scanf("%d",&x);
                queries[i]=Query(1,x);
        }
        else if(c=='C'){
                scanf("%d",&x);
                queries[i]=Query(3,x);
        }
        else if(c=='K'){
                scanf("%d",&x);
                queries[i]=Query(2,x);
        }
        if(c!='K'){
            arr.push_back(x);
        }
    }

    sort(arr.begin(),arr.end());
    map<int,int>mp,mapped;
    int mpCnt=0;
    for(int i:arr){
        if(mp.count(i))continue;
        mp[i]=++mpCnt;
        mapped[mpCnt]=i;
    }
    mpCnt+=30;

    for(Query Q:queries){
        /**
            0 - insert x
            1 - delete x
            2 - kth number
            3 - count number of elements less than x
        */
        //printf("qtype: %d\n",Q.qType);
        if(Q.qType==0){
            int val = mp[Q.x];
            update(1,1,mpCnt,val,1);
        }
        else if(Q.qType==1){
            int val = mp[Q.x];
            update(1,1,mpCnt,val,0);
        }
        else if(Q.qType==2){
            if(Tree[1]<Q.x)printf("invalid\n");
            else {
                printf("%d\n",mapped[Search(1,1,mpCnt,Q.x)]);
            }

        }
        else {
            printf("%d\n",query(1,1,mpCnt,1,mp[Q.x]-1));
        }
    }
return 0;
}
