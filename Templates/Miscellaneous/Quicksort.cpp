#include<bits/stdc++.h>
using namespace std;

int arr[1005];

int _partition(int l, int r){
    int i=l;
    int pivot=arr[r];

    for(int j=l; j<r; j++){
        if(arr[j]<pivot){
            swap(arr[i],arr[j]);
            i++;
        }
    }
    swap(arr[i],arr[r]);
    return i;
}

void quicksort(int l, int r){
    stack<pair<int,int> >st;
    st.push({l,r});

    while(!st.empty()){
        pair<int,int> top=st.top();
        st.pop();
        int lft=top.first;
        int rgt=top.second;
        if(lft<rgt){
            int pivot = _partition(lft,rgt);
            st.push({lft,pivot-1});
            st.push({pivot+1,rgt});
        }
    }

}

int main(){
    int n;
    cin>>n;

    for(int i=0; i<n; i++)cin>>arr[i];

    quicksort(0,n-1);
    for(int i=0; i<n; i++)cout<<arr[i]<<" ";
    cout<<endl;

return 0;
}
