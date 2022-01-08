#include<bits/stdc++.h>
/// SPOJ KQUERYO - K-Query Online
using namespace std;

const int N=3e4+5;

vector<int>Tree[4*N];
int arr[N];

void Merge(vector<int> &ret, vector<int> &L, vector<int> &R){///Merge in Ascending order
    int i=0,j=0,lenL=(int)L.size(),lenR=(int)R.size();
    ret.resize(lenL+lenR);
    for(int x=0,LEN=lenL+lenR; x<LEN; x++){
        if(i==lenL)ret[x]=R[j++];
        else if(j==lenR)ret[x]=L[i++];
        else{
            if(L[i]>R[j])ret[x]=L[i++];
            else ret[x]=R[j++];
        }
    }
}

void build(int node, int l, int r){
    if(l==r){
        Tree[node].push_back(arr[l-1]);
        return;
    }
    int mid = (l+r)>>1;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    Merge(Tree[node], Tree[node*2], Tree[node*2+1]);
}

int query(int node, int l, int r, int posl, int posr, int k){///Returns the number of elements less than 'k'
    if(l>r || l>posr || r<posl)return 0;
    if(l>=posl && r<=posr){
        int low=0,high=(int)Tree[node].size()-1,mid,ans=-1;
        while(low<=high){
            mid=(low+high)>>1;
            if(Tree[node][mid]>k){
                ans=max(ans,mid);
                low=mid+1;
            }
            else high=mid-1;
        }
        return ans+1;
    }
    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr, k) + query(node*2+1, mid+1, r, posl, posr, k);
}

int main(){
    int n,m;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
            scanf("%d",&arr[i]);
    build(1,1,n);

    scanf("%d",&m);
    int l,r,k,last=0;
    while(m--){
        scanf("%d%d%d",&l,&r,&k);
        l^=last;
        r^=last;
        k^=last;
        last=query(1,1,n,l,r,k);
        printf("%d\n",last);
    }

return 0;
}
