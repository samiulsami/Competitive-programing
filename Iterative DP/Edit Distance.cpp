#include<bits/stdc++.h>
using namespace std;

/*
    leetcode problem: Edit Distance
    verdict: AC
*/

int min3(int x, int y, int z){
            return min(x,min(y,z));
}



int minDistance(string s1, string s2) {


        int len1=s1.length();
        int len2=s2.length();
        int ans=0;

        int dp[len1+5][len2+5];

        for(int i=0; i<=len1; i++){
            for(int j=0; j<=len2; j++){

                if(i==0)dp[i][j]=j;

                else if(j==0)dp[i][j]=i;

                else if(s1[i-1]==s2[j-1])dp[i][j]=dp[i-1][j-1];

                else dp[i][j]=1+min3(dp[i-1][j-1],dp[i][j-1],dp[i-1][j]);

            }
        }

        return dp[len1][len2];
}


int main(){
    string a,b;
    cin>>a>>b;
    cout<<minDistance(a,b);


return 0;
}
