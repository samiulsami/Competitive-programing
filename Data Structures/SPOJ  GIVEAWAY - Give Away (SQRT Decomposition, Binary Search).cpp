#include<bits/stdc++.h>

using namespace std;
const int SZ=710;

vector<int> B[SZ];
int arr[SZ*SZ];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0,x; i<n; i++){
            scanf("%d",&x);
            arr[i]=x;
            B[i/SZ].push_back(x);
    }

    int blocks=(n+SZ-1)/SZ;
    for(int i=0; i<blocks; i++)sort(B[i].begin(),B[i].end(),greater<int>());

    int q,low,mid,high;

    scanf("%d",&q);
    for(int i=0,qt,l,r,x; i<q; i++){
        scanf("%d",&qt);

        if(qt==0){
            scanf("%d%d%d",&l,&r,&x);
            l--;
            r--;
            int ans=0;
            int left=l/SZ;
            int right=r/SZ;

            if(left==right){
                for(int j=l; j<=r; j++)ans+=(arr[j]>=x);
            }
            else{
                ///left tail
                for(int j=l,ed=(left+1)*SZ; j<ed; j++)ans+=(arr[j]>=x);
                ///right tail
                for(int j=right*SZ; j<=r; j++)ans+=(arr[j]>=x);

                for(int j=left+1; j<=right-1; j++){
                    low=0,high=(int)B[j].size()-1;
                    int cur=-1;
                    while(low<=high){
                        mid=(low+high)>>1;
                        if(B[j][mid]<x)high=mid-1;
                        else{
                            cur=max(cur,mid);
                            low=mid+1;
                        }
                    }
                    ans+=cur+1;
                }

            }

            printf("%d\n",ans);
        }
        else{
            scanf("%d%d",&l,&x);
            l--;
            int val=arr[l];
            int block=l/SZ;
            for(int l=0; l<(int)B[block].size(); l++){
                if(B[block][l]==val){
                    B[block][l]=x;
                    break;
                }
            }
            arr[l]=x;
            sort(B[block].begin(),B[block].end(), greater<int>());
        }
    }
return 0;
}
