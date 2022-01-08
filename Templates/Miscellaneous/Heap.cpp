#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct Heap{
    T *arr;
    int n,cap;
    Heap(int x=10){
        cap=x;
        n=0;
        arr = new T[cap];
    }
    ~Heap(){delete []arr;}

    void expand(){
        if(n+1>=cap){
            cap*=2;
            T *tmp = new T[cap];
            for(int i=0; i<n; i++)tmp[i]=arr[i];
            delete []arr;
            arr = tmp;
        }
    }

    void push(T x){
        expand();
        arr[n]=x;
        heapifyUp();
        n++;
    }

    T pop(){
        assert(n>0);
        T ret=arr[0];
        arr[0]=arr[n-1];
        n--;
        heapifyDown();
        return ret;
    }

    void heapifyUp(){
        int i=n;
        int parent=(i-1)/2;
        while(parent>=0 && arr[i]<arr[parent]){
            swap(arr[parent],arr[i]);
            i=parent;
            parent = (i-1)/2;
        }
    }

    void heapifyDown(){
        int i=0;
        while((i*2+1)<n){
            int minInd = i*2+1;
            if(minInd+1<n && arr[minInd+1]<arr[minInd])minInd++;
            if(arr[i]>arr[minInd]){
                swap(arr[i],arr[minInd]);
                i=minInd;
            }
            else break;
        }
    }
};

int main(){
    srand(time(NULL));
    Heap<int> heap(1);

    for(int i=1; i<=20; i++){
        int x = rand();
        printf("%d\n",x);
        heap.push(x);
    }

    printf("-----\n");

    while(heap.n>0){
        printf("%d\n",heap.pop());
    }

return 0;
}
