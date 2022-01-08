const int K=__lg(N)+2;
struct SuffixArray{
    int SA[N],LCP[N],invSA[N],RA[N],n;
    int Table[K][N]={{0}};
    void init(const string &s){
        n=(int)s.size();
        int k,i,j;
        for(i=0; i<n; i++)RA[i]=s[i],SA[i]=i;
        auto cmp = [&](int &a, int &b)->bool{
            if(RA[a]^RA[b])return RA[a]<RA[b];
            return (a+k<n && b+k<n)?RA[a+k]<RA[b+k]:a>b;
        };
        for(k=1; k<n ;k<<=1){
            sort(SA,SA+n,cmp);
            invSA[0]=0;
            for(i=1; i<n; i++)invSA[i]=invSA[i-1]+cmp(SA[i-1],SA[i]);
            for(i=0; i<n; i++)RA[SA[i]]=invSA[i];
            if(invSA[n-1]==n-1)break;
        }
        for(i=0; i<n; i++) invSA[SA[i]]=i;
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
            Table[0][invSA[i]]=k;
        }
        for(i=1; i<=K; i++){
            for(j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }
    inline int lcp(int i, int j){
        int lg = __lg(j-i+1);
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }
}SA;