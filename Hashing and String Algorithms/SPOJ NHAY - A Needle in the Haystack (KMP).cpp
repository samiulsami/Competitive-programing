#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    while(scanf("%d",&n)!=EOF){

        char *needle = (char*)malloc((n+2)*sizeof(char));
        scanf(" %s",needle);
        getchar();

        int *pi = (int*)malloc((n+1)*sizeof(int));
        pi[0]=0;
        for(int i=1,j; i<n; i++){
            j=pi[i-1];
            while(j>0 && needle[i]!=needle[j]){
                j=pi[j-1];
            }
            if(needle[i]==needle[j])pi[i]=j+1;
            else pi[i]=0;
        }

        char c;
        int i=0,occurences=0;
        int ind=1;
        while(c=getchar()){
            if(c=='\n')break;

            if(needle[i]==c)i++;
            else{
                while(i>0 && needle[i]!=c){
                    i=pi[i-1];
                }
                if(needle[i]==c)i++;
            }

            if(i==n){
                printf("%d\n",ind-n);
                i=pi[i-1];
            }
            ind++;
        }

        printf("\n");

        free(pi);
        free(needle);
    }


return 0;
}
