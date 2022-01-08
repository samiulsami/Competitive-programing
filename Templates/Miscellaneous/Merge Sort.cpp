#include<bits/stdc++.h>
using namespace std;

template<typename T>
void Mergesort(T *arr, int n){
	int halflen,l1,r1,l2,r2,len,i,j,tmplen;
	for(len=2; ;len<<=1){
		halflen=(len>>1);
		for(i=0; i+halflen<n; i+=len){
			l1=i,r1=l1+halflen;
			l2=r1,r2=min(n,l2+halflen);
			tmplen=r2-l1+1;
			T tmparr[tmplen];
			for(j=0; j<tmplen; j++){
				if(l1==r1)tmparr[j]=arr[l2++];
				else if(l2==r2)tmparr[j]=arr[l1++];
				else if(arr[l1]<arr[l2])tmparr[j]=arr[l1++];
				else tmparr[j]=arr[l2++];
			}
			for(j=0; j<tmplen; j++)arr[j+i]=tmparr[j];
		}
		if(len>=n)break;
	}
}

int main(){
    int arr[] = {1,5,3,2,5,6,7};

    int n = sizeof(arr)/sizeof(int);

    for(int i=0; i<n; i++)printf("%d ",arr[i]);
    printf("\n");

    MergeSort(arr,0,n-1);

    for(int i=0; i<n; i++)printf("%d ",arr[i]);
    printf("\n");

return 0;
}
