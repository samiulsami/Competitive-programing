#include<bits/stdc++.h>
/// SPOJ MKTHNUM - K-th Number
using namespace std;
#define all(x) x.begin(),x.end()
const int N=1e5+5;

vector<int>Tree[4*N];
pair<int,int> arr[N];
int original[N];

void Merge(vector<int> &ret, vector<int> &L, vector<int> &R){///Merge in Ascending order
    int i=0,j=0,lenL=(int)L.size(),lenR=(int)R.size();
    ret.resize(lenL+lenR);
    for(int x=0,LEN=lenL+lenR; x<LEN; x++){
        if(i==lenL)ret[x]=R[j++];
        else if(j==lenR)ret[x]=L[i++];
        else{
            if(L[i]<R[j])ret[x]=L[i++];
            else ret[x]=R[j++];
        }
    }
}

void build(int node, int l, int r){
    if(l==r){
        Tree[node].push_back(arr[l-1].second);
        return;
    }
    int mid = (l+r)>>1;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    Merge(Tree[node], Tree[node*2], Tree[node*2+1]);
}

int findKth(int node, int l, int r, int posl, int posr, int k){
    if(l==r)return Tree[node].back();
    int low=0,high=(int)Tree[node*2].size()-1,mid,upper=-1;
    while(low<=high){
        mid=(low+high)>>1;
        if(Tree[node*2][mid]<=posr){
            upper=max(upper,mid);
            low=mid+1;
        }
        else high=mid-1;
    }

    int lower=1e9;
    low=0,high=(int)Tree[node*2].size()-1;
    while(low<=high){
        mid=(low+high)>>1;
        if(Tree[node*2][mid]>=posl){
            lower=min(lower,mid);
            high=mid-1;
        }
        else low=mid+1;
    }

    int diff=upper-lower+1;
    if(lower==1e9 || upper==-1)diff=0;

    mid=(l+r)>>1;
    if(diff>=k)return findKth(node*2,l,mid,posl,posr,k);
    return findKth(node*2+1,mid+1,r,posl,posr,k-diff);
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0; i<n; i++){
            scanf("%d",&arr[i].first);
            arr[i].second=i;
            original[i]=arr[i].first;
    }
    sort(arr,arr+n);
    build(1,1,n);

    int l,r,k;
    while(m--){
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",original[findKth(1,1,n,l-1,r-1,k)]);
    }

return 0;
}
