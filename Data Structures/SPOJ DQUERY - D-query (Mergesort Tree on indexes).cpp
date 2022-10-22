#include<bits/stdc++.h>
using namespace std;

const int N=3e4+5;
vector<int>Tree[4*N];
int prevPos[int(1e6)+4]={0};
int prevPosInd[N]={0};
int arr[N];

void Merge(vector<int> &ret, vector<int> &L, vector<int> &R){
    int i=0,j=0,lenL=(int)L.size(),lenR=(int)R.size(),total;
    total=lenL+lenR;
    ret.resize(total);
    for(int x=0; x<total; x++){
        if(i==lenL)ret[x]=R[j++];
        else if(j==lenR)ret[x]=L[i++];
        else{
            if(L[i]<R[j])ret[x]=L[i++];
            else ret[x]=R[j++];
        }
    }
}

void build(int node, int l, int r){
    if(l==r)Tree[node].push_back(prevPosInd[l]);
    else{
        int mid = (l+r)>>1;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Merge(Tree[node], Tree[node*2], Tree[node*2+1]);
    }
}

int query(int node, int l, int r, int posl, int posr){
    if(l>r || r<posl || l>posr)return 0;
    if(l>=posl && r<=posr){
        int low=0,mid,high=Tree[node].size()-1,cur=-1;
        while(low<=high){
            mid = (low+high)>>1;
            if(Tree[node][mid]<posl){
                cur=max(cur,mid);
                low=mid+1;
            }
            else high=mid-1;
        }
        return cur+1;
    }
    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr);
}

int main(){
    int n,q,l,r;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)scanf("%d",&arr[i]);
    for(int i=1; i<=n; i++){
        if(prevPos[arr[i]]==0){
            prevPosInd[i]=0;
            prevPos[arr[i]]=i;
        }
        else{
            prevPosInd[i]=prevPos[arr[i]];
            prevPos[arr[i]]=i;
        }
    }

    build(1,1,n);

    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&l,&r);
        printf("%d\n",query(1,1,n,l,r));
    }

return 0;
}
