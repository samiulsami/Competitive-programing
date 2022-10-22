#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int arr[N];
vector<int>Tree[4*N];

void Merge(vector<int> &ret, vector<int> &L, vector<int> &R){
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
    if(l==r)Tree[node].push_back(arr[l]);
    else{
        int mid = (l+r)>>1;
        build(node*2,l,mid);
        build(node*2+1,mid+1,r);
        Merge(Tree[node],Tree[node*2],Tree[node*2+1]);
    }
}

int minn,maxx,p,q;

int query(int node, int l, int r, int posl, int posr){
    if(l>r || l>posr || r<posl)return 0;
    if(l>=posl && r<=posr){
        int low=0,high=(int)Tree[node].size()-1,mid;
        int lower=INT_MAX,upper=-1;
        int lowInd=INT_MAX,highInd=INT_MIN;
        while(low<=high){
            mid=(low+high)>>1;
            if(Tree[node][mid]>=p){
                lowInd=min(lowInd,mid);
                lower=min(lower,Tree[node][mid]);
                high=mid-1;
            }
            else low=mid+1;
        }

        low=0,high=(int)Tree[node].size()-1;
        while(low<=high){
            mid=(low+high)>>1;
            if(Tree[node][mid]<=q){
                highInd=max(highInd,mid);
                upper=max(upper,Tree[node][mid]);
                low=mid+1;
            }
            else high=mid-1;
        }

        if(lower!=INT_MAX && upper!=-1 &&  lower>=p && upper<=q && lowInd<=highInd){
            minn=min(minn,lower);
            maxx=max(maxx,upper);
            return highInd-lowInd+1;
        }
        else return 0;
    }

    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr);
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)scanf("%d",&arr[i]);
    build(1,1,n);

    int l,r;
    while(m--){
        scanf("%d%d%d%d",&l,&r,&p,&q);
        maxx=-1,minn=INT_MAX;
        int ans=query(1,1,n,l,r);
        if(minn==INT_MAX)minn=-1,maxx=-1;
        printf("%d %d %d\n",ans,minn,maxx);
    }

return 0;
}
