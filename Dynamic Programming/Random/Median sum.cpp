#include<bits/stdc++.h>
using namespace std;

int main(){
    bitset<4000001>bit;
    bit[0]=1;
    int n,arr[2001],sum=0;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    int median=(sum>>1)+sum%2;
    for(int i=0; i<n; i++)bit|=(bit<<arr[i]);
    for(int i=median; i<=sum; i++)
        if(bit[i])cout<<i,exit(0);
return 0;
}
