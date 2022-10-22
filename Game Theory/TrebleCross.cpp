#include<bits/stdc++.h>
using namespace std;

int grundy[250];

void precalc(){
    grundy[0]=0;
    grundy[1]=grundy[2]=grundy[3]=1;
    int a,b,i,j,k,mex;
    set<int>se;
    for(i=4; i<=200; i++){
        se.clear();
        mex=0;
        for(j=0,k=(i>>1); j<=k; j++){
            a = max(0, j-2);
            b = max(0,i-j-3);
            se.insert(grundy[a]^grundy[b]);
        }
        while(se.find(mex)!=se.end())mex++;
        grundy[i]=mex;
    }
}


int main(){
    precalc();
    //freopen("output.txt","w",stdout);
    int t,n;
    string s;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        int counter=0,xorsum=0,tmpxorsum;
        int check[250]={0};
        set<int>pr;
        cin>>s;
        n=s.length();
        for(int i=0,xx,j; i<n; i++){
            if(s[i]=='.'){
                j=i;
                counter=0;
                xx=0;
                while(i<n && s[i++]=='.')counter++;
                i--;
                check[j]=counter;
                if(j>0)if(s[j-1]=='X')xx++;
                if(i<n)if(s[i]=='X')xx++;
                xorsum^=grundy[max(0, counter-(2*xx))];
            }
        }
        for(int i=1,ins; i<n-1; i++){
            if((int)(s[i-1]+s[i]+s[i+1])==(int)(((2*'X'))+'.')){
                if(s[i]=='.')ins=i;
                else if(s[i+1]=='.')ins=i+1,i++;
                else ins=i-1;
                pr.insert(ins+1);
            }
        }
        //cout<<"xorsum: "<<xorsum<<endl;
        if(pr.empty() && xorsum){
            for(int i=0,j,xa,xb; i<n; i++){
                if(s[i]=='.'){
                    j=0;
                    xa=0;
                    xb=0;
                    counter=check[i];
                    if(i>0)if(s[i-1]=='X')j+=2,xa=1;
                    if(i+counter<n)if(s[i+counter]=='X')counter-=2,xb=1;
                    tmpxorsum = xorsum^grundy[max(0,check[i]-(2*(xa+xb)))];
                    for(int a,b; j<counter; j++){
                        a=max(0,j-2-(2*xa));
                        b=max(0,counter-j-2-1);
                        //cout<<"counter: "<<counter<<", a: "<<a<<", b: "<<b<<", tmpxorsum: "<<tmpxorsum<<endl;
                        if((tmpxorsum^grundy[a]^grundy[b])==0)pr.insert(i+j+1);
                    }
                    i=i+check[i]-1;
                }
            }
        }
        cout<<"Case "<<cas<<":";
        if(pr.empty())pr.insert(0);

        vector<int>output;
        for(set<int>::iterator it=pr.begin(); it!=pr.end(); it++)output.push_back(*it);
        sort(output.begin(), output.end());
        for(int i=0; i<output.size(); i++)cout<<" "<<output[i];
        cout<<endl;
    }
return 0;
}
